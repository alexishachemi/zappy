/*
** EPITECH PROJECT, 2024
** arg
** File description:
** arg_parse_tests
*/

#include <criterion/criterion.h>
#include "arg.h"

Test(argm_expect_list, argm_expect_list_basic)
{
    argm_t argm;

    argm_init(&argm);
    cr_assert(argm_expect_list(&argm, "test"));
    cr_assert_str_eq((char *)argm.list_expect.head->data, "test");
    argm_deinit(&argm);
}

Test(argm_expect_list, argm_expect_list_null)
{
    cr_assert_not(argm_expect_list(NULL, "test"));
}

Test(argm_parse, argm_parse_basic)
{
    argm_t argm;
    int ac = 11;
    const char *av[] = {
        "./my_prog", "-p", "4242", "-x", "24",
        "-y", "10", "-f", "10.5", "-b", "true"
    };

    argm_init(&argm);
    cr_assert(argm_parse(&argm, ac, av));
    cr_assert_eq(arg_as_int(argm_get(&argm, "p")), 4242);
    cr_assert_eq(arg_as_int(argm_get(&argm, "x")), 24);
    cr_assert_eq(arg_as_int(argm_get(&argm, "y")), 10);
    cr_assert_eq(arg_as_float(argm_get(&argm, "f")), 10.5);
    cr_assert(arg_as_bool(argm_get(&argm, "b")));
    cr_assert_not(argm_has(&argm, "n"));
    argm_deinit(&argm);
}

Test(argm_parse, argm_parse_list)
{
    argm_t argm;
    list_t list;
    int ac = 8;
    const char *av[] = {
        "./my_prog", "-o", "team1", "team2", "team3", "team4", "-p", "4242"};

    list_init(&list);
    argm_init(&argm);
    cr_assert(argm_expect_list(&argm, "o"));
    cr_assert(argm_parse(&argm, ac, av));
    cr_assert_eq(arg_as_int(argm_get(&argm, "p")), 4242);
    cr_assert_str_eq(arg_as_string(argm_get(&argm, "o")),
        "team1 team2 team3 team4");
    cr_assert_not_null(arg_as_list(argm_get(&argm, "o"), &list));
    cr_assert_eq(list_size(&list), 4);
    cr_assert_str_eq(list_at(&list, 0), "team1");
    cr_assert_str_eq(list_at(&list, 1), "team2");
    cr_assert_str_eq(list_at(&list, 2), "team3");
    cr_assert_str_eq(list_at(&list, 3), "team4");
    list_clear(&list, NULL);
    argm_deinit(&argm);
}
