/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory_arithm_tests
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "inventory.h"
#include "server_tests_utils.h"

Test(inventory_add, add)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 1,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 0,
        .sibur = 0,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };
    inventory_t expected = {
        .food = 1,
        .linemate = 2,
        .deraumere = 1,
        .sibur = 0,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };

    inventory_add(&inv1, &inv2);
    cr_assert(inventory_eq(&inv1, &expected));
}

Test(inventory_sub, sub)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 1,
        .sibur = 3,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 0,
        .sibur = 5,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };
    inventory_t expected = {
        .food = 1,
        .linemate = 0,
        .deraumere = 1,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };

    inventory_sub(&inv1, &inv2);
    cr_assert(inventory_eq(&inv1, &expected));
}

Test(inventory_ge, success)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 1,
        .sibur = 5,
        .mendiane = 1,
        .phiras = 2,
        .thystame = 4,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 0,
        .sibur = 5,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };

    cr_assert(inventory_ge(&inv1, &inv2));
}

Test(inventory_ge, fail)
{
    inventory_t inv1 = {
        .food = 1,
        .linemate = 1,
        .deraumere = 1,
        .sibur = 3,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    inventory_t inv2 = {
        .food = 0,
        .linemate = 1,
        .deraumere = 0,
        .sibur = 5,
        .mendiane = 1,
        .phiras = 1,
        .thystame = 0,
    };

    cr_assert_not(inventory_ge(&inv2, &inv1));
}
