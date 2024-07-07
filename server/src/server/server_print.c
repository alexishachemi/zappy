/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_print
*/

#include <ncurses.h>
#include <string.h>
#include "server.h"

static void print_player(team_t *t, player_t *p)
{
    if (p->team_id != t->id)
        return;
    player_print(p);
}

static void count_players(world_t *world, size_t team_id, int *count)
{
    player_t *p = NULL;

    for (node_t *n = world->players.head; n; n = n->next) {
        p = n->data;
        if (p->team_id == team_id)
            count[p->level - 1]++;
    }
}

static size_t count_eggs(world_t *world, size_t team_id)
{
    size_t count = 0;
    egg_t *e = NULL;

    for (node_t *n = world->eggs.head; n; n = n->next) {
        e = n->data;
        count += e->team_id == team_id;
    }
    return count;
}

static void print_team_compact(world_t *world, team_t *t)
{
    int count[PLAYER_MAX_LEVEL];

    memset(count, 0, sizeof(count));
    count_players(world, t->id, count);
    printw("\n[%s]\n", t->name);
    printw("players: [%s: %d", "1", count[0]);
    for (int i = 2; i <= PLAYER_MAX_LEVEL; i++)
        printw(", %d: %d", i, count[i - 1]);
    printw("]\n");
    printw("eggs: %ld\n", count_eggs(world, t->id));
}

static void print_eggs(team_t *t, egg_t *e)
{
    if (e->team_id != t->id)
        return;
    egg_print(e);
}

static void print_team(world_t *world, team_t *team)
{
    size_t count = 0;

    for (node_t *n = world->players.head;
        n && count < TEAM_MAXED_REQUIRED; n = n->next) {
        count += ((player_t *)n->data)->team_id == team->id;
    }
    if (count > TEAM_MAXED_REQUIRED) {
        print_team_compact(world, team);
        return;
    }
    printw("\n[%s]\n\n", team->name);
    list_apply(&world->players, (applicator_t)print_player, team);
    list_apply(&world->eggs, (applicator_t)print_eggs, team);
    printw("\n");
}

void server_print(server_t *server)
{
    inventory_t ressources = {0};

    if (!server || !server->display)
        return;
    ressources = world_count_items(server);
    refresh();
    erase();
    printw("///////////// SERVER /////////////\n\n");
    printw("Step: %ld\n", server->step);
    printw("Port: %d\n", server->net.port);
    printw("Frequency: %d\n", server->world.freq);
    printw("Ressources: ");
    inventory_print(&ressources);
    printw("Teams:\n");
    list_apply(&server->world.teams, (applicator_t)print_team, &server->world);
    printw("\n/////////////////////////////////\n");
    doupdate();
}
