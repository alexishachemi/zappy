/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** net_client_tests
*/

#include <criterion/criterion.h>
#include "socknet_tests_utils.h"

Test(net_client, net_client_queue_packet)
{
    net_t net;
    const char *str = "Hello, World!";

    cr_assert(net_init(&net, 0, NULL, false));
    net.type = NET_CLIENT;
    net.client.is_connected = true;
    cr_assert(netc_send(&net, str));
    cr_assert_eq(list_size(&net.to_send), 1);
    cr_assert_str_eq(((net_transfer_t *)list_at(&net.to_send, 0))->data, str);
    net_deinit(&net);
}

Test(net_client, net_client_queue_packet_multiple)
{
    net_t net;
    const char *str = "Hello, World!";
    const char *str2 = "Hello, World! 2";

    cr_assert(net_init(&net, 0, NULL, false));
    net.type = NET_CLIENT;
    net.client.is_connected = true;
    cr_assert(netc_send(&net, str));
    cr_assert(netc_send(&net, str2));
    cr_assert_eq(list_size(&net.to_send), 2);
    cr_assert_str_eq(((net_transfer_t *)list_at(&net.to_send, 0))->data, str);
    cr_assert_str_eq(((net_transfer_t *)list_at(&net.to_send, 1))->data, str2);
    net_deinit(&net);
}

Test(net_client, net_client_dequeue_packet)
{
    net_t net;
    const char *str = "Hello, World!";
    net_transfer_t *transfer = create_transfer(13, str);
    net_transfer_t transfer_buf = {0};

    cr_assert(net_init(&net, 0, NULL, false));
    net.type = NET_CLIENT;
    net.client.is_connected = true;
    cr_assert(list_add_ptr(&net.to_recv, transfer));
    cr_assert(netc_recv(&net, &transfer_buf));
    cr_assert_eq(list_size(&net.to_recv), 0);
    cr_assert_str_eq(transfer_buf.data, str);
    free(transfer_buf.data);
    net_deinit(&net);
}
