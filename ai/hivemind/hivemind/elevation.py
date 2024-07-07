from .inventory import Inventory

class ElevationRequirement:
    def __init__(self, target_level: int, players: int, ressources: Inventory) -> None:
        self.target_level = target_level
        self.players = players
        self.ressources = ressources

    def __str__(self) -> str:
        return f"level {self.target_level}: players {self.players} {self.ressources}"

    def __add__(self, other: 'ElevationRequirement') -> 'ElevationRequirement':
        return ElevationRequirement(self.target_level, max(self.players, other.players), self.ressources + other.ressources)

REQUIREMENTS = [
    ElevationRequirement(2, 1, Inventory(0, 1, 0, 0, 0, 0, 0)),
    ElevationRequirement(3, 2, Inventory(0, 1, 1, 1, 0, 0, 0)),
    ElevationRequirement(4, 2, Inventory(0, 2, 0, 1, 0, 2, 0)),
    ElevationRequirement(5, 4, Inventory(0, 1, 1, 2, 0, 1, 0)),
    ElevationRequirement(6, 4, Inventory(0, 1, 2, 1, 3, 0, 0)),
    ElevationRequirement(7, 6, Inventory(0, 1, 2, 3, 0, 1, 0)),
    ElevationRequirement(8, 6, Inventory(0, 2, 2, 2, 2, 2, 1)),
]

def get_requirements(current_level: int) -> ElevationRequirement:
    if current_level < 1 or current_level >= 8:
        raise ValueError('Invalid target level')
    return REQUIREMENTS[current_level - 1]

def get_requirements_range(current_level: int, target_level: int) -> ElevationRequirement:
    if not (2 <= current_level < target_level <= 8):
        raise ValueError(f"Invalid level range ({current_level} -> {target_level})")
    requirements = ElevationRequirement(0, 0, Inventory(0, 0, 0, 0, 0, 0, 0))
    for level in range(current_level, target_level):
        requirements += get_requirements(level)
    return requirements
