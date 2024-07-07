/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_update
*/

#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>
#include "server.h"

static time_ms_t get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (((time_ms_t)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

static bool can_update_world(unsigned int f)
{
    static time_ms_t last = 0;
    time_ms_t sleep_time = 1000 / f;
    time_ms_t elapsed = 0;
    time_ms_t now = 0;

    now = get_time_ms();
    if (last == 0)
        last = now;
    elapsed = now - last;
    if (elapsed >= sleep_time) {
        last = now;
        return true;
    }
    return false;
}

static void handle_remaining_packets(net_t *net)
{
    while (!list_empty(&net->to_send) && net_update(net));
}

int server_update(server_t *server)
{
    if (!server || net_update(&server->net) != NET_OK)
        return -1;
    server_handle_clients(server);
    if (!can_update_world(server->world.freq))
        return 0;
    server->step++;
    world_update(server);
    server_kick_dead(server);
    if (!server->enabled) {
        handle_remaining_packets(&server->net);
        return 1;
    }
    server_print(server);
    return 0;
}
