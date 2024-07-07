/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_server
*/

#include <string.h>
#include <stdlib.h>
#include "socknet.h"

const char *status_msg =
"You are client %d\n"
"Connected clients: %d\n"
"Type /exit to leave\n"
"Type /kill to shutdown the server\n"
"Type /status to show this message\n"
"Type anything else to send a message\n";

static void send_status(net_t *net, int sock)
{
    char data[1024] = {0};

    snprintf(data, sizeof(data), status_msg,
        sock, list_size(&net->server.clients));
    nets_send(net, sock, data);
}

static void handle_clients(net_t *net)
{
    int sock = 0;

    while (nets_accept_incoming(net, &sock)) {
        nets_send(net, sock, "Server: Welcome to the server!\n");
        send_status(net, sock);
    }
    while (nets_accept_outgoing(net, &sock)) {
        (void)sock;
    }
}

static bool echo_msg(net_t *net, int sender_sock, const char *msg)
{
    char data[1024] = {0};
    int *sock_ptr = NULL;

    snprintf(data, sizeof(data), "Client %d: %s", sender_sock, msg);
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        sock_ptr = n->data;
        if (*sock_ptr == sender_sock)
            continue;
        if (!nets_send(net, *sock_ptr, data))
            return false;
    }
    return true;
}

static bool handle_command(net_t *net, int sock,
    const char *cmd, bool *is_running)
{
    if (strcmp(cmd, "/status\n") == 0) {
        send_status(net, sock);
        return true;
    }
    if (strcmp(cmd, "/exit\n") == 0) {
        nets_kick(net, sock);
        return true;
    }
    if (strcmp(cmd, "/kill\n") == 0) {
        *is_running = false;
        return true;
    }
    return false;
}

static bool handle_packets(net_t *net)
{
    net_transfer_t transfer;
    bool is_running = true;

    while (nets_recv(net, &transfer)) {
        printf("Socket %d: %s\n",
            transfer.sock, transfer.data);
        if (!handle_command(net, transfer.sock, transfer.data, &is_running))
            is_running = echo_msg(net, transfer.sock, transfer.data);
        free(transfer.data);
    }
    return is_running;
}

static int get_port(int ac, char **av)
{
    if (ac != 2)
        return -1;
    return atoi(av[1]);
}

int main(int ac, char **av)
{
    net_t net = {0};
    bool is_running = true;
    int port = get_port(ac, av);

    if (port <= 0 || !(net_init(&net, (port_t)port, "server.log")
        && net_set_log_level(&net, INFO) && nets_host(&net)))
        return 84;
    while (is_running && net_update(&net) == NET_OK) {
        handle_clients(&net);
        is_running = handle_packets(&net);
    }
    net_deinit(&net);
    return 0;
}
