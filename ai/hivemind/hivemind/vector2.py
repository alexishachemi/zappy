class Vector2:
    def __init__(self, x: int = 0, y: int = 0) -> None:
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"

    def __eq__(self, other: 'Vector2') -> bool:
        return self.x == other.x and self.y == other.y

    def __add__(self, other: 'Vector2') -> 'Vector2':
        return Vector2(self.x + other.x, self.y + other.y)
    
    def __sub__(self, other: 'Vector2') -> 'Vector2':
        return Vector2(self.x - other.x, self.y - other.y)

    def __mul__(self, other: 'Vector2') -> 'Vector2':
        return Vector2(self.x * other.x, self.y * other.y)

    def __div__(self, other: 'Vector2') -> 'Vector2':
        return Vector2(self.x / other.x, self.y / other.y)

    def __mod__(self, other: 'Vector2') -> 'Vector2':
        return Vector2(self.x % other.x, self.y % other.y)

    def distance(self, other: 'Vector2') -> float:
        return ((self.x - other.x) ** 2 + (self.y - other.y) ** 2) ** 0.5

    def cost(self) -> int:
        return (abs(self.x) * 2) + abs(self.y)

    def rotate_left(self) -> 'Vector2':
        return Vector2(-self.y, self.x)
    
    def rotate_right(self) -> 'Vector2':
        return Vector2(self.y, -self.x)

    @staticmethod
    def direction_from_str(s: str) -> 'Vector2':
        match s:
            case "0":
                return Vector2(0, 0)
            case "1":
                return Vector2(0, 1)
            case "2":
                return Vector2(-1, 1)
            case "3":
                return Vector2(-1, 0)
            case "4":
                return Vector2(-1, -1)
            case "5":
                return Vector2(0, -1)
            case "6":
                return Vector2(1, -1)
            case "7":
                return Vector2(1, 0)
            case "8":
                return Vector2(1, 1)
            case _:
                raise ValueError("Invalid direction")
