/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_init_tests
*/

#include <criterion/criterion.h>
#include "arg.h"

Test(argm_init, argm_init_basic)
{
    argm_t argm;

    argm_init(&argm);
    cr_assert_eq(list_size(&argm.args), 0);
    cr_assert_eq(list_size(&argm.list_expect), 0);
    argm_deinit(&argm);
}

Test(argm_init, argm_init_null)
{
    argm_init(NULL);
    cr_assert(1);
}

Test(argm_deinit, argm_deinit_basic)
{
    argm_t argm;

    argm_init(&argm);
    argm_expect_list(&argm, "test");
    cr_assert_eq(list_size(&argm.list_expect), 1);
    argm_deinit(&argm);
    cr_assert_eq(list_size(&argm.args), 0);
    cr_assert_eq(list_size(&argm.list_expect), 0);
}

Test(argm_deinit, argm_deinit_null)
{
    argm_t argm;

    argm_init(&argm);
    argm_deinit(NULL);
    cr_assert(1);
}

Test(arg_create, arg_create_basic)
{
    arg_t *arg = arg_create("test", "value");

    cr_assert_not_null(arg);
    cr_assert_str_eq(arg->name, "test");
    cr_assert_str_eq(arg->value, "value");
    arg_destroy(arg);
}

Test(arg_create, arg_create_null_name)
{
    arg_t *arg = arg_create(NULL, NULL);

    cr_assert_null(arg);
}

Test(arg_destroy, arg_destroy_basic)
{
    arg_t *arg = arg_create("test", "value");

    arg_destroy(arg);
    cr_assert(1);
}

Test(arg_destroy, arg_destroy_null)
{
    arg_destroy(NULL);
    cr_assert(1);
}
