/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward
*/

#include "server.h"
#include "utils.h"

static void forward(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    player_forward(server, player);
    nets_send(&server->net, player->sock, "ok");
}

bool job_build_forward(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = forward;
    return true;
}
