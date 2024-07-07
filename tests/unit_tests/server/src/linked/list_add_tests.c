/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_add_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(list_add, add_node_to_list)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 5;
    *data2 = 10;
    cr_assert_eq(list->head->data, data);
    cr_assert_eq(list->tail->data, data2);
    cr_assert_eq(*(int*)(list->head->data), 5);
    cr_assert_eq(*(int*)(list->head->next->data), 10);
    cr_assert_eq(list->head->next, list->tail);
    cr_assert_eq(list->tail->prev, list->head);
    list_destroy(list, destroy_int);
}

Test(list_add, add_ptr_to_list)
{
    list_t *list = list_create();
    int data = 5;
    int data2 = 10;
    int *ptr = &data;
    int *ptr2 = &data2;
    int *data_ptr = list_add_ptr(list, ptr);
    int *data2_ptr = list_add_ptr(list, ptr2);

    cr_assert_not_null(list);
    cr_assert_not_null(data_ptr);
    cr_assert_not_null(data2_ptr);
    cr_assert_eq(list->head->data, data_ptr);
    cr_assert_eq(list->tail->data, data2_ptr);
    cr_assert_eq(*(int*)(list->head->data), 5);
    cr_assert_eq(*(int*)(list->head->next->data), 10);
    cr_assert_eq(list->head->next, list->tail);
    cr_assert_eq(list->tail->prev, list->head);
    list_destroy(list, NULL);
}

Test(list_add, add_copy_to_list)
{
    list_t *list = list_create();
    int data = 5;
    int data2 = 10;
    int *data_ptr = list_add_copy(list, &data, sizeof(int));
    int *data2_ptr = list_add_copy(list, &data2, sizeof(int));

    cr_assert_not_null(list);
    cr_assert_not_null(data_ptr);
    cr_assert_not_null(data2_ptr);
    cr_assert_eq(list->head->data, data_ptr);
    cr_assert_eq(list->tail->data, data2_ptr);
    cr_assert_eq(*(int*)(list->head->data), 5);
    cr_assert_eq(*(int*)(list->head->next->data), 10);
    cr_assert_eq(list->head->next, list->tail);
    cr_assert_eq(list->tail->prev, list->head);
    list_destroy(list, NULL);
}
