/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** egg
*/

#pragma once

#include <stdlib.h>
#include "vec2.h"
#include "player.h"

typedef struct {
    bool is_initial;
    size_t id;
    const player_t *layer;
    size_t team_id;
    vec2_t position;
    vec2_t direction;
} egg_t;

egg_t *egg_create(size_t team_id, vec2_t position);
egg_t *egg_create_random(size_t team_id, vec2_t size);
egg_t *egg_create_from_player(const player_t *player);
size_t egg_count_from_team(list_t *eggs, size_t team_id);
void egg_print(egg_t *egg);
