/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "linked.h"
#include "server.h"
#include "utils.h"

static server_t server = {0};

static void handle_interrupt(UNUSED int sig)
{
    server_deinit(&server);
    exit(0);
}

int main(int ac, const char **av)
{
    int status = 0;

    signal(SIGINT, handle_interrupt);
    srand(time(NULL));
    if (!server_init(&server, ac, av))
        return 84;
    if (!server.display && !server.net.logger.os)
        printf("Server started on port %d\n", server.net.port);
    while (status == 0) {
        status = server_update(&server);
    }
    server_deinit(&server);
    return status == 1 ? 0 : 84;
}
