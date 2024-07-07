/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** net_common_tests
*/

#include <criterion/criterion.h>
#include "socknet.h"

Test(net_init, net_init)
{
    net_t net;

    cr_assert(net_init(&net, 0, NULL, false));
    cr_assert_null(net.logger.fs);
    cr_assert_neq(net.sock, 0);
    cr_assert_neq(net.sock, -1);
    cr_assert_eq(net.type, NET_NO_TYPE);
    cr_assert(list_empty(&net.to_send));
    cr_assert(list_empty(&net.to_recv));
}

Test(net_deinit, net_deinit)
{
    net_t net;

    cr_assert(net_init(&net, 0, NULL, false));
    net_deinit(&net);
    cr_assert_null(net.logger.fs);
    cr_assert_neq(net.sock, 0);
    cr_assert_eq(net.type, NET_NO_TYPE);
    cr_assert(list_empty(&net.to_send));
    cr_assert(list_empty(&net.to_recv));
    net_deinit(&net);
    cr_assert(true);
}
