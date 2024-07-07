from .tile import Tile
from .vector2 import Vector2

class Vision:
    def __init__(self, look_str) -> None:
        self.tiles = Tile.from_look_str(look_str)
    
    def find_item(self, item) -> Vector2 | None:
        for tile in self.tiles:
            if tile.inventory[item] > 0:
                return tile.position
        return None
