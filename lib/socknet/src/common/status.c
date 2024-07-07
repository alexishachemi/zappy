/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** status function
*/

#include "socknet_dev.h"

bool net_is_busy(const net_t *net)
{
    return net_has_to_send(net) || net_has_to_recv(net);
}
