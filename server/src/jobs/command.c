/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** command
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static const command_t commands[] = {
    {"Forward", 7, false, job_build_forward},
    {"Left", 7, false, job_build_left},
    {"Right", 7, false, job_build_right},
    {"Look", 7, false, job_build_look},
    {"Inventory", 1, false, job_build_inventory},
    {"Broadcast", 7, true, job_build_broadcast},
    {"Connect_nbr", 0, false, job_build_nb_team_slot},
    {"Fork", 42, false, job_build_fork},
    {"Eject", 7, false, job_build_eject},
    {"Take", 7, true, job_build_take},
    {"Set", 7, true, job_build_set},
    {"Incantation", 300, false, job_build_incantation},
    {NULL, 0, false, NULL}
};

static bool set_arg(char **buf, const char *cmd_str,
    size_t cmd_size, const command_t *cmd)
{
    size_t size = 0;

    size = strlen(cmd_str);
    if (!cmd->has_arg) {
        *buf = NULL;
        return size == cmd_size;
    }
    if (cmd_str[cmd_size] != ' ' || cmd_str[cmd_size + 1] == 0)
        return false;
    *buf = strdup(cmd_str + cmd_size + 1);
    return *buf != NULL;
}

bool job_build(server_t *server, player_t *player,
    const char *cmd_str, job_t *job_buf)
{
    const command_t *cmd = NULL;
    size_t cmd_size = 0;

    if (!cmd_str || !job_buf)
        return false;
    for (int i = 0; commands[i].name; i++) {
        cmd = commands + i;
        cmd_size = strlen(cmd->name);
        if (strncmp(cmd_str, cmd->name, cmd_size) != 0 || !cmd->build_job)
            continue;
        job_buf->f = cmd->f;
        job_buf->name = cmd->name;
        return set_arg(&job_buf->jdata.arg, cmd_str, cmd_size, cmd)
            && cmd->build_job(server, player, &job_buf->jdata);
    }
    return false;
}
