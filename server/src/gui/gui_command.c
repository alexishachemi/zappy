/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_command
*/

#include <stdlib.h>
#include <string.h>
#include "gui.h"
#include "utils.h"

static const gui_command_t commands[] = {
    {"msz", 0, gui_send_map_size},
    {"bct", 2, gui_cmd_tile_info},
    {"mct", 0, gui_send_map_info},
    {"tna", 0, gui_send_teams_name},
    {"ppo", 1, gui_cmd_player_pos},
    {"plv", 1, gui_cmd_player_level},
    {"pin", 1, gui_cmd_player_inv},
    {"sgt", 0, gui_send_time_unit},
    {"sst", 1, gui_cmd_set_time_unit},
    {NULL, 0, NULL}
};

static char **free_args(char **args)
{
    if (!args)
        return NULL;
    for (size_t i = 0; args[i]; i++) {
        free(args[i]);
    }
    free(args);
    return NULL;
}

static bool setup_args_buf(char ***buf, size_t expected_args)
{
    char **args = NULL;

    if (!buf || expected_args == 0)
        return false;
    args = malloc(sizeof(char *) * (expected_args + 1));
    if (!args)
        return false;
    memset(args, 0, sizeof(char *) * (expected_args + 1));
    *buf = args;
    return true;
}

static bool check_args(char *str, size_t expected_args, size_t cmd_len)
{
    bool is_sep = false;
    size_t arg_count = 0;

    if (str[cmd_len] != ' ')
        return false;
    for (size_t i = cmd_len; str[i]; i++) {
        if (is_sep && str[i] == ' ')
            return false;
        if (!is_sep && str[i] == ' ') {
            is_sep = true;
            continue;
        }
        if (is_sep && str[i] != ' ') {
            arg_count++;
            is_sep = false;
        }
    }
    return arg_count == expected_args;
}

static char **split_args(char *str, size_t expected_args, size_t cmd_len)
{
    char **args = NULL;
    char *arg = NULL;

    if (!str || expected_args == 0 || !check_args(str, expected_args, cmd_len)
        || !setup_args_buf(&args, expected_args))
        return NULL;
    arg = strtok(str, " ");
    if (!arg)
        return NULL;
    for (size_t i = 0; i < expected_args; i++) {
        arg = strtok(NULL, " ");
        if (!arg)
            return free_args(args);
        args[i] = strdup(arg);
        if (!args[i])
            return free_args(args);
    }
    return args;
}

static int process_matched(
    server_t *s, int sock, char *str, const gui_command_t *cmd)
{
    char **args = NULL;
    size_t cmd_len = 0;
    bool status = true;

    cmd_len = strlen(cmd->name);
    if (cmd->expected_args == 0 && strlen(str) > cmd_len)
        return false;
    args = split_args(str, cmd->expected_args, cmd_len);
    if ((!args && cmd->expected_args != 0) || !cmd->callback(s, sock, args))
        status = false;
    free_args(args);
    return status;
}

void gui_process_command(server_t *server, int sock, char *str)
{
    if (!server || !str)
        return;
    for (size_t i = 0; commands[i].name; i++) {
        if (strncmp(str, commands[i].name, strlen(commands[i].name)) != 0)
            continue;
        if (!process_matched(server, sock, str, commands + i))
            return gui_send_bad_arg(server, sock);
        else
            return;
    }
    gui_send_unknown_cmd(server, sock);
}
