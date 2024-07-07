/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_player
*/

#include "server.h"
#include "gui.h"

static void broadcast_player_add(server_t *server, player_t *player,
    egg_t *egg)
{
    if (egg->layer)
        gui_broadcast_event(server, gui_send_player_from_egg, egg);
    gui_broadcast_event(server, gui_send_new_player, player);
}

player_t *world_add_player_from_egg(server_t *server, int sock, egg_t *egg)
{
    player_t *player = NULL;

    if (!server || sock < 0 || !egg)
        return NULL;
    player = list_add(&server->world.players, (allocator_t)create_player);
    if (!player)
        return NULL;
    player->sock = sock;
    player->direction = egg->direction;
    player->position = egg->position;
    player->team_id = egg->team_id;
    broadcast_player_add(server, player, egg);
    SLOG(server, INFO, "Player %ld hatched from egg %ld", player->id, egg->id);
    if (!world_move_player(server, player, player->position)
        || !world_remove_egg(server, egg->position, egg->team_id)) {
        list_remove_free(&server->world.players, -1);
        return NULL;
    }
    return player;
}

static int get_random_team_egg(server_t *server, size_t team_id, egg_t **egg)
{
    size_t count = 0;
    size_t random = 0;
    world_t *world = &server->world;

    count = egg_count_from_team(&world->eggs, team_id);
    if (count == 0)
        return -1;
    random = rand() % count;
    for (size_t i = 0; i < list_size(&world->eggs); i++) {
        *egg = list_at(&world->eggs, i);
        if ((*egg)->team_id == team_id && random == 0)
            return i;
        if ((*egg)->team_id == team_id)
            random--;
    }
    return -1;
}

player_t *world_add_player(server_t *server, int sock, int team_id)
{
    int egg_index = -1;
    egg_t *egg = NULL;

    if (!server || sock < 0 || team_id < 0)
        return NULL;
    egg_index = get_random_team_egg(server, team_id, &egg);
    if (egg_index == -1)
        return NULL;
    return world_add_player_from_egg(server, sock, egg);
}

static int find_player_in_tile(tile_t *tile, int sock)
{
    player_t *player = NULL;

    for (size_t i = 0; i < list_size(&tile->players); i++) {
        player = list_at(&tile->players, i);
        if (player->sock == sock)
            return i;
    }
    return -1;
}

static bool move_from_tiles(tile_t *from, tile_t *to, player_t *player)
{
    int player_index = -1;

    player_index = find_player_in_tile(from, player->sock);
    if (player_index != -1)
        return list_move(&from->players, player_index, &to->players);
    return list_add_ptr(&to->players, player);
}

bool world_move_player(server_t *server, player_t *player, vec2_t to)
{
    tile_t *from_tile = NULL;
    tile_t *to_tile = NULL;

    if (!server || !server->world.map || !player)
        return false;
    to = world_wrap_pos(to, server->world.size);
    from_tile = world_get_tile(server, player->position);
    to_tile = world_get_tile(server, to);
    if (!from_tile || !to_tile
        || !move_from_tiles(from_tile, to_tile, player))
        return false;
    player->position = to;
    return true;
}
