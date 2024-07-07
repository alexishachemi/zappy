/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** handle_arg.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "linked.h"
#include "arg.h"

static void init_arg_flag(argm_t *arg_manager)
{
    argm_expect_list(arg_manager, "-p");
    argm_expect_list(arg_manager, "-x");
    argm_expect_list(arg_manager, "-y");
    argm_expect_list(arg_manager, "-n");
    argm_expect_list(arg_manager, "-c");
    argm_expect_list(arg_manager, "-f");
}

static void init_port_argument(argm_t *arg_manager)
{
    const arg_t *port_arg = NULL;
    int port = 0;

    port_arg = argm_get(arg_manager, "-p");
    if (port_arg) {
        port = arg_as_int(port_arg);
        printf("Port: %d\n", port);
    }
}

static void init_width_argument(argm_t *arg_manager)
{
    const arg_t *width_arg = NULL;
    int width = 0;

    width_arg = argm_get(arg_manager, "-x");
    if (width_arg) {
        width = arg_as_int(width_arg);
        printf("Width: %d\n", width);
    }
}

static void init_height_argument(argm_t *arg_manager)
{
    const arg_t *height_arg = NULL;
    int height = 0;

    height_arg = argm_get(arg_manager, "-y");
    if (height_arg) {
        height = arg_as_int(height_arg);
        printf("Height: %d\n", height);
    }
}

static void init_team_argument(argm_t *arg_manager)
{
    const arg_t *team_arg = NULL;
    list_t teams;

    team_arg = argm_get(arg_manager, "-n");
    if (team_arg) {
        list_init(&teams);
        arg_as_list(team_arg, &teams);
        printf("Teams:\n");
        for (node_t *node = teams.head; node; node = node->next) {
            printf("  - %s\n", (char *)node->data);
        }
        list_clear(&teams, free);
    }
}

static void init_client_argument(argm_t *arg_manager)
{
    const arg_t *clients_arg = NULL;
    int clients = 0;

    clients_arg = argm_get(arg_manager, "-c");
    if (clients_arg) {
        clients = arg_as_int(clients_arg);
        printf("Clients per team: %d\n", clients);
    }
}

static void init_freq_argument(argm_t *arg_manager)
{
    const arg_t *freq_arg = NULL;
    int freq = 0;

    freq_arg = argm_get(arg_manager, "-f");
    if (freq_arg) {
        freq = arg_as_int(freq_arg);
        printf("Frequency: %d\n", freq);
    }
}

bool get_args(argm_t *arg_manager, const char **args, const int nb_arg)
{
    argm_init(arg_manager);
    init_arg_flag(arg_manager);
    if (!argm_parse(arg_manager, nb_arg, args)) {
        fprintf(stderr, "Error: Failed to parse arguments\n");
        return false;
    }
    init_port_argument(arg_manager);
    init_width_argument(arg_manager);
    init_height_argument(arg_manager);
    init_team_argument(arg_manager);
    init_client_argument(arg_manager);
    init_freq_argument(arg_manager);
    list_clear(&arg_manager->args, free);
    list_clear(&arg_manager->list_expect, free);
    return true;
}
