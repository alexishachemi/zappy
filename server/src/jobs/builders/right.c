/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-alexis.hachemi
** File description:
** right.c
*/

#include "server.h"
#include "utils.h"

static void right(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    player_right(server, player);
    nets_send(&server->net, player->sock, "ok");
}

bool job_build_right(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = right;
    return true;
}
