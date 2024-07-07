import logging
from random import random, seed
from time import time
from multiprocessing import Process
from .hivemind import Hivemind
from .direction import Direction
from .net import Net
from .inventory import Inventory
from .pathfinder import Pathfinder
from .item import Item
from .vector2 import Vector2
from .vision import Vision
from .hivemind import Order
from .elevation import get_requirements_range

class Ai:

    MIN_FOOD = 15
    MAX_FOOD = 35

    def __init__(self, host: str, port: int, team: str, wait: bool, multip_max: int) -> None:
        self.id = int(time() + (time() * random()))
        self.net = Net()
        self.pathfinder = Pathfinder()
        self.inventory = Inventory()
        self.hivemind = Hivemind(self.id, team)
        self.level = 1
        self.alive = True
        self.maxed = False
        self.multip_max = multip_max
        self.args = (host, port, team, wait, multip_max - 1)
        self.gathering_food = True
        self.map_size = Vector2(0, 0)
        self.food_limits = [self.MIN_FOOD, self.MAX_FOOD]

    @staticmethod
    def run(host: str, port: int, team: str, wait: bool, multip_max: int) -> bool:
        ai = Ai(host, port, team, wait, multip_max)
        try:
            if not ai.start():
                return False
            while ai.update(): pass
        except (KeyboardInterrupt, BrokenPipeError, ConnectionError):
            logging.warning(f"AI {ai.id} stopped")
        return True

    ############################################################### Main logic

    def start(self) -> bool:
        try:
            remaining_slots, self.map_size = self.net.connect(*self.args[:-1])
            if remaining_slots > 0:
                self.multip_fork()
        except:
            return False
        logging.info(f"Started AI {self.id}")
        self.hivemind.set_order(Order.MATURE)
        return True

    def update(self) -> bool:
        if not self.alive:
            if self.maxed:
                logging.warning(f"AI {self.id} reached max level")
            else:
                logging.critical(f"AI {self.id} died")
            return False
        self._update()
        self.communicate()
        self.update_inventory()
        if self.inventory[Item.FOOD] >= self.food_limits[1]:
            self.gathering_food = False
        if self.inventory[Item.FOOD] <= self.food_limits[0]:
            self.gathering_food = True
        if self.gathering_food \
            and self.hivemind.order != Order.ELEVATE and self.hivemind.order != Order.RETURN:
            self.gather_item(Item.FOOD)
            return True
        self.update_food_limits()
        self.execute_order()
        return True

    def _update(self, elevating: bool = False) -> None:
        self.net.update()
        if not elevating:
            while self.handle_received_events(elevating): pass

    def communicate(self) -> None:
        msg = self.hivemind.get_next_response()
        if msg is not None:
            self.broadcast_msg(msg)
        if self.hivemind.is_leader() \
            and (self.hivemind.order == Order.RETURN or self.hivemind.order == Order.ELEVATE):
            self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "PING"))

    def execute_order(self):
        match self.hivemind.order:
            case Order.MATURE:
                self.mature()
            case Order.GATHER:
                self.gather_item()
            case Order.RETURN:
                self.return_to_leader()
            case Order.ELEVATE:
                self.elevate_to_leader()

    ################################################################### Orders

    def mature(self) -> None:
        if self.level > 1 and self.inventory[Item.FOOD] >= self.food_limits[0]:
            self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "OK"))
            self.hivemind.set_order(Order.GATHER)
        elif self.look().tiles[0].inventory.linemate > 0:
            self.elevate()
        elif not self.fetch_item(Item.LINEMATE):
            self.random_move()
        elif self.pathfinder.finished():
            self.move(self.pathfinder.next_direction())
        else:
            self.random_move()

    def gather_item(self, item: Item = None) -> None:
        target_item = item or Item.FOOD
        if self.hivemind.is_leader():
            if self.get_team_slots() == 0:
                self.fork()
            elif self.level >= 2 and self.group_can_elevate():
                self.hivemind.set_order(Order.RETURN)
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "Return"))
        else:
            target_item = item or self.hivemind.get_needed_item(self.inventory, self.level)
        if target_item is None:
            return self.return_to_leader()
        if self.pathfinder.active():
            self.move(self.pathfinder.next_direction())
        elif self.pathfinder.finished():
            self.take(target_item)
        elif not self.fetch_item(target_item):
            self.random_move()

    def return_to_leader(self) -> None:
        if self.hivemind.is_leader():
            ground_tile = self.look().tiles[0].inventory
            if self.inventory[Item.FOOD] < 10:
                self.take(Item.FOOD)
            elif ground_tile.food <= 5:
                self.drop(Item.FOOD)
            if not self.group_can_elevate(ground_tile) \
                or ground_tile.food + self.inventory[Item.FOOD] < 3:
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "Gather"))
                self.hivemind.set_order(Order.GATHER)
            elif self.can_incant():
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "Elevate"))
                self.hivemind.set_order(Order.ELEVATE)
            else:
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "Return"))
            return
        if self.pathfinder.active():
            self.move(self.pathfinder.next_direction())
        elif self.pathfinder.finished():
            self.broadcast_msg(self.hivemind.encode_message(self, self.hivemind.leader, "PING"))
        elif self.hivemind.leader_dir == Vector2(0, 0):
            self.pathfinder.clear()
            return
        else:
            self.pathfinder.compute_path(self.hivemind.leader_dir)

    def elevate_to_leader(self) -> None:
        if self.hivemind.is_leader() and self.can_incant():
            self.elevate()
        if self.inventory[Item.FOOD] < 10:
            self.take(Item.FOOD)
        if self.hivemind.is_leader():
            if self.group_can_elevate():
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "PING"))
            else:
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "Gather"))
                self.hivemind.set_order(Order.GATHER)
            return
        if not self.hivemind.is_leader() and self.hivemind.leader_dir != Vector2(0, 0):
            self.broadcast_msg(self.hivemind.encode_message(self, self.hivemind.leader, "PING"))
            return self.return_to_leader()
        for item, amount in reversed(self.inventory.items()):
            if item == Item.FOOD:
                continue
            if amount > 0 and self.drop(item):
                break

    ################################################################## Actions

    def set_level(self, level: int) -> None:
        self.level = level
        logging.warning(f"AI {self.id} is now level {self.level}")
        if self.level >= 8:
            self.maxed = True

    def await_response(self, elevating: False) -> str:
        resp = None
        while resp is None:
            self._update(elevating)
            resp = self.net.recv()
        return resp

    def attempt(self, action: str, elevating: bool = False) -> str | None:
        self.net.send(action)
        resp = self.await_response(elevating)
        if resp == "ko":
            logging.debug(f"Failed to execute action '{action}'")
            return None
        return resp

    def do(self, action: str) -> str:
        resp = self.attempt(action)
        if resp is None:
            raise Exception(f"Failed to execute action '{action}'")
        return resp

    def move(self, direction: Direction) -> None:
        if self.hivemind.is_leader() and self.hivemind.order in [Order.RETURN, Order.ELEVATE]:
            self.pathfinder.clear()
            return
        match direction:
            case Direction.FORWARD:
                self.move_forward()
            case Direction.LEFT:
                self.turn_left()
            case Direction.RIGHT:
                self.turn_right()
            case _:
                raise ValueError("Invalid direction")

    def random_move(self) -> None:
        if self.hivemind.is_leader() and self.hivemind.order in [Order.RETURN, Order.ELEVATE]:
            self.pathfinder.clear()
            return
        self.move(Direction.random())
        self.move_forward()

    def multip_fork(self) -> None:
        if self.multip_max <= 0:
            return
        self.multip_max = 0
        proc = Process(target=Ai.run, args=self.args)
        proc.start()
    
    def await_elevation(self) -> None:
        resp = self.await_response(True)
        if resp.startswith("Current level:"):
            self.set_level(int(resp.removeprefix("Current level:").strip()))

    def fetch_item(self, item: Item) -> bool:
        for _ in range(4):
            item_pos = self.look().find_item(item)
            if item_pos is not None:
                logging.debug(f"Found {item} at {item_pos}")
                self.pathfinder.compute_path(item_pos)
                return True
            self.turn_right()
        return False

    def process_message(self, direction: Vector2, message: str) -> None:
        self.hivemind.decode_message(self, direction, message)

    def process_event(self, event: str, elevating: bool = False) -> bool:
        if event.startswith("message"):
            self.net.to_recv.remove(event)
            msg_dir, msg_text = event.removeprefix("message").split(",", 1)
            self.process_message(Vector2.direction_from_str(msg_dir.strip()), msg_text.strip())
            return True
        if event == "dead":
            self.net.to_recv.remove(event)
            self.alive = False
            return True
        if event == "Elevation underway":
            self.net.to_recv.remove(event)
            self.await_elevation()
            return True
        if event.startswith("Current level:"):
            self.net.to_recv.remove(event)
            self.level = int(event.removeprefix("Current level:").strip())
            return True
        return False

    def handle_received_events(self, elevating: bool = False) -> bool:
        for received in self.net.to_recv:
            if self.process_event(received, elevating):
                return True
        return False

    def group_can_elevate(self, ground_tile = None) -> bool:
        ground = ground_tile or self.look().tiles[0].inventory
        requirements = get_requirements_range(self.level, 8)
        if requirements is None:
            return False
        if not self.hivemind.count_teammates() >= requirements.players - 1:
            return False
        if not (self.hivemind.get_team_inventory(self.inventory) + ground) >= requirements.ressources:
            return False
        return True

    def can_incant(self) -> bool:
        return self.look().tiles[0].players >= self.hivemind.count_teammates() + 1

    def update_food_limits(self) -> None:
        if self.hivemind.is_leader() and self.hivemind.order != Order.MATURE:
            self.food_limits = [self.MIN_FOOD * 3, self.MAX_FOOD * 3]
            return
        match self.hivemind.order:
            case Order.GATHER:
                self.food_limits = [self.MIN_FOOD * 2, self.MAX_FOOD * 2]
            case _:
                self.food_limits = [self.MIN_FOOD, self.MAX_FOOD]

    ############################################################## AI Commands

    def move_forward(self) -> None:
        logging.debug("Moved forward")
        self.do("Forward")
    
    def turn_left(self) -> None:
        logging.debug("Turned left")
        self.do("Left")

    def turn_right(self) -> None:
        logging.debug("Turned right")
        self.do("Right")

    def look(self) -> Vision:
        logging.debug("Looked around")
        return Vision(self.do("Look"))

    def update_inventory(self) -> None:
        self.inventory = Inventory.from_inv_str(self.do("Inventory"))
        logging.debug(f"Updated inventory: {self.inventory}")

    def broadcast_msg(self, msg: str) -> None:
        self.do(f"Broadcast {msg}")
        logging.debug(f"Broadcasted message: {msg}")

    def get_team_slots(self) -> int:
        logging.debug("Got team slots")
        return int(self.do("Connect_nbr"))
    
    def fork(self) -> None:
        self.do("Fork")
        self.multip_fork()
        logging.debug("Forked")

    def eject(self) -> bool:
        if self.attempt("Eject") is not None:
            logging.debug("Ejected")
            return True
        logging.error("Failed to eject")
        return False

    def take(self, item: Item) -> bool:
        success = self.attempt(f"Take {item}") is not None
        if success:
            self.inventory[item] += 1
            logging.debug(f"Successfully took {item}")
            if self.hivemind.order != Order.MATURE:
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "OK"))
        else:
            logging.debug(f"Failed to take {item}")
        return success

    def drop(self, item: Item) -> bool:
        success = self.attempt(f"Set {item}") is not None
        if success:
            self.inventory[item] -= 1
            logging.debug(f"Successfully dropped {item}")
            if self.hivemind.order != Order.MATURE:
                self.broadcast_msg(self.hivemind.encode_message(self, "ALL", "OK"))
        else:
            logging.debug(f"Failed to drop {item}")
        return success

    def elevate(self) -> bool:
        logging.debug("Elevating")
        resp = self.attempt("Incantation", True)
        if resp is None:
            logging.debug("Failed to elevate")
            return False
        self.await_elevation()
        return True
