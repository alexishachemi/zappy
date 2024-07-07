/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** vec2_rotate
*/

#include <stdlib.h>
#include "vec2.h"

static const direction_map_t dir_map[] = {
    {1, {0, 1}},
    {2, {-1, 1}},
    {3, {-1, 0}},
    {4, {-1, -1}},
    {5, {0, -1}},
    {6, {1, -1}},
    {7, {1, 0}},
    {8, {1, 1}},
};

static const id_map_t id_map[] = {
    {{0, 1}, {1, 2, 3, 4, 5, 6, 7, 8}},
    {{1, 0}, {3, 4, 5, 6, 7, 8, 1, 2}},
    {{0, -1}, {5, 6, 7, 8, 1, 2, 3, 4}},
    {{-1, 0}, {7, 8, 1, 2, 3, 4, 5, 6}},
};

int vec2_direction_to_id(vec2_t direction)
{
    for (int i = 0; i < 8; i++) {
        if (vec2_eq(dir_map[i].direction, direction))
            return dir_map[i].id;
    }
    return 0;
}

static int convert_id(const int id, const int *from, const int *to)
{
    for (int i = 0; i < 8; i++) {
        if (from[i] == id)
            return to[i];
    }
    return 0;
}

static const id_map_t *get_id_map(vec2_t up)
{
    for (int i = 0; i < 4; i++) {
        if (vec2_eq(id_map[i].up, up))
            return id_map + i;
    }
    return NULL;
}

int vec2_rotate_id(unsigned int id, vec2_t current_up, vec2_t desired_up)
{
    const id_map_t *from = NULL;
    const id_map_t *to = NULL;

    from = get_id_map(current_up);
    to = get_id_map(desired_up);
    if (!from || !to)
        return -1;
    return convert_id(id, from->ids, to->ids);
}

vec2_t vec2_rotate_dir_left(vec2_t a)
{
    if (a.x == 0 && a.y == 1)
        return ((vec2_t){-1, 0});
    if (a.x == -1 && a.y == 0)
        return ((vec2_t){0, -1});
    if (a.x == 0 && a.y == -1)
        return ((vec2_t){1, 0});
    return ((vec2_t){0, 1});
}

vec2_t vec2_rotate_dir_right(vec2_t a)
{
    if (a.x == 0 && a.y == 1)
        return ((vec2_t){1, 0});
    if (a.x == 1 && a.y == 0)
        return ((vec2_t){0, -1});
    if (a.x == 0 && a.y == -1)
        return ((vec2_t){-1, 0});
    return ((vec2_t){0, 1});
}

int vec2_dir_to_gui_orientation(vec2_t vec)
{
    if (vec2_eq(vec, VEC2_UP))
        return 1;
    if (vec2_eq(vec, VEC2_RIGHT))
        return 2;
    if (vec2_eq(vec, VEC2_DOWN))
        return 3;
    if (vec2_eq(vec, VEC2_LEFT))
        return 4;
    return -1;
}
