/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team
*/

#pragma once

#include <stdlib.h>

#define TEAM_MAXED_REQUIRED 6

typedef struct {
    size_t id;
    char *name;
} team_t;

team_t *team_create(const char *name);
void team_destroy(team_t *team);
