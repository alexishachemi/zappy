/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** egg
*/

#include <string.h>
#include <ncurses.h>
#include "linked.h"
#include "egg.h"

static const vec2_t directions[] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

static egg_t *alloc_egg(void)
{
    egg_t *egg = NULL;

    egg = malloc(sizeof(egg_t));
    if (egg)
        memset(egg, 0, sizeof(egg_t));
    return egg;
}

egg_t *egg_create(size_t team_id, vec2_t position)
{
    static size_t id = 0;
    egg_t *egg = NULL;

    egg = alloc_egg();
    if (!egg)
        return NULL;
    egg->layer = NULL;
    egg->id = id;
    egg->team_id = team_id;
    egg->position = position;
    egg->direction = directions[rand() % 4];
    id++;
    return egg;
}

egg_t *egg_create_random(size_t team_id, vec2_t size)
{
    vec2_t position = {0};
    egg_t *egg = NULL;

    if (!(size.x > 0 && size.y > 0))
        return NULL;
    position.x = rand() % size.x;
    position.y = rand() % size.y;
    egg = egg_create(team_id, position);
    return egg;
}

egg_t *egg_create_from_player(const player_t *player)
{
    egg_t *egg = NULL;

    if (!player)
        return NULL;
    egg = egg_create(player->team_id, player->position);
    if (egg)
        egg->layer = player;
    return egg;
}

size_t egg_count_from_team(list_t *eggs, size_t team_id)
{
    size_t count = 0;
    egg_t *egg = NULL;

    for (node_t *n = eggs->head; n; n = n->next) {
        egg = n->data;
        if (egg->team_id == team_id)
            count++;
    }
    return count;
}

void egg_print(egg_t *egg)
{
    if (!egg)
        return;
    printw("Egg | pos (%d,%d) | dir (%d,%d)\n",
        egg->position.x, egg->position.y, egg->direction.x, egg->direction.y);
}
