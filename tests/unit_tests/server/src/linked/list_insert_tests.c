/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_add_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(list_insert, insert_node_positive_index)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_insert(list, allocate_int, 0);
    int *data3 = list_insert(list, allocate_int, 4);
    int *data4 = list_insert(list, allocate_int, 1);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(*(int*)(list->head->data), 2);
    cr_assert_eq(*(int*)(list->head->next->data), 4);
    cr_assert_eq(*(int*)(list->head->next->next->data), 1);
    cr_assert_eq(*(int*)(list->head->next->next->next->data), 3);
    list_destroy(list, destroy_int);
}

Test(list_insert, insert_node_negative_index)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_insert(list, allocate_int, -1);
    int *data3 = list_insert(list, allocate_int, -2);
    int *data4 = list_insert(list, allocate_int, -10);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(*(int*)(list->head->data), 4);
    cr_assert_eq(*(int*)(list->head->next->data), 1);
    cr_assert_eq(*(int*)(list->head->next->next->data), 3);
    cr_assert_eq(*(int*)(list->head->next->next->next->data), 2);
    list_destroy(list, destroy_int);
}

Test(list_insert, insert_node_null_list)
{
    int *data = list_insert(NULL, allocate_int, 0);

    cr_assert_null(data);
}

Test(list_insert, insert_node_null_node)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_insert(list, NULL, 0);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_null(data2);
    list_destroy(list, destroy_int);
}
