/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_move_tests
*/

#include <criterion/criterion.h>
#include "inventory.h"

Test(inventory_move, move)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 230,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 3,
        .sibur = 0,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };

    cr_assert(inventory_move(&inv1, &inv2, "deraumere", 7));
    cr_assert_eq(inv1.deraumere, 223);
    cr_assert_eq(inv2.deraumere, 10);
}

Test(inventory_move, move_fail)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 230,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 3,
        .sibur = 0,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };

    cr_assert_not(inventory_move(&inv1, &inv2, "linemate", 7));
    cr_assert_eq(inv1.linemate, 1);
    cr_assert_eq(inv2.linemate, 1);
}
