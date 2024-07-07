/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parser
*/

#include "Parser.hpp"
#include "Gui.hpp"

using namespace gui;

Parser::Parser()
{
    registerEventParser("msz", mapSizeCmd);
    registerEventParser("bct", tileContentCmd);
    registerEventParser("tna", teamNameCmd);
    registerEventParser("pnw", playerConnectionCmd);
    registerEventParser("ppo", playerPosCmd);
    registerEventParser("plv", playerLevelCmd);
    registerEventParser("pin", playerInventoryCmd);
    registerEventParser("pex", playerExpulsionCmd);
    registerEventParser("pbc", broadcastCmd);
    registerEventParser("pic", incantationCmd);
    registerEventParser("pie", incantationEndingCmd);
    registerEventParser("pfk", eggLayingCmd);
    registerEventParser("pdr", dropRessourcesCmd);
    registerEventParser("pgt", collectingRessourcesCmd);
    registerEventParser("pdi", playerDeathCmd);
    registerEventParser("enw", eggLayedCmd);
    registerEventParser("ebo", playerConnectionEggCmd);
    registerEventParser("edi", eggDeathCmd);
    registerEventParser("sgt", timeRequestCmd);
    registerEventParser("sst", timeModificationCmd);
    registerEventParser("seg", endGameCmd);
    registerEventParser("smg", serverMessageCmd);
    registerEventParser("suc", unknownCmd);
    registerEventParser("sbp", cmdParam);
}

void Parser::registerEventParser(const std::string &cmdName, EventParser parser)
{
    EventMap[cmdName] = parser;
}

void Parser::getCommand(Gui &g, const std::string &cmdName, const std::vector<std::string> &data)
{
    for (auto &p: EventMap) {
        if (p.first == cmdName) {
            p.second(g, data);
            return;
        }
    }
}

bool Parser::splitString(std::string data, char delimiter, std::vector<std::string> &buf)
{
    std::stringstream ss(data);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        buf.push_back(item);
    }
    return buf.size() > 0;
}

void Parser::parseLine(Gui &g, const std::string &line)
{
    std::vector<std::string> params;
    std::string cmdName;

    if (!splitString(line, ' ', params)) {
        return;
    }
    cmdName = params.front();
    params.erase(params.begin());
    getCommand(g, cmdName, params);
}

void Parser::parse(Gui &g, const std::string &data)
{
    std::vector<std::string> lines;

    if (!splitString(data, '\n', lines)) {
        return;
    }
    for (auto &line: lines) {
        parseLine(g, line);
    }
}
