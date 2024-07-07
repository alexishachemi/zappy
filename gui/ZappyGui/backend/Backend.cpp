/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Backend
*/

#include "Backend.hpp"

gui::Backend::Backend()
{
    mapSize = {0, 0};
}

void gui::Backend::setMapSize(Vec2 size)
{
    mapSize = size;
    resizeMap(size);
}

gui::Vec2 gui::Backend::getMapSize() const
{
    return mapSize;
}

gui::Player &gui::Backend::addPlayer(std::size_t id, Vec2 pos, Orientation orient, std::size_t level, const std::string &team)
{
    Player *player = new Player(id, pos, orient, level, getTeamId(team));
    
    players.push_back(std::unique_ptr<Player>(player));
    addToMap(*player);
    return *player;
}

gui::Player &gui::Backend::getPlayer(std::size_t id)
{
    for (auto &p : players) {
        if (p->getId() == id)
            return *p;
    }
    throw BackendError("Cannot find player " + std::to_string(id));
}

void gui::Backend::removePlayer(std::size_t id)
{
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getId() == id) {
            Tile &tile = getTile(players[i]->getPos());
            tile.removePlayer(players[i]->getId());
            players.erase(players.begin() + i);
            return;
        }
    }
}

gui::Egg &gui::Backend::addEgg(std::size_t id, Vec2 pos, std::size_t teamId)
{
    Egg *egg = new Egg(id, pos, teamId);

    eggs.push_back(std::unique_ptr<Egg>(egg));
    addToMap(*egg);
    return *egg;
}

gui::Egg &gui::Backend::getEgg(std::size_t id)
{
    for (auto &e : eggs) {
        if (e->getId() == id)
            return *e;
    }
    throw BackendError("Cannot find egg " + std::to_string(id));
}

void gui::Backend::removeEgg(std::size_t id)
{
    for (int i = 0; i < eggs.size(); i++) {
        if (eggs[i]->getId() == id) {
            Tile &tile = getTile(eggs[i]->getPos());
            tile.removeEgg(eggs[i]->getId());
            eggs.erase(eggs.begin() + i);
            return;
        }
    }
}

std::size_t gui::Backend::addTeam(const std::string &name)
{
    static std::size_t id = 0;

    teams.push_back({id++, name});
    return teams.back().first;
}

std::size_t gui::Backend::getTeamId(const std::string &name) const
{
    for (auto &t : teams) {
        if (t.second == name)
            return t.first;
    }
    throw BackendError("Cannot find team " + name);
}

std::size_t gui::Backend::getTeamId(const std::string &name)
{
    for (auto &t : teams) {
        if (t.second == name)
            return t.first;
    }
    return addTeam(name);
}

gui::Tile &gui::Backend::addTile(Vec2 pos)
{
    try {
        getTile(pos);
    } catch (gui::Backend::BackendError &e) {
        tiles.push_back(pos);
        return tiles.back();
    }
    return getTile(pos);
}

gui::Tile &gui::Backend::getTile(Vec2 pos)
{
    for (auto &t : tiles) {
        if (t.pos == pos)
            return t;
    }
    throw BackendError("Could not find tile at position " + pos.toString());
}

const gui::Tile &gui::Backend::getTile(Vec2 pos) const
{
    for (auto &t : tiles) {
        if (t.pos == pos)
            return t;
    }
    throw BackendError("Could not find tile at position " + pos.toString());
}

const std::string &gui::Backend::getTeamName(std::size_t id) const
{
    for (auto &t : teams) {
        if (t.first == id)
            return t.second;
    }
    throw BackendError("Cannot find team with id " + std::to_string(id));    
}

void gui::Backend::setFrequency(std::size_t freq)
{
    this->freq = freq;
}

std::size_t gui::Backend::getFrequency() const
{
    return freq;
}

const std::vector<std::unique_ptr<gui::Player>> &gui::Backend::getPlayers() const
{
    return players;
}

const std::vector<std::unique_ptr<gui::Egg>> &gui::Backend::getEggs() const
{
    return eggs;
}

const std::vector<gui::Backend::Team> &gui::Backend::getTeams() const
{
    return teams;
}

const std::vector<gui::Tile>::const_iterator gui::Backend::begin() const
{
    return tiles.begin();
}

const std::vector<gui::Tile>::const_iterator gui::Backend::end() const
{
    return tiles.end();
}

void gui::Backend::resizeMap(Vec2 size)
{
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            addTile({x, y});
        }
    }
}

void gui::Backend::addToMap(Player &player)
{
    getTile(player.getPos()).addPlayer(player);
}

void gui::Backend::addToMap(Egg &egg)
{
    getTile(egg.getPos()).addEgg(egg);
}
