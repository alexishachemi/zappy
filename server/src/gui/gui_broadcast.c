/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_broadcast
*/

#include "gui.h"

void gui_broadcast_event(server_t *server, gui_callback_t callback, void *arg)
{
    if (!server || !callback)
        return;
    for (node_t *n = server->graphical_clients.head; n; n = n->next) {
        callback(server, *(int *)n->data, arg);
    }
}
