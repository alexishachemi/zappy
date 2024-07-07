/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GraphicsFactory
*/

#include "GraphicsFactory.hpp"
#include "SFMLGraphics.hpp"
#include "RLGraphics.hpp"

gui::GraphicsFactory::GraphicsFactory()
{
    registerGraphics("sfml", [](){ return std::make_unique<SFMLGraphics>(); });
    registerGraphics("raylib", [](){ return std::make_unique<RLGraphics>(); });
}

void gui::GraphicsFactory::registerGraphics(const std::string &name, CreatorFunction creator)
{
    try {
        removeGraphcis(name);
    } catch (GraphicsFactoryError &e) {}
    creators.push_back({name, creator});
}

void gui::GraphicsFactory::removeGraphcis(const std::string &name)
{
    for (int i = 0; i < creators.size(); i++) {
        if (creators[i].first == name) {
            creators.erase(creators.begin() + i);
            return;
        }
    }
    throw GraphicsFactoryError("No graphics registered as " + name + " to remove");
}

std::unique_ptr<gui::IGraphics>gui::GraphicsFactory::createGraphics(const std::string &name)
{
    return getCreator(name)();
}

gui::GraphicsFactory::CreatorFunction &gui::GraphicsFactory::getCreator(const std::string &name)
{
    for (auto &creator : creators) {
        if (creator.first == name) {
            return creator.second;
        }
    }
    throw GraphicsFactoryError("No graphics registered as " + name);
}
