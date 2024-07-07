/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_cmd
*/

#include <string.h>
#include "gui.h"

static player_t *player_from_id(server_t *server, void *arg)
{
    int id = 0;
    char **args = arg;

    if (!arg)
        return NULL;
    id = atoi(args[0]);
    if (id < 0)
        return NULL;
    return world_get_player_by_id(server, id);
}

bool gui_cmd_tile_info(server_t *server, int sock, void *arg)
{
    vec2_t pos = {0};
    char **args = arg;

    if (!server || !args)
        return false;
    pos.x = atoi(args[0]);
    pos.y = atoi(args[1]);
    if (pos.x < 0 || pos.y < 0 || pos.x >= server->world.size.x
        || pos.y >= server->world.size.y)
        return false;
    return gui_send_tile_info(server, sock, &pos);
}

bool gui_cmd_player_pos(server_t *server, int sock, void *arg)
{
    if (!server || !arg)
        return false;
    return gui_send_player_pos(server, sock, player_from_id(server, arg));
}

bool gui_cmd_player_level(server_t *server, int sock, void *arg)
{
    if (!server || !arg)
        return false;
    return gui_send_player_level(server, sock, player_from_id(server, arg));
}

bool gui_cmd_player_inv(server_t *server, int sock, void *arg)
{
    if (!server || !arg)
        return false;
    return gui_send_player_inv(server, sock, player_from_id(server, arg));
}

bool gui_cmd_set_time_unit(server_t *server, int sock, void *arg)
{
    char buf[16];
    int freq = 0;
    char **args = arg;

    if (!server || !args)
        return false;
    memset(buf, 0, sizeof(buf));
    freq = atoi(args[0]);
    if (freq <= 0)
        return false;
    return gui_set_time_unit(server, sock, &freq);
}
