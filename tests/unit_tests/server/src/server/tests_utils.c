/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_utils
*/

#include "server.h"

bool inventory_eq(const inventory_t *inv1, const inventory_t *inv2)
{
    size_t *val1 = (size_t *)inv1;
    size_t *val2 = (size_t *)inv2;

    if (!inv1 || !inv2)
        return false;
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        if (val1[i] != val2[i]) {
            dprintf(2, "expected: %ld, got: %ld\n", val2[i], val1[i]);
            return false;
        }
    }
    return true;
}
