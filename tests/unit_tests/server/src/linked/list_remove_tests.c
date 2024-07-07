/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_remove_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(list_remove, remove_index_in_range)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int *data_removed = NULL;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_size(list), 4);
    data_removed = list_pop(list, 2);
    cr_assert_not_null(data_removed);
    cr_assert_eq(data_removed, data3);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(list->head->data, data);
    cr_assert_eq(list->head->next->data, data2);
    cr_assert_eq(list->head->next->next->data, data4);
    cr_assert_null(list->head->next->next->next);
    list_destroy(list, destroy_int);
    destroy_int(data_removed);
}

Test(list_remove, remove_index_out_of_range)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int *data_removed = NULL;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_size(list), 4);
    data_removed = list_pop(list, 12);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(data_removed, data4);
    cr_assert_eq(list->head->data, data);
    cr_assert_eq(list->head->next->data, data2);
    cr_assert_eq(list->head->next->next->data, data3);
    cr_assert_null(list->head->next->next->next);
    list_destroy(list, destroy_int);
    destroy_int(data_removed);
}

Test(list_remove, remove_index_zero)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int *data_removed = NULL;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_size(list), 4);
    data_removed = list_pop(list, 0);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(data_removed, data);
    cr_assert_eq(list->head->data, data2);
    cr_assert_eq(list->head->next->data, data3);
    cr_assert_eq(list->head->next->next->data, data4);
    cr_assert_null(list->head->next->next->next);
    list_destroy(list, destroy_int);
    destroy_int(data_removed);
}

Test(list_remove, remove_index_last)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int *data_removed = NULL;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_size(list), 4);
    data_removed = list_pop(list, 3);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(data_removed, data4);
    cr_assert_eq(list->head->data, data);
    cr_assert_eq(list->head->next->data, data2);
    cr_assert_eq(list->head->next->next->data, data3);
    cr_assert_null(list->head->next->next->next);
    list_destroy(list, destroy_int);
    destroy_int(data_removed);
}

Test(list_remove, remove_index_negative)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int *data_removed = NULL;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_size(list), 4);
    data_removed = list_pop(list, -3);
    cr_assert_eq(list_size(list), 3);
    cr_assert_not_null(data_removed);
    cr_assert_eq(data_removed, data2);
    cr_assert_eq(list->head->data, data);
    cr_assert_eq(list->head->next->data, data3);
    cr_assert_eq(list->head->next->next->data, data4);
    cr_assert_null(list->head->next->next->next);
    list_destroy(list, destroy_int);
    destroy_int(data_removed);
}

Test(list_remove_if, remove_if_null_list)
{
    int right = 1;

    cr_assert_eq(list_remove_if(NULL, int_gt, &right, destroy_int), -1);
}

Test(list_remove_if, remove_if_null_compare)
{
    list_t *list = list_create();
    int right = 1;

    cr_assert_eq(list_remove_if(list, NULL, &right, destroy_int), -1);
    list_destroy(list, destroy_int);
}

Test(list_remove_if, remove_if_null_right)
{
    list_t *list = list_create();

    cr_assert_eq(list_remove_if(list, int_gt, NULL, destroy_int), -1);
    list_destroy(list, destroy_int);
}

Test(list_remove_if, remove_if_no_match)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int right = 3;

    *data = 1;
    *data2 = 2;
    cr_assert_eq(list_remove_if(list, int_gt, &right, destroy_int), 0);
    cr_assert_eq(list_size(list), 2);
    list_destroy(list, destroy_int);
}

Test(list_remove_if, remove_if_one_match)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int right = 1;

    *data = 1;
    *data2 = 2;
    cr_assert_eq(list_remove_if(list, int_gt, &right, destroy_int), 1);
    cr_assert_eq(list_size(list), 1);
    list_destroy(list, destroy_int);
}

Test(list_remove_if, remove_if_multiple_match)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);
    int right = 1;

    *data = 1;
    *data2 = 2;
    *data3 = 1;
    *data4 = 4;
    cr_assert_eq(list_remove_if(list, int_gt, &right, destroy_int), 2);
    cr_assert_eq(list_size(list), 2);
    list_destroy(list, destroy_int);
}
