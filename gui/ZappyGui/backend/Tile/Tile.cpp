/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"

gui::Tile::Tile(Vec2 pos)
 : pos(pos) {}

gui::Player &gui::Tile::getPlayer(std::size_t id)
{
    for (Player *p : players) {
        if (p->getId() == id)
            return *p;
    }
    throw TileError("Cannot find player with id " + std::to_string(id) + "at tile " + pos.toString());
}

void gui::Tile::addPlayer(Player &player)
{
    players.push_back(&player);
    player.setPos(pos);
}

void gui::Tile::removePlayer(std::size_t id)
{
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getId() == id) {
            players.erase(players.begin() + i);
            return;
        }
    }
}

void gui::Tile::movePlayer(Player &player, Tile &to)
{
    removePlayer(player.getId());
    to.addPlayer(player);
}

void gui::Tile::addEgg(Egg &egg)
{
    eggs.push_back(&egg);
}

void gui::Tile::removeEgg(std::size_t id)
{
    for (int i = 0; i < eggs.size(); i++) {
        if (eggs[i]->getId() == id) {
            eggs.erase(eggs.begin() + i);
            return;
        }
    }
}

void gui::Tile::clearEggs()
{
    eggs.clear();    
}

gui::Tile &gui::Tile::operator=(const Tile &tile)
{
    inventory = tile.inventory;
    players = tile.players;
    eggs = tile.eggs;
    return *this;
}
