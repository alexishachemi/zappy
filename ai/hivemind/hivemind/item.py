from enum import Enum

class Item(Enum):
    FOOD = 1
    LINEMATE = 2
    DERAUMERE = 3
    SIBUR = 4
    MENDIANE = 5
    PHIRAS = 6
    THYSTAME = 7

    def __str__(self) -> str:
        if self == Item.FOOD:
            return 'food'
        if self == Item.LINEMATE:
            return 'linemate'
        if self == Item.DERAUMERE:
            return 'deraumere'
        if self == Item.SIBUR:
            return 'sibur'
        if self == Item.MENDIANE:
            return 'mendiane'
        if self == Item.PHIRAS:
            return 'phiras'
        if self == Item.THYSTAME:
            return 'thystame'
        raise ValueError('Invalid item')

    @staticmethod
    def from_str(s: str) -> 'Item':
        if s == 'food':
            return Item.FOOD
        if s == 'linemate':
            return Item.LINEMATE
        if s == 'deraumere':
            return Item.DERAUMERE
        if s == 'sibur':
            return Item.SIBUR
        if s == 'mendiane':
            return Item.MENDIANE
        if s == 'phiras':
            return Item.PHIRAS
        if s == 'thystame':
            return Item.THYSTAME
        raise ValueError(f"Invalid item string ({s})")
