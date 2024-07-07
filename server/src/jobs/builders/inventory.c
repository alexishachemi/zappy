/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-alexis.hachemi
** File description:
** invtry.c
*/

#include "server.h"
#include "utils.h"

static void inventory(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    char *str = NULL;

    str = player_items_to_string(&player->inventory);
    if (!str)
        return;
    nets_send(&server->net, player->sock, str);
    free(str);
}

bool job_build_inventory(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = inventory;
    return true;
}
