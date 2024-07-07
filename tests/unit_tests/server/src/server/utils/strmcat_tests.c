/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** strmcat_tests
*/

#include <criterion/criterion.h>
#include "utils.h"

Test(strmcat, simple_cat)
{
    char *dest = strdup("Hello");
    char *src = " World";
    strmcat(&dest, src);

    cr_assert_str_eq(dest, "Hello World");
    free(dest);
}

Test(strmcat, null_dest)
{
    char *dest = NULL;
    char *src = " World";
    strmcat(&dest, src);

    cr_assert_str_eq(dest, " World");
    free(dest);
}

Test(strmcat, null_src)
{
    char *dest = strdup("Hello");
    char *src = NULL;
    strmcat(&dest, src);

    cr_assert_str_eq(dest, "Hello");
    free(dest);
}

Test(strmcat, null_both)
{
    char *dest = NULL;
    char *src = NULL;
    strmcat(&dest, src);

    cr_assert_null(dest);
}

Test(strmcat, empty_dest)
{
    char *dest = strdup("");
    char *src = " World";
    strmcat(&dest, src);

    cr_assert_str_eq(dest, " World");
    free(dest);
}

Test(strmcat, empty_src)
{
    char *dest = strdup("Hello");
    char *src = "";
    strmcat(&dest, src);

    cr_assert_str_eq(dest, "Hello");
    free(dest);
}
