/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#pragma once

#include "socknet.h"
#include "world.h"
#include "utils.h"

typedef long long time_ms_t;

typedef struct {
    server_t *server;
    player_t *emitter;
    vec2_t new_pos;
} ejector_t;

typedef struct {
    server_t *server;
    player_t *emitter;
    const char *msg;
} broadcaster_t;

struct server_s {
    bool enabled;
    net_t net;
    world_t world;
    bool display;
    bool god_mode;
    size_t step;
    list_t player_clients;
    list_t playerless_clients;
    list_t graphical_clients;
    list_t dead_clients;
};

bool server_init(server_t *server, int ac, const char **av);
void server_deinit(server_t *server);
void server_print(server_t *server);
int server_update(server_t *server);
void server_check_win(server_t *server);

void server_handle_clients(server_t *server);

bool server_sock_has_player(server_t *server, int sock);
void server_remove_client(server_t *server, int sock);
bool server_add_playerless(server_t *server, int sock);
bool server_try_add_player(server_t *server, int sock, const char *team_name);
bool server_try_add_gui(server_t *server, int sock, const char *team_name);

bool server_broadcast(server_t *server, player_t *emitter, const char *msg);
bool server_kill_player(server_t *server, int sock);
bool server_kick_dead(server_t *server);
