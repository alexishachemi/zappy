/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player_handle
*/

#include <string.h>
#include <ncurses.h>
#include "player.h"
#include "utils.h"
#include "server.h"

static void append_item(char **str, const char *name, size_t nb)
{
    char buf[32];

    if (!str || !name)
        return;
    memset(buf, 0, 32);
    if (*str && strlen(*str) > 1 && !strmcat(str, ", ")) {
        *str = NULL;
        return;
    }
    snprintf(buf, 32, "%s %ld", name, nb);
    if (!strmcat(str, buf))
        *str = NULL;
}

static char *items_to_string(inventory_t *inv)
{
    char *str = NULL;

    if (!inv)
        return NULL;
    str = strdup("");
    append_item(&str, "food", inv->food);
    append_item(&str, "linemate", inv->linemate);
    append_item(&str, "deraumere", inv->deraumere);
    append_item(&str, "sibur", inv->sibur);
    append_item(&str, "mendiane", inv->mendiane);
    append_item(&str, "phiras", inv->phiras);
    append_item(&str, "thystame", inv->thystame);
    return str;
}

char *player_items_to_string(inventory_t *items)
{
    char *inv_str = NULL;
    char *str = NULL;

    inv_str = items_to_string(items);
    if (!inv_str)
        return NULL;
    str = strmcat(&str, "[");
    if (!str) {
        free(inv_str);
        return NULL;
    }
    str = strmcat(&str, inv_str);
    free(inv_str);
    if (!str)
        return NULL;
    return strmcat(&str, "]");
}

void player_print(player_t *p)
{
    printw(
        "Player %d | lives %ld | hunger %ld | level %ld "
        "| pos (%d,%d) | dir (%d,%d)\n",
        p->sock, p->lives, p->hunger, p->level, p->position.x, p->position.y,
        p->direction.x, p->direction.y
    );
    printw("    ");
    inventory_print(&p->inventory);
    printw("    ");
    if (p->elevation_status != ELEV_NONE)
        printw("(Elevating) ");
    if (!job_print_array(p->jobs))
        printw("\n");
    printw("\n");
}

void player_update(server_t *server)
{
    list_apply(&server->world.players,
        (applicator_t)player_update_jobs, server);
    list_apply(&server->world.players,
        (applicator_t)player_update_hunger, server);
}
