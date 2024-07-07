/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_create_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(list_create, list_alloc)
{
    list_t *list = list_create();

    cr_assert_not_null(list);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);
    free(list);
}

Test(node_create, node_alloc_no_allocator)
{
    node_t *node = node_create(NULL);

    cr_assert_not_null(node);
    cr_assert_null(node->data);
    cr_assert_null(node->list);
    cr_assert_null(node->prev);
    cr_assert_null(node->next);
    free(node);
}

Test(node_create, node_create_with_allocator)
{
    node_t *node = node_create(allocate_int);
    int *data = NULL;

    cr_assert_not_null(node);
    data = node->data;
    cr_assert_not_null(data);
    cr_assert_null(node->list);
    cr_assert_null(node->prev);
    cr_assert_null(node->next);
    free(data);
    free(node);
}
