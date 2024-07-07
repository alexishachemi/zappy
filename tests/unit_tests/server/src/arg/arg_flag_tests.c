/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_flag_tests
*/

#include <criterion/criterion.h>
#include "arg.h"

Test(arg_flag, arg_flag_type)
{
    cr_assert_eq(arg_flag_type("-p"), FLAG_SINGLE);
    cr_assert_eq(arg_flag_type("--port"), FLAG_DOUBLE);
    cr_assert_eq(arg_flag_type("port"), FLAG_NONE);
    cr_assert_eq(arg_flag_type(NULL), FLAG_NONE);
}

Test(arg_flag, arg_unflag)
{
    const char *single_flag = "-p";
    const char *double_flag = "--port";
    const char *no_flag = "port";

    cr_assert_str_eq(arg_unflag(single_flag), "p");
    cr_assert_str_eq(arg_unflag(double_flag), "port");
    cr_assert_null(arg_unflag(no_flag));
    cr_assert_null(arg_unflag(NULL));
}
