/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile_handle_tests
*/

#include <criterion/criterion.h>
#include "server.h"

Test(tile_items_to_string, single_items)
{
    tile_t tile = {
        .inventory = {
            .food = 1,
            .linemate = 1,
            .deraumere = 1,
            .sibur = 0,
            .mendiane = 0,
            .phiras = 0,
            .thystame = 0,
        },
    };
    const char *expected = "food linemate deraumere";
    char *result = tile_to_string(&tile);

    cr_assert_str_eq(result, expected);
    free(result);
}

Test(tile_items_to_string, multiple_items)
{
    tile_t tile = {
        .inventory = {
            .food = 5,
            .linemate = 2,
            .deraumere = 0,
            .sibur = 0,
            .mendiane = 0,
            .phiras = 0,
            .thystame = 0,
        },
    };
    const char *expected = "food food food food food linemate linemate";
    char *result = tile_to_string(&tile);

    cr_assert_str_eq(result, expected);
    free(result);
}

Test(tile_items_to_string, empty)
{
    tile_t tile = {0};
    const char *expected = "";
    char *result = tile_to_string(&tile);

    cr_assert_str_eq(result, expected);
    free(result);
}

Test(tile_items_to_string, null)
{
    cr_assert_null(tile_to_string(NULL));
}
