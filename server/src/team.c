/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team
*/

#include <string.h>
#include "team.h"

team_t *team_create(const char *name)
{
    static size_t id = 0;
    team_t *team = NULL;

    team = malloc(sizeof(team_t));
    if (!team)
        return NULL;
    team->id = id;
    id++;
    team->name = strdup(name);
    if (!team->name) {
        free(team);
        return NULL;
    }
    return team;
}

void team_destroy(team_t *team)
{
    if (!team)
        return;
    if (team->name)
        free(team->name);
    free(team);
}
