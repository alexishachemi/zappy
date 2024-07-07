import logging
from copy import deepcopy
from enum import Enum
from .inventory import Inventory
from .item import Item
from .elevation import get_requirements_range
from .vector2 import Vector2

class Order(Enum):
    MATURE = 1,
    GATHER = 2,
    RETURN = 3,
    ELEVATE = 4,

    def __str__(self) -> str:
        match self:
            case Order.MATURE:
                return "Mature"
            case Order.GATHER:
                return "Gather"
            case Order.RETURN:
                return "Return"
            case Order.ELEVATE:
                return "Elevate"
            case _:
                raise ValueError("Invalid order")

    @staticmethod
    def from_str(order: str) -> "Order":
        match order:
            case "Mature":
                return Order.MATURE
            case "Gather":
                return Order.GATHER
            case "Return":
                return Order.RETURN
            case "Elevate":
                return Order.ELEVATE
            case _:
                raise ValueError(f"Invalid order ({order})")

class Teammate:
    def __init__(self, id: int, level: int = None, inventory: Inventory = None, direction: Vector2 = None):
        self.id = id
        self.level = level or 1
        self.inventory = inventory or Inventory()
        self.direction = direction or Vector2(0, 0)
        self.timeout = 0

    def update(self, mate: "Teammate") -> None:
        self.level = mate.level
        self.inventory = mate.inventory
        self.direction = mate.direction
        self.timeout = 0

class Hivemind:

    LEADER_TIMEOUT = 1000
    TEAMMATE_TIMEOUT = 1000
    LEVEL_MISSMATCH_TIMEOUT = 50

    def __init__(self, id: int, team: str):
        self.id = id
        self.team = team
        self.leader = id
        self.leader_dir = Vector2(0, 0)
        self.teammates: list[Teammate] = []
        self.order = Order.MATURE
        self.to_send = []
        self.last_leader_bc = 0
        self.level_missmatch_counter = 0

    def is_leader(self) -> bool:
        return self.leader == self.id

    def find_leader(self) -> None:
        found_leader = False
        for mate in self.teammates:
            if mate.id == self.leader:
                found_leader = True
            if mate.id < self.leader:
                self.leader = mate.id
                logging.info(f"New leader: {mate.id}")
                return
        if not found_leader and not self.is_leader():
            self.leader = self.id
            logging.info(f"New leader: {self.id} (self)")

    def update_leader(self, mate: Teammate) -> None:
        self.find_leader()
        if mate.id == self.leader:
            self.leader_dir = mate.direction
            self.last_leader_bc = 0
        elif self.is_leader():
            self.leader_dir = Vector2(0, 0)
            self.last_leader_bc = 0
        if self.last_leader_bc > Hivemind.LEADER_TIMEOUT * len(self.teammates):
            self.leader = self.id
            logging.info("Leader timeout")
            self.set_order(Order.GATHER)
            self.last_leader_bc = 0
            self.leader_dir = Vector2(0, 0)
        self.last_leader_bc += 1

    def get_team_inventory(self, own_inventory: Inventory = None) -> Inventory:
        inventory = Inventory()
        if own_inventory and not self.is_leader():
            inventory += own_inventory
        for mate in self.teammates:
            if mate.id == self.leader:
                continue
            inventory += mate.inventory
        return inventory

    def add_teammate(self, mate: Teammate) -> None:
        for m in self.teammates:
            if m.id == mate.id:
                m.update(mate)
                logging.debug(f"Teammate {m.id} updated")
                return
        self.teammates.append(mate)
        logging.info(f"New teammate: {mate.id}")
 
    def remove_teammate(self, mate_id: int) -> None:
        for i, m in enumerate(self.teammates):
            if m.id == mate_id:
                self.teammates.pop(i)
                if mate_id == self.leader:
                    self.find_leader()
                logging.info(f"Teammate {mate_id} removed")
                return

    def update_teammate(self, ai, mate: Teammate) -> None:
        if mate.level == ai.level:
            self.add_teammate(mate)
            self.update_leader(mate)
        for m in self.teammates:
            if m.level != ai.level:
                self.level_missmatch_counter += 1
                if self.level_missmatch_counter > Hivemind.LEVEL_MISSMATCH_TIMEOUT * len(self.teammates):
                    self.level_missmatch_counter = 0
                    self.remove_teammate(m.id)
                    logging.debug(f"Teammate {m.id} level mismatch")
                continue
            else:
                self.level_missmatch_counter = 0
            m.timeout += 1
            if m.timeout > Hivemind.TEAMMATE_TIMEOUT:
                logging.info(f"Teammate {m.id} timeout")
                self.remove_teammate(m.id)
            elif m.timeout > Hivemind.TEAMMATE_TIMEOUT * 0.75:
                self.to_send.append(self.encode_message(ai, m.id, "PING"))

    def get_next_response(self) -> str | None:
        if self.to_send:
            return self.to_send.pop(0)
        return None

    def get_needed_item(self, inventory: Inventory, current_level: int) -> Item | None:
        if current_level >= 8:
            return None
        ressources = get_requirements_range(current_level, 8).ressources * 1.5
        ressources -= self.get_team_inventory(inventory)
        for item, count in ressources.items():
            if count > 0:
                return item
        return None

    def set_order(self, order: Order) -> None:
        if order != self.order:
            logging.info(f"New order: {order}")
        self.order = order

    def count_teammates(self) -> int:
        return len(self.teammates)

    def decode_message(self, ai, direction: Vector2, message: str) -> None:
        if not message.startswith("CHM"):
            return
        sender, mate_level, mate_inv, team, recipient, msg = message.removeprefix("CHM").split()
        if team != self.team:
            return
        mate = Teammate(int(sender), int(mate_level), Inventory.decode(mate_inv), direction)
        self.update_teammate(ai, mate)
        if msg == "OK" or not recipient in ("ALL", str(self.id)) or self.order == Order.MATURE:
            return
        if not self.is_leader() and msg != "PING":
            self.set_order(Order.from_str(msg))
        self.to_send.append(self.encode_message(ai, sender, "OK"))

    def encode_message(self, ai, recipient: str, msg: str) -> str:
        return f"CHM{self.id} {ai.level} {ai.inventory.encode()} {self.team} {recipient} {msg}"
