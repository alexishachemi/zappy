/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** inventory
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define ITEMS_TYPES (sizeof(inventory_t) / sizeof(size_t))

typedef enum {
    ERR_ITEM = -1,
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} item_t;

typedef struct {
    item_t item;
    const char *name;
} item_map_t;

typedef struct inventory_s {
    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} inventory_t;

void inventory_init(inventory_t *inv);

void inventory_add(inventory_t *dest, const inventory_t *src);
void inventory_sub(inventory_t *dest, const inventory_t *src);
bool inventory_ge(const inventory_t *inv1, const inventory_t *inv2);

char *inventory_to_string(const inventory_t *inv);
item_t item_from_string(const char *name);
const char *item_to_string(item_t item);
size_t *inventory_index_item(inventory_t *inv, item_t item);
size_t *inventory_index(inventory_t *inv, const char *name);

bool inventory_move(inventory_t *from, inventory_t *to,
    const char *name, size_t amount);

void inventory_print(inventory_t *inv);
