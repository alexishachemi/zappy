/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_iterator_tests
*/

#include <criterion/criterion.h>
#include "arg.h"

Test(arg_iterator, arg_iterator_init)
{
    arg_iterator_t iter;
    size_t args_len = 10;
    const char *args[] = {
        "-p", "4242", "-n", "team1", "-c", "10", "-x", "10", "-y", "10"};

    cr_assert(arg_iterator_init(&iter, args_len, args));
    cr_assert_eq(iter.args, args);
    cr_assert_eq(iter.args_len, args_len);
    cr_assert_eq(iter.current_index, 0);
}

Test(arg_iterator, arg_iterator_init_null)
{
    size_t args_len = 10;
    const char *args[] = {
        "-p", "4242", "-n", "team1", "-c", "10", "-x", "10", "-y", "10"};

    cr_assert_not(arg_iterator_init(NULL, args_len, args));
}

Test(arg_iterator, arg_iterator_next)
{
    arg_iterator_t iter;
    size_t args_len = 10;
    const char *args[] = {
        "-p", "4242", "-n", "team1", "-c", "10", "-x", "10", "-y", "10"};

    cr_assert(arg_iterator_init(&iter, args_len, args));
    cr_assert_str_eq(arg_iterator_next(&iter), "-p");
    cr_assert_str_eq(arg_iterator_next(&iter), "4242");
    cr_assert_str_eq(arg_iterator_next(&iter), "-n");
    cr_assert_str_eq(arg_iterator_next(&iter), "team1");
    cr_assert_str_eq(arg_iterator_next(&iter), "-c");
    cr_assert_str_eq(arg_iterator_next(&iter), "10");
    cr_assert_str_eq(arg_iterator_next(&iter), "-x");
    cr_assert_str_eq(arg_iterator_next(&iter), "10");
    cr_assert_str_eq(arg_iterator_next(&iter), "-y");
    cr_assert_str_eq(arg_iterator_next(&iter), "10");
    cr_assert_null(arg_iterator_next(&iter));
}

Test(arg_iterator, arg_iterator_next_none)
{
    arg_iterator_t iter;
    const char *args[] = {};
    size_t args_len = 0;

    cr_assert(arg_iterator_init(&iter, args_len, args));
    cr_assert_null(arg_iterator_next(&iter));
}

Test(arg_iterator, arg_iterator_next_null)
{
    cr_assert_null(arg_iterator_next(NULL));
}
