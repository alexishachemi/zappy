/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include "clogger.h"

#define UNUSED __attribute__((unused))
#define SPRE "[SERVER] "
#define SLOG(s, lvl, f...) (LOG(&s->net.logger, lvl, SPRE f))
#define FALSE_SLOG(s, lvl, f...) (LOG_FALSE(&s->net.logger, lvl, SPRE f))
#define TRUE_SLOG(s, lvl, f...) (LOG_TRUE(&s->net.logger, lvl, SPRE f))
#define NULL_SLOG(s, lvl, f...) (LOG_NULL(&ns->net.logger, lvl, SPRE f))

char *strmcat(char **dest_ptr, const char *src);
bool ptr_eq(void *p1, void *p2);
bool int_eq(void *a, void *b);
bool player_id_eq(void *player, void *id);
bool player_sock_eq(void *player, void *sock);
