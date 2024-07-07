/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** nb_connect.c
*/

#include "server.h"
#include "utils.h"

static void nb_team_slot(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    char buf[32];

    snprintf(buf, 32, "%lu",
        egg_count_from_team(&server->world.eggs, player->team_id));
    nets_send(&server->net, player->sock, buf);
}

bool job_build_nb_team_slot(server_t *server, player_t *player,
    job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = nb_team_slot;
    return true;
}
