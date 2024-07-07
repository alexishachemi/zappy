/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands and jobs
*/

#pragma once
#include <stdbool.h>

#define MAX_JOBS 10

typedef struct server_s server_t;
typedef struct player_s player_t;
typedef struct job_data_s job_data_t;

typedef void (*job_callback_t)(server_t *, player_t *, const char *, void *);
typedef bool (*job_check_t)(server_t *, player_t *, const char *, void *);
typedef bool (*job_builder_t)(server_t *, player_t *, job_data_t *);

struct job_data_s {
    bool check_first;
    job_check_t check;
    job_callback_t start;
    job_callback_t sucess;
    job_callback_t failure;
    char *arg;
    void *data;
};

typedef struct {
    bool started;
    bool enabled;
    int priority;
    unsigned int f;
    job_data_t jdata;
    const char *name;
} job_t;

typedef struct {
    const char *name;
    unsigned int f;
    bool has_arg;
    job_builder_t build_job;
} command_t;

bool job_build(server_t *server, player_t *player,
    const char *cmd_str, job_t *job_buf);

bool job_print_array(job_t *jobs);

// Builders

bool job_build_forward(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_left(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_right(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_inventory(server_t *server, player_t *player,
    job_data_t *jdata);
bool job_build_nb_team_slot(server_t *server, player_t *player,
    job_data_t *jdata);
bool job_build_broadcast(server_t *server, player_t *player,
    job_data_t *jdata);
bool job_build_fork(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_eject(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_incantation(server_t *server, player_t *player,
    job_data_t *jdata);
bool job_build_take(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_set(server_t *server, player_t *player, job_data_t *jdata);
bool job_build_look(server_t *server, player_t *player, job_data_t *jdata);
