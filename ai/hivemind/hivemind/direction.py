import random
from enum import Enum
from .vector2 import Vector2

class Direction(Enum):
    FORWARD = 1
    LEFT = 2
    RIGHT = 3

    def __str__(self) -> str:
        if self == Direction.FORWARD:
            return "forward"
        if self == Direction.LEFT:
            return "left"
        if self == Direction.RIGHT:
            return "right"
        raise ValueError("Invalid direction")

    @staticmethod
    def random() -> "Direction":
        return random.choice([Direction.FORWARD, Direction.LEFT, Direction.RIGHT])
