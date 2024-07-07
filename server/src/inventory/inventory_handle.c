/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "inventory.h"
#include "utils.h"

static const item_map_t item_map[] = {
    {FOOD, "food"},
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
    {ERR_ITEM, NULL}
};

static void append_item(char **str, const char *name, size_t nb)
{
    if (!str || !name)
        return;
    if (*str && strlen(*str) > 1 && nb > 0 && !strmcat(str, " ")) {
        *str = NULL;
        return;
    }
    while (nb > 0) {
        nb--;
        if (!strmcat(str, name) || (nb > 0 && !strmcat(str, " "))) {
            *str = NULL;
            return;
        }
    }
}

char *inventory_to_string(const inventory_t *inv)
{
    char *str = NULL;

    if (!inv)
        return NULL;
    str = strdup("");
    append_item(&str, "food", inv->food);
    append_item(&str, "linemate", inv->linemate);
    append_item(&str, "deraumere", inv->deraumere);
    append_item(&str, "sibur", inv->sibur);
    append_item(&str, "mendiane", inv->mendiane);
    append_item(&str, "phiras", inv->phiras);
    append_item(&str, "thystame", inv->thystame);
    return str;
}

item_t item_from_string(const char *name)
{
    if (!name)
        return ERR_ITEM;
    for (int i = 0; item_map[i].item != ERR_ITEM; i++) {
        if (strcmp(name, item_map[i].name) == 0)
            return item_map[i].item;
    }
    return ERR_ITEM;
}

const char *item_to_string(item_t item)
{
    if (item == ERR_ITEM)
        return NULL;
    for (int i = 0; item_map[i].item != ERR_ITEM; i++) {
        if (item_map[i].item == item)
            return item_map[i].name;
    }
    return NULL;
}

size_t *inventory_index_item(inventory_t *inv, item_t item)
{
    if (!inv || item == ERR_ITEM)
        return NULL;
    return ((size_t *)inv) + item;
}

size_t *inventory_index(inventory_t *inv, const char *name)
{
    return inventory_index_item(inv, item_from_string(name));
}
