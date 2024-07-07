/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** fork.c
*/

#include "server.h"
#include "utils.h"
#include "gui.h"

static void job_fork(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    world_add_egg_from_player(server, player);
    nets_send(&server->net, player->sock, "ok");
}

static void fork_start(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    gui_broadcast_event(server, gui_send_egg_lay_start, player);
}

bool job_build_fork(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata) {
        return false;
    }
    jdata->data = NULL;
    jdata->start = fork_start;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = job_fork;
    return true;
}
