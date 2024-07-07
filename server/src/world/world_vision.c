/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_vision
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static void safe_free(void **data_ptr)
{
    if (data_ptr && *data_ptr) {
        free(*data_ptr);
        *data_ptr = NULL;
    }
}

static bool append_tile_failure(char **str, char *tile_str)
{
    safe_free((void **)str);
    if (tile_str)
        free(tile_str);
    return false;
}

static char *get_prefix(char **str, char *tile_str, char *buf, bool is_first)
{
    memset(buf, 0, 4);
    if (is_first) {
        *str = strdup("");
        return str ? buf : NULL;
    }
    if (!tile_str || strlen(tile_str) == 0)
        return strcpy(buf, ",");
    return strcpy(buf, ", ");
}

static bool append_tile(char **str, tile_t *tile, bool is_first)
{
    char buf[4];
    char *tile_str = NULL;
    bool status = false;

    if (!str || !tile)
        return append_tile_failure(str, tile_str);
    tile_str = tile_to_string(tile);
    if (!tile_str)
        return append_tile_failure(str, tile_str);
    if (!strmcat(str, get_prefix(str, tile_str, buf, is_first)))
        return append_tile_failure(str, tile_str);
    status = strmcat(str, tile_str);
    free(tile_str);
    return status;
}

static char *line_to_str(server_t *server, vec2_t pos, vec2_t right, size_t nb)
{
    char *str = NULL;
    bool is_first = nb <= 1;

    while (nb) {
        if (!append_tile(&str, world_get_tile(server, pos), is_first))
            return NULL;
        pos = world_wrap_pos(vec2_add(pos, right), server->world.size);
        nb--;
        is_first = false;
    }
    return str;
}

static char *get_vision_failure(char *str, char *line)
{
    if (str)
        free(str);
    if (line)
        free(line);
    return NULL;
}

static char *add_list_prefix(char *str)
{
    char *list_str = NULL;

    if (!str)
        return NULL;
    list_str = strdup("[");
    if (!list_str || !strmcat(&list_str, str)) {
        free(str);
        return NULL;
    }
    free(str);
    return strmcat(&list_str, "]");
}

char *world_get_vision_str(server_t *server, vec2_t pos,
    vec2_t dir, size_t dist)
{
    char *str = NULL;
    char *line = NULL;
    vec2_t right = {0};
    vec2_t left = {0};
    vec2_t top_left = {0};

    right = vec2_rotate_dir_right(dir);
    left = vec2_rotate_dir_left(dir);
    for (size_t i = 0; i <= dist; i++) {
        top_left = pos;
        for (size_t j = 0; j < i; j++)
            top_left = vec2_add(top_left, vec2_add(dir, left));
        line = line_to_str(server, top_left, right, i == 0 ? 1 : i * 2 + 1);
        if (!line || !strmcat(&str, line))
            return get_vision_failure(str, line);
        safe_free((void **)(&line));
    }
    return add_list_prefix(str);
}
