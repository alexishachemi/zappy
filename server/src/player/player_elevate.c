/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_elevate
*/

#include <string.h>
#include "world.h"
#include "gui.h"

static void apply_elevation_setup(player_t *host, player_t *participant)
{
    if (participant == host
        || participant->elevation_status != ELEV_NONE
        || participant->level != host->level)
        return;
    list_add_ptr(&host->elevation_list, participant);
    participant->elevation_status = ELEV_MEMB;
}

bool player_setup_elevation(server_t *server, player_t *player, tile_t *tile)
{
    if (!player || !tile)
        return false;
    list_apply(&tile->players, (applicator_t)apply_elevation_setup, player);
    player->elevation_status = ELEV_HOST;
    gui_broadcast_event(server, gui_send_elev_start, player);
    return true;
}

static void apply_elevation(server_t *server, player_t *player)
{
    char buf[32];

    memset(buf, 0, 32);
    player->elevation_status = ELEV_NONE;
    player->level++;
    snprintf(buf, 32, "Current level: %ld", player->level);
    if (!server)
        return;
    gui_broadcast_event(server, gui_send_player_level, player);
    nets_send(&server->net, player->sock, buf);
}

bool player_elevate(server_t *server, player_t *player)
{
    elevation_result_t result = {.host = player, .success = true};

    if (!player || player->elevation_status != ELEV_HOST)
        return false;
    gui_broadcast_event(server, gui_send_elev_end, &result);
    apply_elevation(server, player);
    list_apply(&player->elevation_list, (applicator_t)apply_elevation, server);
    list_clear(&player->elevation_list, NULL);
    server_check_win(server);
    return true;
}

static void apply_elevation_cancel(server_t *server, player_t *player)
{
    if (server)
        nets_send(&server->net, player->sock, "ko");
    player->elevation_status = ELEV_NONE;
}

bool player_cancel_elevation(server_t *server, player_t *player)
{
    elevation_result_t result = {.host = player, .success = false};

    if (!player || player->elevation_status != ELEV_HOST)
        return false;
    apply_elevation_cancel(server, player);
    list_apply(&player->elevation_list,
        (applicator_t)apply_elevation_cancel, server);
    list_clear(&player->elevation_list, NULL);
    gui_broadcast_event(server, gui_send_elev_end, &result);
    return true;
}
