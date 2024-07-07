from .direction import Direction
from .vector2 import Vector2

class Pathfinder:
    def __init__(self) -> None:
        self.path = []
        self.finish_flag = False

    def finished(self) -> bool:
        if self.finish_flag:
            self.finish_flag = False
            return True
        return False

    def clear(self) -> None:
        self.path = []
        self.finish_flag = False

    def active(self) -> bool:
        return len(self.path) != 0

    def next_direction(self) -> Direction | None:
        if not self.path:
            return None
        next_dir = self.path.pop(0)
        if not self.path:
            self.finish_flag = True
        return next_dir

    def compute_path(self, target_pos: Vector2) -> None:
        self.path = []
        self.finish_flag = False
        if target_pos == Vector2(0, 0):
            self.finish_flag = True
            return
        flipped = False
        if target_pos.y < 0:
            self.path.append(Direction.RIGHT)
            self.path.append(Direction.RIGHT)
            flipped = True
        for _ in range(abs(target_pos.y)):
            self.path.append(Direction.FORWARD)
        if target_pos.x < 0:
            self.path.append(Direction.LEFT if not flipped else Direction.RIGHT)
        elif target_pos.x > 0:
            self.path.append(Direction.RIGHT if not flipped else Direction.LEFT)
        for _ in range(abs(target_pos.x)):
            self.path.append(Direction.FORWARD)

    def __len__(self) -> int:
        return len(self.path)

    def __str__(self) -> str:
        return str(self.path)
