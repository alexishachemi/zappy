from .item import Item

class Inventory:
    def __init__(
            self,
            food: int = 0,
            linemate: int = 0,
            deraumere: int = 0,
            sibur: int = 0,
            mendiane: int = 0,
            phiras: int = 0,
            thystame: int = 0
        ) -> None:
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.sibur = sibur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self) -> str:
        return f"food {self.food}, linemate {self.linemate}, deraumere {self.deraumere}, sibur {self.sibur}, mendiane {self.mendiane}, phiras {self.phiras}, thystame {self.thystame}"

    def __getitem__(self, item: Item) -> int:
        if item == Item.FOOD:
            return self.food
        if item == Item.LINEMATE:
            return self.linemate
        if item == Item.DERAUMERE:
            return self.deraumere
        if item == Item.SIBUR:
            return self.sibur
        if item == Item.MENDIANE:
            return self.mendiane
        if item == Item.PHIRAS:
            return self.phiras
        if item == Item.THYSTAME:
            return self.thystame
        raise ValueError("Invalid item")

    def __setitem__(self, item: Item, value: int) -> None:
        if item == Item.FOOD:
            self.food = value
        elif item == Item.LINEMATE:
            self.linemate = value
        elif item == Item.DERAUMERE:
            self.deraumere = value
        elif item == Item.SIBUR:
            self.sibur = value
        elif item == Item.MENDIANE:
            self.mendiane = value
        elif item == Item.PHIRAS:
            self.phiras = value
        elif item == Item.THYSTAME:
            self.thystame = value
        else:
            raise ValueError("Invalid item")

    def items(self) -> list[tuple[Item, int]]:
        return [
            (Item.FOOD, self.food),
            (Item.LINEMATE, self.linemate),
            (Item.DERAUMERE, self.deraumere),
            (Item.SIBUR, self.sibur),
            (Item.MENDIANE, self.mendiane),
            (Item.PHIRAS, self.phiras),
            (Item.THYSTAME, self.thystame)
        ]

    def __iter__(self):
        return iter([self.food, self.linemate, self.deraumere, self.sibur, self.mendiane, self.phiras, self.thystame])

    def __add__(self, other: "Inventory") -> "Inventory":
        inv = Inventory()
        for item, amount in self.items():
            inv[item] = amount + other[item]
        return inv

    def __sub__(self, other: "Inventory") -> "Inventory":
        inv = Inventory()
        for item, amount in self.items():
            inv[item] = amount - other[item]
        return inv

    def __ge__(self, other: "Inventory") -> bool:
        for item, amount in self.items():
            if amount < other[item]:
                return False
        return True

    def __mul__(self, other: float) -> "Inventory":
        inv = Inventory()
        for item, amount in self.items():
            inv[item] = int(amount * other)
        return inv

    def copy(self) -> "Inventory":
        return Inventory(self.food, self.linemate, self.deraumere, self.sibur, self.mendiane, self.phiras, self.thystame)

    def encode(self) -> str:
        return f"{self.food}.{self.linemate}.{self.deraumere}.{self.sibur}.{self.mendiane}.{self.phiras}.{self.thystame}"

    @staticmethod
    def decode(data: str) -> "Inventory":
        inv = Inventory()
        inv.food, inv.linemate, inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, inv.thystame = [int(x) for x in data.split(".")]
        return inv
    
    @staticmethod
    def from_tile_str(tile_str: str) -> "Inventory":
        inv = Inventory()
        tile_str = tile_str.strip("[]")
        for item_str in tile_str.split(" "):
            try:
                inv[Item.from_str(item_str)] += 1
            except ValueError:
                pass
        return inv

    @staticmethod
    def from_inv_str(inv_str: str) -> "Inventory":
        inv = Inventory()
        inv_str = inv_str.strip("[] ")
        for item_str in inv_str.split(","):
            try:
                item, count = item_str.split()
            except ValueError as e:
                raise ValueError(f"Invalid inventory string: {inv_str}") from e
            inv[Item.from_str(item)] = int(count)
        return inv
