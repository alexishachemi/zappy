/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Gui
*/

#pragma once

#include "socknet.hpp"
#include "Backend.hpp"
#include "Parser.hpp"
#include "GraphicsFactory.hpp"

namespace gui
{
    class Gui
    {
        public:
            socknet::Net net;
            Backend backend;
            Parser parser;
            GraphicsFactory graphicsFactory;
            std::unique_ptr<IGraphics> graphics;

            Gui(const std::string &host, socknet::port hostPort);
            bool update();
            void setGraphics(const std::string &name);
            void requestMapSize();
            void requestTileContent(Vec2 pos);
            void requestMapContent();
            void requestTeamNames();
            void requestPlayerPos(std::size_t id);
            void requestPlayerLevel(std::size_t id);
            void requestPlayerInventory(std::size_t id);
            void requestTimeUnit();
            void setTimeUnit(std::size_t unit);
            void stopPlayerElevation(Player &player);

            NEW_ERROR(GuiError);
    };
}
