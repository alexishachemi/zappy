/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** socknet_server_tests
*/

#include <criterion/criterion.h>
#include "socknet_tests_utils.h"

static bool int_eq(void *data, void *ref)
{
    return *(int *)data == *(int *)ref;
}

Test(net_server, net_server_host)
{
    net_t net;

    cr_assert(net_init(&net, 0, NULL, false));
    cr_assert(nets_host(&net));
    cr_assert_neq(net.sock, 0);
    cr_assert_neq(net.sock, -1);
    net_deinit(&net);
}

Test(net_server, net_server_queue_packet)
{
    net_t net;
    const char *str = "Hello, World!";
    const char *expected = "Hello, World!\n";
    int sock = 0;

    cr_assert(net_init(&net, 0, NULL, false));
    list_add_ptr(&net.server.clients, &sock);
    cr_assert(nets_send(&net, sock, str));
    cr_assert_eq(list_size(&net.to_send), 1);
    list_remove_if(&net.server.clients, int_eq, &sock, NULL);
    cr_assert_str_eq(
        ((net_transfer_t *)list_at(&net.to_send, 0))->data, expected);
    net_deinit(&net);
}

Test(net_server, net_server_queue_packet_multiple)
{
    net_t net;
    int sock = 0;
    const char *str = "Hello, World!";
    const char *str2 = "Hello, World! 2";
    const char *expected = "Hello, World!\n";
    const char *expected2 = "Hello, World! 2\n";

    cr_assert(net_init(&net, 0, NULL, false));
    list_add_ptr(&net.server.clients, &sock);
    cr_assert(nets_send(&net, 0, str));
    cr_assert(nets_send(&net, 0, str2));
    cr_assert_eq(list_size(&net.to_send), 2);
    list_remove_if(&net.server.clients, int_eq, &sock, NULL);
    cr_assert_str_eq(
        ((net_transfer_t *)list_at(&net.to_send, 0))->data, expected);
    cr_assert_str_eq(
        ((net_transfer_t *)list_at(&net.to_send, 1))->data, expected2);
    net_deinit(&net);
}

Test(net_server, net_server_dequeue_packet)
{
    net_t net;
    const char *str = "Hello, World!";
    net_transfer_t *transfer = create_transfer(13, str);
    net_transfer_t transfer_buf = {0};

    cr_assert(net_init(&net, 0, NULL, false));
    cr_assert(nets_host(&net));
    cr_assert(list_add_ptr(&net.to_recv, transfer));
    cr_assert(nets_recv(&net, &transfer_buf));
    cr_assert_eq(list_size(&net.to_recv), 0);
    cr_assert_str_eq(transfer_buf.data, str);
    free(transfer_buf.data);
    net_deinit(&net);
}
