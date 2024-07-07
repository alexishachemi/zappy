/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLRendererManager
*/

#include <algorithm>
#include "RLRendererManager.hpp"
#include "RL2DRenderer.hpp"
#include "RLIsoRenderer.hpp"

void gui::RLRendererManager::init()
{
    addRenderer(new RLIsoRenderer());
    addRenderer(new RL2DRenderer());
}

void gui::RLRendererManager::addRenderer(IRLRenderer *renderer)
{
    this->renderers.push_back(std::unique_ptr<IRLRenderer>(renderer));
    if (!this->currentRenderer)
        this->currentRenderer = renderer;
}

gui::IRLRenderer *gui::RLRendererManager::getRenderer(const std::string &name)
{
    for (auto &renderer : this->renderers) {
        if (renderer->getName() == name)
            return renderer.get();
    }
    throw RLRendererManagerError("Map renderer " + name + " not found");
}

gui::IRLRenderer *gui::RLRendererManager::getRenderer()
{
    if (!currentRenderer)
        throw RLRendererManagerError("No map renderer available");
    return this->currentRenderer;
}

void gui::RLRendererManager::setCurrentRenderer(const std::string &name)
{
    this->currentRenderer = this->getRenderer(name);
}

void gui::RLRendererManager::nextRenderer()
{
    if (renderers.empty())
        throw RLRendererManagerError("No renderer available");
    if (renderers.size() == 1)
        return;
    currentRenderer->stop();
    if (currentRenderer == renderers.back().get()) {
        currentRenderer = renderers.front().get();
        currentRenderer->start();
        return;
    }
    auto isCurrent = [this](const std::unique_ptr<IRLRenderer> &renderer) {
        return renderer.get() == currentRenderer;
    };
    auto it = std::find_if(renderers.begin(), renderers.end(), isCurrent);
    currentRenderer = (++it)->get();
    currentRenderer->start();
}

void gui::RLRendererManager::previousRenderer()
{
    if (renderers.empty())
        throw RLRendererManagerError("No renderer available");
    if (renderers.size() == 1)
        return;
    currentRenderer->stop();
    if (currentRenderer == renderers.front().get()) {
        currentRenderer = renderers.back().get();
        currentRenderer->start();
        return;
    }
    auto isCurrent = [this](const std::unique_ptr<IRLRenderer> &renderer) {
        return renderer.get() == currentRenderer;
    };
    auto it = std::find_if(renderers.begin(), renderers.end(), isCurrent);
    currentRenderer = (--it)->get();
    currentRenderer->start();
}
