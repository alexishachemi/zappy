/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_obj_events
*/

#include <string.h>
#include "gui.h"

bool gui_send_drop(server_t *server, int sock, void *arg)
{
    char buf[16];
    object_interact_t *itr = arg;

    if (!server || !itr)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pdr %ld %d", itr->player->id, itr->item);
    nets_send(&server->net, sock, buf);
    return true;
}

bool gui_send_collect(server_t *server, int sock, void *arg)
{
    char buf[16];
    object_interact_t *itr = arg;

    if (!server || !itr)
        return false;
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "pgt %ld %d", itr->player->id, itr->item);
    nets_send(&server->net, sock, buf);
    return true;
}
