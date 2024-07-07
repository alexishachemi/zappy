/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** look.c
*/

#include "server.h"
#include "utils.h"

static void look(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    char *vision = NULL;

    vision = world_get_vision_str(server, player->position,
        player->direction, player->level);
    if (vision) {
        nets_send(&server->net, player->sock, vision);
        free(vision);
    }
}

bool job_build_look(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->check_first = false;
    jdata->data = NULL;
    jdata->check = NULL;
    jdata->failure = NULL;
    jdata->sucess = look;
    return true;
}
