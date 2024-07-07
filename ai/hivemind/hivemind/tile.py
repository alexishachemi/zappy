from .vector2 import Vector2
from .inventory import Inventory
from .item import Item

class Tile:
    def __init__(self) -> None:
        self.position = Vector2(0, 0)
        self.inventory = Inventory()
        self.players = 0
        self.eggs = 0

    def __str__(self) -> str:
        return f"pos {self.position} {self.inventory} players {self.players} eggs {self.eggs}"

    @staticmethod
    def from_str(s: str) -> 'Tile':
        tile = Tile()
        for entity in s.split():
            match entity:
                case "player":
                    tile.players += 1
                case "egg":
                    tile.eggs += 1
                case _:
                    tile.inventory[Item.from_str(entity)] += 1
        return tile

    @staticmethod
    def from_look_str(s: str) -> list["Tile"]:
        tiles = []
        pos = Vector2(0, 0)
        pos_start = 0
        pos_end = 0
        for tile_str in s.strip("[]").split(","):
            tile = Tile.from_str(tile_str.strip())
            tile.position = Vector2(pos.x, pos.y)
            tiles.append(tile)
            pos.x += 1
            if pos.x > pos_end:
                pos.y += 1
                pos_start -= 1
                pos_end += 1
                pos.x = pos_start
        tiles.sort(key=lambda tile: tile.position.cost())
        return tiles
