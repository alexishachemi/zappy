/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Parser
*/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include "Backend.hpp"

namespace gui
{
    class Gui;
    class Parser
    {
        using EventParser = std::function<void(Gui &g, const std::vector<std::string>&)>;
        public:
            Parser();

            /// @brief 
            /// @param cmdName 
            /// @param parser 
            void registerEventParser(const std::string &cmdName, EventParser parser);

            bool splitString(std::string data, char delimiter, std::vector<std::string> &buf);

            /// @brief 
            /// @param data 
            void parse(Gui &g, const std::string &data);

            /// @brief 
            /// @param  
            void getCommand(Gui &g, const std::string &cmdName, const std::vector<std::string> &data);

            /// @brief msz X Y\n, map size
            /// @param const string & 
            static void mapSizeCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief bct X Y q0 q1 q2 q3 q4 q5 q6\n, content of a tile
            /// @param const string & 
            static void tileContentCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief mct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles, content of the map (all the tiles)
            /// @param const string & 
            static void mapContentCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief tna N\n * nbr_teams, name of all the teams
            /// @param const string & 
            static void teamNameCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pnw #n X Y O L N\n, connection of a new player
            /// @param const string & 
            static void playerConnectionCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief ppo #n X Y O\n, player’s position
            /// @param const string & 
            static void playerPosCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief plv #n L\n, player’s level
            /// @param const string & 
            static void playerLevelCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pin #n X Y q0 q1 q2 q3 q4 q5 q6\n, player’s inventory
            /// @param const string & 
            static void playerInventoryCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pex #n\n, player expulsion
            /// @param const string & 
            static void playerExpulsionCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pbc #n M\n, player broadcast
            /// @param const string & 
            static void broadcastCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pic X Y L #n #n . . .\n, start of an incantation (by the first player)
            /// @param const string & 
            static void incantationCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pie X Y R\n, end of an incantation
            /// @param const string & 
            static void incantationEndingCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pfk #n\n egg laying by the player
            /// @param const string & 
            static void eggLayingCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pdr #n i\n, resource dropping
            /// @param const string & 
            static void dropRessourcesCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pgt #n i\n, resource collecting
            /// @param const string & 
            static void collectingRessourcesCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief pdi #n\n, death of a player
            /// @param const string & 
            static void playerDeathCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief enw #e #n X Y\n, an egg was laid by a player
            /// @param const string & 
            static void eggLayedCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief ebo #e\n, player connection for an egg
            /// @param const string & 
            static void playerConnectionEggCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief edi #e\n, death of an egg
            /// @param const string & 
            static void eggDeathCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief sgt T\n, time unit request
            /// @param const string & 
            static void timeRequestCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief sst T\n, time unit modification
            /// @param const string & 
            static void timeModificationCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief seg N\n, end of game
            /// @param const string & 
            static void endGameCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief smg M\n, message from the server
            /// @param const string & 
            static void serverMessageCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief suc\n, server say that there is an unknown command
            /// @param data 
            static void unknownCmd(Gui &g, const std::vector<std::string> &data);

            /// @brief sbp\n, command parameter
            /// @param data 
            static void cmdParam(Gui &g, const std::vector<std::string> &data);

        private:
            std::map<std::string, EventParser> EventMap;
            // std::map<std::string, void (Parser::*)(const std::string&)> command;

            void parseLine(Gui &g, const std::string &line);
    };
}
