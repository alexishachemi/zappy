/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Gui
*/

#include "Gui.hpp"
#include "SFMLGraphics.hpp"

gui::Gui::Gui(const std::string &host, socknet::port hostPort)
    : net(0, "gui.log")
{
    net.connect(host, hostPort);
    net.send("GRAPHIC");
}

bool gui::Gui::update()
{
    std::string data;
    bool winOpen = true;

    while (net.recv(data)) {
        parser.parse(*this, data);
    }
    if (graphics.get()) {
        winOpen = graphics->update(backend);
    }
    return net.update() == socknet::status::NET_OK && winOpen;
}

void gui::Gui::setGraphics(const std::string &name)
{
    graphics = graphicsFactory.createGraphics(name);
}

void gui::Gui::requestMapSize()
{
    net.send("msz");
}

void gui::Gui::requestTileContent(Vec2 pos)
{
    net.send("bct " + pos.toString());
}

void gui::Gui::requestMapContent()
{
    net.send("mct");
}

void gui::Gui::requestTeamNames()
{
    net.send("tna");
}

void gui::Gui::requestPlayerPos(std::size_t id)
{
    net.send("ppo " + std::to_string(id));
}

void gui::Gui::requestPlayerLevel(std::size_t id)
{
    net.send("plv " + std::to_string(id));
}

void gui::Gui::requestPlayerInventory(std::size_t id)
{
    net.send("pin " + std::to_string(id));
}

void gui::Gui::requestTimeUnit()
{
    net.send("sgt");
}

void gui::Gui::setTimeUnit(std::size_t unit)
{
    net.send("sst " + std::to_string(unit));
}

void gui::Gui::stopPlayerElevation(Player &player)
{
    if (player.isElevating()) {
        player.setElevating(false);
        requestPlayerLevel(player.getId());
    }
}
