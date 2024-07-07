/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_size_tests
*/

#include <criterion/criterion.h>
#include "linked.h"
#include "test_utils.h"

Test(list_size, empty_list)
{
    list_t *list = list_create();
    size_t size = list_size(list);

    cr_assert_eq(size, 0);
    list_destroy(list, NULL);
}

Test(list_size, one_element)
{
    list_t *list = list_create();
    list_add(list, allocate_int);
    size_t size = list_size(list);

    cr_assert_eq(size, 1);
    list_destroy(list, destroy_int);
}

Test(list_size, multiple_elements)
{
    list_t *list = list_create();
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    size_t size = list_size(list);

    cr_assert_eq(size, 4);
    list_destroy(list, destroy_int);
}

Test(list_size, null_list)
{
    size_t size = list_size(NULL);

    cr_assert_eq(size, 0);
}

Test(list_empty, empty_list)
{
    list_t *list = list_create();
    bool is_empty = list_empty(list);

    cr_assert_eq(is_empty, true);
    list_destroy(list, NULL);
}

Test(list_empty, one_element)
{
    list_t *list = list_create();
    list_add(list, allocate_int);
    bool is_empty = list_empty(list);

    cr_assert_eq(is_empty, false);
    list_destroy(list, destroy_int);
}

Test(list_empty, multiple_elements)
{
    list_t *list = list_create();
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    list_add(list, allocate_int);
    bool is_empty = list_empty(list);

    cr_assert_eq(is_empty, false);
    list_destroy(list, destroy_int);
}

Test(list_empty, null_list)
{
    bool is_empty = list_empty(NULL);

    cr_assert_eq(is_empty, true);
}
