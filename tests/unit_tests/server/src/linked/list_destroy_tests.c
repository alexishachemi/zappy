/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_destroy_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(node_destroy, node_destroy_no_destroy)
{
    node_t *node = node_create(NULL);

    node_destroy(node, NULL);
    cr_assert(1);
}

Test(node_destroy, node_destroy_with_destroy)
{
    node_t *node = node_create(allocate_int);

    node_destroy(node, destroy_int);
    cr_assert(1);
}

Test(node_destroy, node_destroy_null)
{
    node_destroy(NULL, destroy_int);
    cr_assert(1);
}

Test(node_destroy_all, node_destroy_all_no_destroy)
{
    node_t *node = node_create(NULL);

    node_destroy_all(node, NULL);
    cr_assert(1);
}

Test(node_destroy_all, node_destroy_all_with_destroy)
{
    node_t *node = node_create(allocate_int);

    node_destroy_all(node, destroy_int);
    cr_assert(1);
}

Test(node_destroy_all, node_destroy_all_null)
{
    node_destroy_all(NULL, destroy_int);
    cr_assert(1);
}

Test(list_clear, list_clear_no_destroy)
{
    list_t list = {NULL, NULL};
    node_t *node = node_create(NULL);

    list.head = node;
    list.tail = node;
    list_clear(&list, NULL);
    cr_assert_null(list.head);
    cr_assert_null(list.tail);
}

Test(list_clear, list_clear_with_destroy)
{
    list_t list = {NULL, NULL};
    node_t *node = node_create(allocate_int);

    list.head = node;
    list.tail = node;
    list_clear(&list, destroy_int);
    cr_assert_null(list.head);
    cr_assert_null(list.tail);
}

Test(list_destroy, list_destroy_no_destroy)
{
    list_t *list = list_create();

    list_destroy(list, NULL);
    cr_assert(1);
}

Test(list_destroy, list_destroy_with_destroy)
{
    list_t *list = list_create();

    list_destroy(list, destroy_int);
    cr_assert(1);
}

Test(list_destroy, list_destroy_null)
{
    list_destroy(NULL, destroy_int);
    cr_assert(1);
}
