/*
** EPITECH PROJECT, 2023
** server
** File description:
** win.c
*/

#include "server.h"
#include "gui.h"

static bool check_team_level(list_t *players_list, size_t team_id)
{
    int count = 0;
    player_t *player = NULL;

    for (node_t *n = players_list->head; n; n = n->next) {
        player = n->data;
        if (player->team_id == team_id && player->level >= PLAYER_MAX_LEVEL)
            count++;
    }
    return count >= TEAM_MAXED_REQUIRED;
}

static int check_team_victory(server_t *server, list_t *teams_list)
{
    team_t *team = NULL;

    for (node_t *n = teams_list->head; n; n = n->next) {
        team = n->data;
        if (check_team_level(&server->world.players, team->id))
            return team->id;
    }
    return -1;
}

void server_check_win(server_t *server)
{
    int winner = -1;
    char *team_name = NULL;

    if (!server)
        return;
    winner = check_team_victory(server, &server->world.teams);
    if (winner == -1)
        return;
    server->enabled = false;
    team_name = world_get_team_name(server, winner);
    gui_broadcast_event(server, gui_send_game_end, team_name);
    TRUE_SLOG(server, INFO, "Team %s won the game", team_name);
}
