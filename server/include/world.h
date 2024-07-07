/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#pragma once

#include "linked.h"
#include "inventory.h"
#include "player.h"
#include "vec2.h"
#include "egg.h"
#include "team.h"
#include "tile.h"

#define RESSOURCE_SPAWN_RATE 20

typedef struct {
    item_t item;
    float density;
} item_density_t;

typedef item_density_t item_density_list_t[ITEMS_TYPES];

typedef struct {
    tile_t **map;
    vec2_t size;
    list_t teams;
    list_t players;
    list_t eggs;
    inventory_t spawn_map;
    unsigned int spawn_timer;
    unsigned int freq;
} world_t;


bool world_init(server_t *server, vec2_t size, const item_density_list_t map);
void world_deinit(server_t *server);

vec2_t world_wrap_pos(vec2_t pos, vec2_t size);
tile_t *world_get_tile(server_t *server, vec2_t pos);
tile_t *world_get_random_tile(server_t *server, vec2_t *pos_buf);

player_t *world_get_player(server_t *server, int sock);
player_t *world_get_player_by_id(server_t *server, size_t id);

player_t *world_add_player_from_egg(server_t *server, int sock, egg_t *egg);
player_t *world_add_player(server_t *server, int sock, int team_id);
bool world_move_player(server_t *server, player_t *player, vec2_t to);
bool world_remove_player(server_t *server, int sock);

bool world_add_egg_from_player(server_t *server, player_t *player);
bool world_add_egg_randomly(server_t *server, size_t team_id);
bool world_remove_tile_eggs(server_t *server, tile_t *tile);
bool world_remove_egg(server_t *server, vec2_t pos, size_t team_id);
bool world_add_eggs_per_team(server_t *server, size_t nb);

void world_print_map(server_t *server);

bool world_add_team(server_t *server, const char *name);
bool world_add_teams(server_t *server, list_t *names);
int world_get_team_id(server_t *server, const char *name);
char *world_get_team_name(server_t *server, size_t id);

bool world_update(server_t *server);
bool world_set_freq(server_t *server, int freq);

int world_get_direction(server_t *server, vec2_t from, vec2_t to, vec2_t up);

inventory_t world_count_items(const server_t *server);
bool world_spawn_item(server_t *server, item_t item, size_t nb,
    list_t *tiles_buf);
bool world_set_item_density(server_t *server, item_t item, float density);
bool world_set_items_density(server_t *server, const item_density_list_t map);
bool world_spawn_ressources(server_t *server);

char *world_get_vision_str(
    server_t *server, vec2_t pos, vec2_t dir, size_t dist);
