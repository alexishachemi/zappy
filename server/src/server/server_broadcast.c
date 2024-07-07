/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_broadcast
*/

#include <string.h>
#include "server.h"
#include "utils.h"
#include "gui.h"

static void apply_broadcast(broadcaster_t *b, player_t *player)
{
    char buf[32];
    char *str = NULL;
    unsigned int dir_id = 0;

    if (player == b->emitter)
        return;
    dir_id = world_get_direction(b->server, player->position,
        b->emitter->position, player->direction);
    memset(buf, 0, 32);
    snprintf(buf, 32, "message %d, ", dir_id);
    if (!strmcat(&str, buf) || !strmcat(&str, b->msg))
        return;
    nets_send(&b->server->net, player->sock, str);
    free(str);
}

bool server_broadcast(server_t *server, player_t *emitter, const char *msg)
{
    broadcaster_t broadcaster = {0};

    if (!server || !emitter || !msg)
        return false;
    broadcaster.server = server;
    broadcaster.emitter = emitter;
    broadcaster.msg = msg;
    gui_broadcast_event(server, gui_send_broadcast, &broadcaster);
    list_apply(&server->world.players,
        (applicator_t)apply_broadcast, &broadcaster);
    return TRUE_SLOG(server, DEBUG,
        "Player %ld broadcasted message: %s\n", emitter->id, msg);
}
