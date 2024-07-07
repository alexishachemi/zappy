/*
** EPITECH PROJECT, 2024
** linked
** File description:
** list_handle_tests
*/

#include <criterion/criterion.h>
#include "test_utils.h"
#include "linked.h"

Test(list_get, get_index_in_range)
{
    list_t *list = list_create();
    int *data_get = NULL;
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    data_get = list_at(list, 2);
    cr_assert_not_null(data_get);
    cr_assert_eq(data_get, data3);
    list_destroy(list, destroy_int);
}

Test(list_get, get_index_out_of_range)
{
    list_t *list = list_create();
    int *data_get = NULL;
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    data_get = list_at(list, 12);
    cr_assert_not_null(data_get);
    cr_assert_eq(data_get, data4);
    list_destroy(list, destroy_int);
}

Test(list_get, get_index_negative)
{
    list_t *list = list_create();
    int *data_get = NULL;
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    data_get = list_at(list, -2);
    cr_assert_not_null(data_get);
    cr_assert_eq(data_get, data3);
    list_destroy(list, destroy_int);
}

Test(list_get, get_empty_list)
{
    list_t *list = list_create();
    int *data_get = NULL;

    cr_assert_not_null(list);
    data_get = list_at(list, 0);
    cr_assert_null(data_get);
    list_destroy(list, destroy_int);
}

Test(list_get, get_first)
{
    list_t *list = list_create();
    int *data_get = NULL;
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    data_get = list_at(list, 0);
    cr_assert_not_null(data_get);
    cr_assert_eq(data_get, data);
    list_destroy(list, destroy_int);
}

Test(list_get, get_last)
{
    list_t *list = list_create();
    int *data_get = NULL;
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    data_get = list_at(list, 2);
    cr_assert_not_null(data_get);
    cr_assert_eq(data_get, data3);
    list_destroy(list, destroy_int);
}

Test(list_move, move_index_in_range)
{
    list_t *list = list_create();
    list_t *list2 = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(list2);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_move(list, 2, list2), true);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(list_size(list2), 1);
    cr_assert_eq(*(int *)list_at(list, 0), 1);
    cr_assert_eq(*(int *)list_at(list, 1), 2);
    cr_assert_eq(*(int *)list_at(list, 2), 4);
    cr_assert_eq(*(int *)list_at(list2, 0), 3);
    list_destroy(list, destroy_int);
    list_destroy(list2, destroy_int);
}

Test(list_move, move_index_out_of_range)
{
    list_t *list = list_create();
    list_t *list2 = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(list2);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_move(list, 12, list2), true);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(list_size(list2), 1);
    cr_assert_eq(*(int *)list_at(list, 0), 1);
    cr_assert_eq(*(int *)list_at(list, 1), 2);
    cr_assert_eq(*(int *)list_at(list, 2), 3);
    cr_assert_eq(*(int *)list_at(list2, 0), 4);
    list_destroy(list, destroy_int);
    list_destroy(list2, destroy_int);
}

Test(list_move, move_negative_index)
{
    list_t *list = list_create();
    list_t *list2 = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(list2);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    *data4 = 4;
    cr_assert_eq(list_move(list, -2, list2), true);
    cr_assert_eq(list_size(list), 3);
    cr_assert_eq(list_size(list2), 1);
    cr_assert_eq(*(int *)list_at(list, 0), 1);
    cr_assert_eq(*(int *)list_at(list, 1), 2);
    cr_assert_eq(*(int *)list_at(list, 2), 4);
    cr_assert_eq(*(int *)list_at(list2, 0), 3);
    list_destroy(list, destroy_int);
    list_destroy(list2, destroy_int);
}

Test(list_apply, apply_sum_int)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int acc = 0;

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    list_apply(list, sum_int, &acc);
    cr_assert_eq(acc, 6);
    list_destroy_free(list);
}

Test(list_apply, apply_sum_int_empty_list)
{
    list_t *list = list_create();
    int acc = 0;

    cr_assert_not_null(list);
    list_apply(list, sum_int, &acc);
    cr_assert_eq(acc, 0);
    list_destroy_free(list);
}

Test(list_apply, apply_sum_int_null_list)
{
    int acc = 0;

    list_apply(NULL, sum_int, &acc);
    cr_assert_eq(acc, 0);
}

Test(list_map, map_add)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    *data = 1;
    *data2 = 2;
    *data3 = 3;
    list_map(list, inc_int);
    cr_assert_eq(*data, 2);
    cr_assert_eq(*data2, 3);
    cr_assert_eq(*data3, 4);
    list_map(list, inc_int);
    cr_assert_eq(*data, 3);
    cr_assert_eq(*data2, 4);
    cr_assert_eq(*data3, 5);
    list_destroy(list, destroy_int);
}

Test(list_map, map_empty_list)
{
    list_t *list = list_create();

    cr_assert_not_null(list);
    list_map(list, inc_int);
    list_destroy_free(list);
}

Test(list_map, map_null_list)
{
    list_map(NULL, inc_int);
}

Test(list_has_ptr, has_ptr)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_eq(list_has_ptr(list, data), true);
    cr_assert_eq(list_has_ptr(list, data2), true);
    cr_assert_eq(list_has_ptr(list, data3), true);
    list_destroy(list, destroy_int);
}

Test(list_has_ptr, has_ptr_empty_list)
{
    list_t *list = list_create();
    int *data = malloc(sizeof(int));

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_eq(list_has_ptr(list, data), false);
    free(data);
    list_destroy_free(list);
}

Test(list_has_ptr, has_ptr_null_list)
{
    int *data = malloc(sizeof(int));

    cr_assert_eq(list_has_ptr(NULL, data), false);
    free(data);
}

Test(list_has_ptr, does_not_have_ptr)
{
    list_t *list = list_create();
    int *data = list_add(list, allocate_int);
    int *data2 = list_add(list, allocate_int);
    int *data3 = list_add(list, allocate_int);
    int *data4 = malloc(sizeof(int));

    cr_assert_not_null(list);
    cr_assert_not_null(data);
    cr_assert_not_null(data2);
    cr_assert_not_null(data3);
    cr_assert_not_null(data4);
    cr_assert_eq(list_has_ptr(list, data4), false);
    free(data4);
    list_destroy(list, destroy_int);
}
