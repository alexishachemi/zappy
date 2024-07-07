/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server-side server/gui communication
*/

#pragma once

#include "server.h"

#define GUI_TEAM "GRAPHIC"

typedef bool (*gui_callback_t)(server_t *, int, void *);

typedef struct {
    const char *name;
    unsigned int expected_args;
    gui_callback_t callback;
} gui_command_t;

bool gui_send_current_state(server_t *server, int sock);
void gui_send_bad_arg(server_t *server, int sock);
void gui_send_unknown_cmd(server_t *server, int sock);

void gui_process_command(server_t *server, int sock, char *str);

void gui_broadcast_event(server_t *server, gui_callback_t callback, void *arg);

// Commmands

bool gui_send_new_player(server_t *server, int sock, void *arg);// player_t
bool gui_send_expulsion(server_t *server, int sock, void *arg); // player_t
bool gui_send_broadcast(server_t *server, int sock, void *arg); //broadcaster_t

bool gui_send_elev_start(server_t *server, int sock, void *arg); // player_t
bool gui_send_elev_end(server_t *server, int sock, void *arg); // elev_result_t

bool gui_send_egg_lay_start(server_t *server, int sock, void *arg); // player_t
bool gui_send_egg_lay_end(server_t *server, int sock, void *arg); // egg_t
bool gui_send_player_from_egg(server_t *server, int sock, void *arg); // egg_t
bool gui_send_egg_death(server_t *server, int sock, void *arg); // egg_t

bool gui_send_drop(server_t *server, int sock, void *arg); // obj_interact_t
bool gui_send_collect(server_t *server, int sock, void *arg); // obj_interact_t

bool gui_send_player_death(server_t *server, int sock, void *arg); // player_t
bool gui_send_game_end(server_t *server, int sock, void *arg); // char
bool gui_send_message(server_t *server, int sock, void *arg); // char

bool gui_send_map_size(server_t *server, int sock, void *arg); // NULL
bool gui_send_tile_info(server_t *server, int sock, void *arg); // tile_t
bool gui_send_map_info(server_t *server, int sock, void *arg); // NULL

bool gui_send_teams_name(server_t *server, int sock, void *arg); // NULL
bool gui_send_player_pos(server_t *server, int sock, void *arg); // player_t
bool gui_send_player_level(server_t *server, int sock, void *arg); // player_t
bool gui_send_player_inv(server_t *server, int sock, void *arg); // player_t

bool gui_send_time_unit(server_t *server, int sock, void *arg); // NULL
bool gui_set_time_unit(server_t *server, int sock, void *arg); // int

// callable by gui

bool gui_cmd_tile_info(server_t *server, int sock, void *arg); // char *
bool gui_cmd_player_pos(server_t *server, int sock, void *arg); // char *
bool gui_cmd_player_level(server_t *server, int sock, void *arg); // char *
bool gui_cmd_player_inv(server_t *server, int sock, void *arg); // char *
bool gui_cmd_set_time_unit(server_t *server, int sock, void *arg); // char *
