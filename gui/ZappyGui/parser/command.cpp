/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parser
*/

#include "Parser.hpp"
#include "Gui.hpp"

using namespace gui;

void Parser::mapSizeCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 2)
        return;
    g.backend.setMapSize({std::stoi(data[0]), std::stoi(data[1])});
}

void Parser::tileContentCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() <= 2)
        return;
    Inventory &inv = g.backend.getTile({std::stoi(data[0]), std::stoi(data[1])}).inventory;
    for (int i = 0; i < 7; i++) {
        std::size_t &count = inv[static_cast<Item>(i)];
        count = std::stoi(data[i + 2]);
        g.backend.addTile({std::stoi(data[0]), std::stoi(data[1])}).inventory = inv;
    }
}

void Parser::teamNameCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    g.backend.addTeam(data[0]);
}

void Parser::playerConnectionCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 6)
        return;
    int id = std::stoi(data[0]);
    Vec2 pos(std::stoi(data[1]), std::stoi(data[2]));
    Orientation	orientation = static_cast<Orientation>(std::stoi(data[3]));
    int level = std::stoi(data[4]);
    std::string team = data[5];
    g.backend.addPlayer(id, pos, orientation, level, team);
}

void Parser::playerPosCmd(Gui &g, const std::vector<std::string> &data)
{
    int id = std::stoi(data[0]);
    int x = std::stoi(data[1]);
    int y = std::stoi(data[2]);
    int view = std::stoi(data[3]);
    Player &player = g.backend.getPlayer(id);
    Tile &oldTile = g.backend.getTile(player.getPos());
    Tile &newTile = g.backend.getTile({x, y});
    player.setOrientation(static_cast<Orientation>(view));
    oldTile.movePlayer(player, newTile);
    g.stopPlayerElevation(player);
    player.setLaying(false);
}

void Parser::playerLevelCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 2)
        return;
    int id = std::stoi(data[0]);
    int level = std::stoi(data[1]);
    g.backend.getPlayer(id).setLevel(level);
}

void Parser::playerInventoryCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 10)
        return;
    int id = std::stoi(data[0]);
    Inventory &inv = g.backend.getPlayer(id).inventory;
    for (int i = 0; i < 7; i++) {
        std::size_t &count = inv[static_cast<Item>(i)];
        count = std::stoi(data[i + 3]);
    }
}

void Parser::playerExpulsionCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    Player &player = g.backend.getPlayer(std::stoi(data[0]));
    Tile &tile = g.backend.getTile(player.getPos());
    for (auto *p: tile.players) {
        g.requestPlayerPos(p->getId());
    }
}

void Parser::broadcastCmd(Gui &g, const std::vector<std::string> &data)
{
    return;
}

void Parser::incantationCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() < 2)
        return;
    for (int i = 3; i < data.size(); i++) {
        Player &player = g.backend.getPlayer(std::stoi(data[i]));
        player.setElevating(true);
        player.setLaying(false);
    }
}

void Parser::incantationEndingCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 3)
        return;
    int x = std::stoi(data[0]);
    int y = std::stoi(data[1]);
    Tile &tile = g.backend.getTile({x, y});

    for (auto *p: tile.players) {
        g.stopPlayerElevation(*p);
    }
}

void Parser::eggLayingCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    Player &player = g.backend.getPlayer(std::stoi(data[0]));
    g.stopPlayerElevation(player);
    player.setLaying(true);
}

void Parser::dropRessourcesCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 2)
        return;
    int id = std::stoi(data[0]);
    int item = std::stoi(data[1]);
    Player &player = g.backend.getPlayer(id);
    g.requestPlayerInventory(id);
    g.requestTileContent(player.getPos());
}

void Parser::collectingRessourcesCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 2)
        return;
    int id = std::stoi(data[0]);
    int item = std::stoi(data[1]);
    Player &player = g.backend.getPlayer(id);
    g.requestPlayerInventory(id);
    g.requestTileContent(player.getPos());
}

void Parser::playerDeathCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    int id = std::stoi(data[0]);
    g.backend.removePlayer(id);
}

void Parser::eggLayedCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 4)
        return;
    int egg_id = std::stoi(data[0]);
    int layer_id = std::stoi(data[1]);
    Vec2 pos(std::stoi(data[2]), std::stoi(data[3]));
    int team_id = layer_id < 0 ? -1 : g.backend.getPlayer(layer_id).getTeam();

    g.backend.addEgg(egg_id, pos, team_id);
}

void Parser::playerConnectionEggCmd(Gui &g, const std::vector<std::string> &data)
{
    return;
}

void Parser::eggDeathCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    int egg_id = std::stoi(data[0]);
    g.backend.removeEgg(egg_id);
}

void Parser::timeRequestCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    g.backend.setFrequency(std::stoi(data[0]));
}

void Parser::timeModificationCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    g.backend.setFrequency(std::stoi(data[0]));
}

void Parser::endGameCmd(Gui &g, const std::vector<std::string> &data)
{
    if (data.size() != 1)
        return;
    g.backend.end();
}

void Parser::serverMessageCmd(Gui &g, const std::vector<std::string> &data)
{
    return;
}

void Parser::unknownCmd(Gui &g, const std::vector<std::string> &data)
{
    return;
}

void Parser::cmdParam(Gui &g, const std::vector<std::string> &data)
{
    return;
}
