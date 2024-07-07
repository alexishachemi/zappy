/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_handle_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(player_items_to_string, handle)
{
    inventory_t inv = {
        .food = 1,
        .linemate = 1,
        .deraumere = 1,
        .sibur = 0,
        .mendiane = 0,
        .phiras = 0,
        .thystame = 0,
    };
    const char *expected = "[food 1, linemate 1, deraumere 1, "
        "sibur 0, mendiane 0, phiras 0, thystame 0]";
    char *result = player_items_to_string(&inv);

    cr_assert_str_eq(result, expected);
    free(result);
}

Test(player_items_to_string, handle_null)
{
    cr_assert_null(player_items_to_string(NULL));
}

Test(player_items_to_string, handle_empty)
{
    inventory_t inv = {0};
    const char *expected = "[food 0, linemate 0, deraumere 0, "
        "sibur 0, mendiane 0, phiras 0, thystame 0]";
    char *result = player_items_to_string(&inv);

    cr_assert_str_eq(result, expected);
    free(result);
}
