/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile_elevation
*/

#include "tile.h"

static const elev_requirements_t elev_map[] = {
    {
        2, .players = 1, {0,
            .linemate = 1,
            .deraumere = 0,
            .sibur = 0,
            .mendiane = 0,
            .phiras = 0,
            .thystame = 0
        },
    },
    {
        3, .players = 2, {0,
            .linemate = 1,
            .deraumere = 1,
            .sibur = 1,
            .mendiane = 0,
            .phiras = 0,
            .thystame = 0
        },
    },
    {
        4, .players = 2, {0,
            .linemate = 2,
            .deraumere = 0,
            .sibur = 1,
            .mendiane = 0,
            .phiras = 2,
            .thystame = 0
        },
    },
    {
        5, .players = 4, {0,
            .linemate = 1,
            .deraumere = 1,
            .sibur = 2,
            .mendiane = 0,
            .phiras = 1,
            .thystame = 0
        },
    },
    {
        6, .players = 4, {0,
            .linemate = 1,
            .deraumere = 2,
            .sibur = 1,
            .mendiane = 3,
            .phiras = 0,
            .thystame = 0
        },
    },
    {
        7, .players = 6, {0,
            .linemate = 1,
            .deraumere = 2,
            .sibur = 3,
            .mendiane = 0,
            .phiras = 1,
            .thystame = 0
        },
    },
    {
        8, .players = 6, {0,
            .linemate = 2,
            .deraumere = 2,
            .sibur = 2,
            .mendiane = 2,
            .phiras = 2,
            .thystame = 1
        },
    }
};

static size_t count_members(tile_t *tile,
    const elev_requirements_t *requirements, player_t *host)
{
    player_t *player = NULL;
    size_t members = 1;

    if (host->elevation_status == ELEV_MEMB
        || host->level != requirements->target_level - 1)
        return 0;
    for (node_t *n = tile->players.head; n; n = n->next) {
        player = n->data;
        if (player == host || player->level != requirements->target_level - 1)
            continue;
        if (host->elevation_status == ELEV_HOST)
            members += list_has_ptr(&host->elevation_list, player);
        if (host->elevation_status == ELEV_NONE)
            members += player->elevation_status == ELEV_NONE;
    }
    return members;
}

static bool check_requirements(tile_t *tile,
    const elev_requirements_t *requirements, player_t *host)
{
    return count_members(tile, requirements, host) >= requirements->players
        && inventory_ge(&tile->inventory, &requirements->ressources);
}

static const elev_requirements_t *get_requirements(size_t current_level)
{
    size_t max_level = sizeof(elev_map) / sizeof(elev_requirements_t) + 1;

    if (current_level == 0 || current_level > max_level)
        return false;
    return elev_map + current_level - 1;
}

bool tile_can_elevate(tile_t *tile, player_t *host)
{
    return check_requirements(tile, get_requirements(host->level), host);
}

bool tile_remove_elev_ressources(tile_t *tile, size_t target_level)
{
    const elev_requirements_t *requirements = NULL;

    requirements = get_requirements(target_level - 1);
    if (!requirements)
        return false;
    inventory_sub(&tile->inventory, &requirements->ressources);
    return true;
}
