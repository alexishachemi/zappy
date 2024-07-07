/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world_team
*/

#include <string.h>
#include "world.h"
#include "gui.h"

bool world_add_team(server_t *server, const char *name)
{
    team_t *team = NULL;

    if (!server || !name || strcmp(name, GUI_TEAM) == 0)
        return false;
    team = team_create(name);
    if (!team)
        return false;
    if (!list_add_ptr(&server->world.teams, team)) {
        team_destroy(team);
        return false;
    }
    return TRUE_SLOG(server, INFO, "Team %s has been added", name);
}

bool world_add_teams(server_t *server, list_t *names)
{
    char *name = NULL;

    if (!server || !names)
        return false;
    for (node_t *node = names->head; node; node = node->next) {
        name = node->data;
        if (!world_add_team(server, name))
            return false;
    }
    return true;
}

int world_get_team_id(server_t *server, const char *name)
{
    team_t *team = NULL;

    if (!server || !name)
        return false;
    for (node_t *node = server->world.teams.head; node; node = node->next) {
        team = node->data;
        if (!strcmp(team->name, name))
            return team->id;
    }
    return -1;
}

char *world_get_team_name(server_t *server, size_t id)
{
    team_t *team = NULL;

    if (!server)
        return false;
    for (node_t *node = server->world.teams.head; node; node = node->next) {
        team = node->data;
        if (team->id == id)
            return team->name;
    }
    return NULL;
}
