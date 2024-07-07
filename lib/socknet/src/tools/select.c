/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** select handling
*/

#include "socknet_dev.h"

bool net_can_write_fd(int fd, unsigned int timeout_ms)
{
    fd_set set;
    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(fd, &set);
    tv.tv_sec = 0;
    tv.tv_usec = timeout_ms;
    if (select(fd + 1, NULL, &set, NULL, &tv) < 0)
        return false;
    return FD_ISSET(fd, &set);
}

bool net_can_read_fd(int fd, unsigned int timeout_ms)
{
    fd_set set;
    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(fd, &set);
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = timeout_ms;
    if (select(fd + 1, &set, NULL, NULL, &tv) < 0)
        return false;
    return FD_ISSET(fd, &set);
}
