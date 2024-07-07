/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** list_utils
*/

#include <stdbool.h>
#include "player.h"

bool ptr_eq(void *p1, void *p2)
{
    return p1 == p2;
}

bool int_eq(void *a, void *b)
{
    return *(int *)a == *(int *)b;
}

bool player_id_eq(void *player, void *id)
{
    return ((player_t *)player)->id == *(size_t *)id;
}

bool player_sock_eq(void *player, void *sock)
{
    return ((player_t *)player)->sock == *(int *)sock;
}
