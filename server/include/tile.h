/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** tile
*/

#pragma once

#include "player.h"

struct tile_s {
    vec2_t position;
    list_t players;
    list_t eggs;
    inventory_t inventory;
};

typedef struct {
    size_t target_level;
    size_t players;
    inventory_t ressources;
} elev_requirements_t;

void tile_init(tile_t *tile, vec2_t position);
void tile_deinit(tile_t *tile);

char *tile_to_string(tile_t *tile);
void tile_eject(server_t *server, player_t *emitter, tile_t *tile);
bool tile_can_elevate(tile_t *tile, player_t *host);
bool tile_remove_elev_ressources(tile_t *tile, size_t target_level);
