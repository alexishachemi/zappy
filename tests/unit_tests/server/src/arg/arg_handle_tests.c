/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_handle_tests
*/

#include <criterion/criterion.h>
#include "arg.h"

Test(arg_as_int, arg_as_int_basic)
{
    arg_t *arg = arg_create("test", "42");

    cr_assert_not_null(arg);
    cr_assert_eq(arg_as_int(arg), 42);
    arg_destroy(arg);
}

Test(arg_as_int, arg_as_int_null)
{
    cr_assert_eq(arg_as_int(NULL), 0);
}

Test(arg_as_int, arg_as_int_invalid)
{
    arg_t *arg = arg_create("test", "test");

    cr_assert_not_null(arg);
    cr_assert_eq(arg_as_int(arg), 0);
    arg_destroy(arg);
}

Test(arg_as_float, arg_as_float_basic)
{
    arg_t *arg = arg_create("test", "42.42");
    float res = 0.0f;

    cr_assert_not_null(arg);
    res = arg_as_float(arg);
    cr_assert(res > 42.41 && res < 42.43);
    arg_destroy(arg);
}

Test(arg_as_float, arg_as_float_null)
{
    cr_assert_eq(arg_as_float(NULL), 0.0f);
}

Test(arg_as_float, arg_as_float_invalid)
{
    arg_t *arg = arg_create("test", "test");

    cr_assert_not_null(arg);
    cr_assert_eq(arg_as_float(arg), 0.0f);
    arg_destroy(arg);
}

Test(arg_as_string, arg_as_string_basic)
{
    arg_t *arg = arg_create("test", "test");

    cr_assert_not_null(arg);
    cr_assert_str_eq(arg_as_string(arg), "test");
    arg_destroy(arg);
}

Test(arg_as_string, arg_as_string_null)
{
    cr_assert_null(arg_as_string(NULL));
}

Test(arg_as_bool, arg_as_bool_basic)
{
    arg_t *arg = arg_create("test", "true");

    cr_assert_not_null(arg);
    cr_assert_eq(arg_as_bool(arg), true);
    arg_destroy(arg);
}

Test(arg_as_bool, arg_as_bool_null)
{
    cr_assert_eq(arg_as_bool(NULL), false);
}

Test(arg_as_bool, arg_as_bool_invalid)
{
    arg_t *arg = arg_create("test", "test");

    cr_assert_not_null(arg);
    cr_assert_eq(arg_as_bool(arg), false);
    arg_destroy(arg);
}

Test(arg_as_list, arg_as_list_basic)
{
    arg_t *arg = arg_create("test", "test test2");
    list_t *list = list_create();

    cr_assert_not_null(arg);
    cr_assert_not_null(list);
    cr_assert_not_null(arg_as_list(arg, list));
    cr_assert_eq(list_size(list), 2);
    cr_assert_str_eq(list_at(list, 0), "test");
    cr_assert_str_eq(list_at(list, 1), "test2");
    list_destroy_free(list);
    arg_destroy(arg);
}

Test(arg_as_list, arg_as_list_long)
{
    arg_t *arg = arg_create("test", "test test2 test3 test4 test5");
    list_t *list = list_create();

    cr_assert_not_null(arg);
    cr_assert_not_null(list);
    cr_assert_not_null(arg_as_list(arg, list));
    cr_assert_eq(list_size(list), 5);
    cr_assert_str_eq(list_at(list, 0), "test");
    cr_assert_str_eq(list_at(list, 1), "test2");
    cr_assert_str_eq(list_at(list, 2), "test3");
    cr_assert_str_eq(list_at(list, 3), "test4");
    cr_assert_str_eq(list_at(list, 4), "test5");
    list_destroy_free(list);
    arg_destroy(arg);
}

Test(arg_as_list, arg_as_list_null)
{
    cr_assert_null(arg_as_list(NULL, NULL));
}
