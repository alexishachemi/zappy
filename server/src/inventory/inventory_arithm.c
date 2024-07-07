/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_arithm
*/

#include "inventory.h"

void inventory_add(inventory_t *dest, const inventory_t *src)
{
    if (!dest || !src)
        return;
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        ((size_t *)dest)[i] += ((const size_t *)src)[i];
    }
}

void inventory_sub(inventory_t *dest, const inventory_t *src)
{
    size_t *dest_arr = (size_t *)dest;
    size_t *src_arr = (size_t *)src;

    if (!dest || !src)
        return;
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        if (dest_arr[i] < src_arr[i])
            dest_arr[i] = 0;
        else
            dest_arr[i] -= src_arr[i];
    }
}

bool inventory_ge(const inventory_t *inv1, const inventory_t *inv2)
{
    if (!inv1 || !inv2)
        return false;
    for (size_t i = 0; i < ITEMS_TYPES; i++) {
        if (((size_t *)inv1)[i] < ((const size_t *)inv2)[i])
            return false;
    }
    return true;
}
