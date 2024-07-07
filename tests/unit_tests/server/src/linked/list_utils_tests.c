/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_utils_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(node_isolate, node_isolate_null)
{
    node_isolate(NULL);
    cr_assert(1);
}

Test(node_link, node_link_null)
{
    node_link(NULL, NULL);
    cr_assert(1);
}

Test(node_link, node_link_one_node)
{
    node_t *node = node_create(NULL);

    node_link(node, NULL);
    cr_assert_null(node->prev);
    cr_assert_null(node->next);
    node_destroy(node, NULL);
}

Test(node_link, node_link_two_nodes)
{
    node_t *node = node_create(NULL);
    node_t *node2 = node_create(NULL);

    node_link(node, node2, NULL);
    cr_assert_null(node->prev);
    cr_assert_eq(node->next, node2);
    cr_assert_eq(node2->prev, node);
    cr_assert_null(node2->next);
    node_destroy_all(node, NULL);
}

Test(node_link, node_link_three_nodes)
{
    node_t *node = node_create(NULL);
    node_t *node2 = node_create(NULL);
    node_t *node3 = node_create(NULL);

    node_link(node, node2, node3, NULL);
    cr_assert_null(node->prev);
    cr_assert_eq(node->next, node2);
    cr_assert_eq(node2->prev, node);
    cr_assert_eq(node2->next, node3);
    cr_assert_eq(node3->prev, node2);
    cr_assert_null(node3->next);
    node_destroy_all(node, NULL);
}
