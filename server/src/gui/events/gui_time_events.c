/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_cmd_time
*/

#include <string.h>
#include "gui.h"
#include "utils.h"

bool gui_send_time_unit(server_t *server, int sock, UNUSED void *arg)
{
    char buf[16];

    if (!server)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "sgt %d", server->world.freq);
    return nets_send(&server->net, sock, buf);
}

bool gui_set_time_unit(server_t *server, int sock, void *arg)
{
    char buf[16];
    int *freq = arg;

    if (!server || !freq)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "sst %d", *freq);
    server->world.freq = *freq;
    nets_send(&server->net, sock, buf);
    return true;
}
