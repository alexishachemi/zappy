/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_move
*/

#include "gui.h"
#include "server.h"

void player_right(server_t *server, player_t *player)
{
    if (!server || !player)
        return;
    player->direction = vec2_rotate_dir_right(player->direction);
    gui_broadcast_event(server, gui_send_player_pos, player);
}

void player_left(server_t *server, player_t *player)
{
    if (!server || !player)
        return;
    player->direction = vec2_rotate_dir_left(player->direction);
    gui_broadcast_event(server, gui_send_player_pos, player);
}

void player_forward(server_t *server, player_t *player)
{
    if (!server || !player)
        return;
    world_move_player(server, player,
        vec2_add(player->position, player->direction));
    gui_broadcast_event(server, gui_send_player_pos, player);
}
