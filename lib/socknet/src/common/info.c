/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** info
*/

#include "socknet_dev.h"

port_t net_get_port(int sock)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
        return 0;
    return ntohs(sin.sin_port);
}
