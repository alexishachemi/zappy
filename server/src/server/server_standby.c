/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server standby
*/

#include <string.h>
#include "server.h"
#include "gui.h"

static void *alloc_int(void)
{
    return malloc(sizeof(int));
}

bool server_sock_has_player(server_t *server, int sock)
{
    return list_find_if(&server->player_clients, int_eq, &sock) != NULL;
}

void server_remove_client(server_t *server, int sock)
{
    if (list_remove_if_free(&server->player_clients, int_eq, &sock) > 0) {
        world_remove_player(server, sock);
        return;
    }
    if (list_remove_if_free(&server->playerless_clients, int_eq, &sock) > 0)
        return;
    list_remove_if_free(&server->graphical_clients, int_eq, &sock);
}

bool server_add_playerless(server_t *server, int sock)
{
    int *csock = NULL;

    csock = list_add(&server->playerless_clients, alloc_int);
    if (!csock)
        return false;
    *csock = sock;
    nets_send(&server->net, sock, "WELCOME");
    return TRUE_SLOG(server, INFO, "New client %d has connected", sock);
}

static void send_player_info(server_t *server, int sock, size_t team_id)
{
    char buf[128];

    memset(buf, 0, 128);
    snprintf(
        buf, 128, "%ld\n%d %d",
        egg_count_from_team(&server->world.eggs, team_id),
        server->world.size.x, server->world.size.y
    );
    nets_send(&server->net, sock, buf);
}

bool server_try_add_gui(server_t *server, int sock, const char *team_name)
{
    if (!server || !team_name || strcmp(team_name, GUI_TEAM) != 0)
        return false;
    list_move_if(&server->playerless_clients, &server->graphical_clients,
        int_eq, &sock);
    gui_send_current_state(server, sock);
    return TRUE_SLOG(server, INFO, "Client %d is now registered as GUI", sock);
}

bool server_try_add_player(server_t *server, int sock, const char *team_name)
{
    int team_id = 0;
    player_t *player = NULL;

    if (!server || !team_name)
        return false;
    team_id = world_get_team_id(server, team_name);
    player = world_add_player(server, sock, team_id);
    if (!player) {
        nets_send(&server->net, sock, "ko");
        return false;
    }
    send_player_info(server, sock, team_id);
    list_move_if(&server->playerless_clients, &server->player_clients,
        int_eq, &sock);
    return TRUE_SLOG(server, INFO,
        "Client %d is now registered as player %ld", sock, player->id);
}
