/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-alexis.hachemi
** File description:
** player.h
*/

#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "inventory.h"
#include "vec2.h"
#include "job.h"
#include "linked.h"

#define PLAYER_LIVES 10
#define PLAYER_HUNGER 126
#define PLAYER_BASE_LEVEL 1
#define PLAYER_MAX_LEVEL 8

typedef struct tile_s tile_t;

typedef enum {
    ELEV_NONE,
    ELEV_HOST,
    ELEV_MEMB
} elevation_status_t;

typedef struct {
    player_t *host;
    bool success;
} elevation_result_t;

typedef struct {
    player_t *player;
    item_t item;
} object_interact_t;

struct player_s {
    size_t id;
    int sock;
    size_t team_id;
    size_t lives;
    size_t hunger;
    size_t level;
    inventory_t inventory;
    vec2_t direction;
    vec2_t position;
    job_t jobs[MAX_JOBS];
    elevation_status_t elevation_status;
    list_t elevation_list;
};

// init

void init_player(player_t *player);
player_t *create_player(void);

// handle

char *player_items_to_string(inventory_t *items);
void player_print(player_t *player);
void player_update_hunger(server_t *server, player_t *player);
void player_update(server_t *server);

// job

void player_update_jobs(server_t *server, player_t *player);
void player_schedule_job(server_t *server, player_t *player, const char *msg);

// movement

void player_forward(server_t *server, player_t *player);
void player_left(server_t *server, player_t *player);
void player_right(server_t *server, player_t *player);

// elevation

bool player_setup_elevation(server_t *server, player_t *player, tile_t *tile);
bool player_cancel_elevation(server_t *server, player_t *player);
bool player_elevate(server_t *server, player_t *player);
