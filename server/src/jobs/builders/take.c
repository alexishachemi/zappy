/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** take
*/

#include "server.h"
#include "utils.h"
#include "gui.h"

static void take(server_t *server, player_t *player, const char *arg,
    void *data)
{
    tile_t *tile = data;
    object_interact_t itr = {.player = player, .item = ERR_ITEM};

    itr.item = item_from_string(arg);
    gui_broadcast_event(server, gui_send_collect, &itr);
    inventory_move(&tile->inventory, &player->inventory, arg, 1);
    nets_send(&server->net, player->sock, "ok");
}

static void take_fail(server_t *server, player_t *player,
    UNUSED const char *arg, UNUSED void *data)
{
    nets_send(&server->net, player->sock, "ko");
}

static bool can_take(UNUSED server_t *server, UNUSED player_t *player,
    const char *arg, void *data)
{
    tile_t *tile = data;
    size_t *item_ptr = NULL;

    item_ptr = inventory_index(&tile->inventory, arg);
    return item_ptr != NULL && *item_ptr > 0;
}

bool job_build_take(server_t *server, player_t *player, job_data_t *jdata)
{
    if (!server || !player || !jdata)
        return false;
    jdata->check_first = false;
    jdata->data = world_get_tile(server, player->position);
    jdata->check = can_take;
    jdata->failure = take_fail;
    jdata->sucess = take;
    return jdata->data != NULL;
}
