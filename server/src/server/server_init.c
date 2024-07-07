/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_init
*/

#include <string.h>
#include <ncurses.h>
#include "server.h"
#include "arg.h"
#include "clogger.h"

static const char *help_msg =
"USAGE:\t./zappy_server -x width -y height -n name1 name2 ... "
"[-p port] [-c clientsNb] [-f freq] [-d]\nOPTIONS:"
"\n\t-x width\twidth of the world"
"\n\t-y height\theight of the world"
"\n\t-n n1 n2...\tnames of the teams"
"\n\t-p port\t\tport of the server (default: chosen automatically)"
"\n\t-c clientsNb\tnumber of slots per team at the start (default: 1)"
"\n\t-f freq\t\treciprocal of time unit for execution of "
"actions (default: 100)"
"\n\t-d\t\tturn on status display on the terminal (default: off)"
"\n\t-v\t\tturn on verbose mode (default: off)"
"\n\t-l\t\tlog file (Does not log by default, \"server.log\" if the "
"specified path is not valid)"
"\n\t--god-mode\tdisable hunger (default: off)\n";

static const char *expected_args[] = {"x", "y", "n", NULL};

static bool get_args(argm_t *args, int ac, const char **av)
{
    argm_init(args);
    argm_expect_list(args, "n");
    if (!argm_parse(args, ac, av))
        return false;
    if (argm_has(args, "h") || argm_has(args, "help")) {
        puts(help_msg);
        return false;
    }
    for (size_t i = 0; expected_args[i]; i++) {
        if (!argm_has(args, expected_args[i])) {
            dprintf(2, "Missing mandatory argument: -%s\n", expected_args[i]);
            argm_deinit(args);
            return false;
        }
    }
    return true;
}

static bool init_world(server_t *server, argm_t *args)
{
    vec2_t size = {0, 0};
    list_t teams = {0};

    list_init(&teams);
    size.x = arg_as_int(argm_get(args, "x"));
    size.y = arg_as_int(argm_get(args, "y"));
    if (!world_init(server, size, NULL))
        return FALSE_SLOG(server, CRITICAL, "Failed to create map");
    if (!world_add_teams(server, arg_as_list(argm_get(args, "n"), &teams)))
        return FALSE_SLOG(server, CRITICAL, "Failed to add teams");
    list_clear_free(&teams);
    if (argm_has(args, "f") &&
        !world_set_freq(server, arg_as_int(argm_get(args, "f"))))
        return FALSE_SLOG(server, CRITICAL, "Failed to set frequency");
    if (!world_add_eggs_per_team(server,
        argm_has(args, "c") ? arg_as_int(argm_get(args, "c")) : 1))
        return FALSE_SLOG(server, CRITICAL, "Failed to add default slots");
    return TRUE_SLOG(server, INFO, "Initialized world of size (%d, %d)",
        size.x, size.y);
}

static bool init_net(net_t *net, argm_t *args)
{
    port_t port = 0;
    const char *default_log_file = "server.log";
    const char *log_file = NULL;
    bool log_stdout = false;
    char buf[LOG_LEVEL_SIZE + 1];

    memset(buf, 0, LOG_LEVEL_SIZE + 1);
    log_stdout = !argm_has(args, "d") && argm_has(args, "v");
    if (argm_has(args, "l")) {
        log_file = arg_as_string(argm_get(args, "l"));
        if (!log_file)
            log_file = default_log_file;
    }
    port = arg_as_int(argm_get(args, "p"));
    if (!net_init(net, port, log_file, log_stdout) || !nets_host(net))
        return false;
    if (argm_has(args, "log-level") && !logger_set_level_str(
        &net->logger, arg_as_string(argm_get(args, "log-level"))))
        return false;
    return true;
}

static void init_display(server_t *server, argm_t *args)
{
    server->display = argm_has(args, "d");
    if (server->display) {
        SLOG(server, INFO, "Initializing NCurses display...");
        initscr();
        keypad(stdscr, FALSE);
        nodelay(stdscr, TRUE);
        noecho();
    }
}

static void init_list(server_t *server)
{
    list_init(&server->dead_clients);
    list_init(&server->player_clients);
    list_init(&server->playerless_clients);
}

bool server_init(server_t *server, int ac, const char **av)
{
    argm_t args;

    if (!server || !av || !get_args(&args, ac, av))
        return false;
    if (!init_net(&server->net, &args)) {
        argm_deinit(&args);
        return false;
    }
    if (!init_world(server, &args)) {
        argm_deinit(&args);
        net_deinit(&server->net);
        return false;
    }
    init_display(server, &args);
    server->god_mode = argm_has(&args, "god-mode");
    argm_deinit(&args);
    server->step = 0;
    server->enabled = true;
    init_list(server);
    return true;
}

void server_deinit(server_t *server)
{
    if (!server)
        return;
    list_clear_free(&server->player_clients);
    list_clear_free(&server->playerless_clients);
    list_clear_free(&server->graphical_clients);
    world_deinit(server);
    if (server->display) {
        SLOG(server, INFO, "Deinitializing NCurses display...");
        endwin();
    }
    SLOG(server, INFO, "Server deinitialized");
    net_deinit(&server->net);
}
