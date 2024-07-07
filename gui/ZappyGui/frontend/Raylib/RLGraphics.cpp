/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLGraphics
*/

#include "RLGraphics.hpp"
#include "raymath.h"

const unsigned int gui::RLGraphics::maxFps = 60;
const Vector2 gui::RLGraphics::screenSize = {800, 600};
const ConfigFlags gui::RLGraphics::configFlags = FLAG_WINDOW_RESIZABLE;

gui::RLGraphics::RLGraphics()
    : animationCounter(0)
{
    SetConfigFlags(configFlags);
    InitAudioDevice();
    InitWindow(screenSize.x, screenSize.y, "Zappy - RayLib");
    SetExitKey(0);
    SetTargetFPS(maxFps);
    rendererManager.init();
    rendererManager.getRenderer()->start();
}

gui::RLGraphics::~RLGraphics()
{
    CloseWindow();
    CloseAudioDevice();
}

bool gui::RLGraphics::update(const Backend &be)
{
    IRLRenderer *renderer = rendererManager.getRenderer();
    
    handleKeyboardInput(be);
    renderer->update(be);
    BeginDrawing();
    renderer->render(be);
    EndDrawing();
    return !WindowShouldClose();
}

void gui::RLGraphics::handleKeyboardInput(const Backend &be)
{
    if (IsKeyPressed(KEY_RIGHT))
        rendererManager.nextRenderer();
    if (IsKeyPressed(KEY_LEFT))
        rendererManager.previousRenderer(); 
}
