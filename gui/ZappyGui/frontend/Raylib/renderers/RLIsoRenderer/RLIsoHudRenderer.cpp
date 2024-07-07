/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLIsoHudRenderer
*/

#define RAYGUI_IMPLEMENTATION

#include <algorithm>
#include "RLIsoHudRenderer.hpp"
#include "raygui.h"
#include "RLIsoRenderer.hpp"

gui::RLIsoHudRenderer::RLIsoHudRenderer()
{
    for (auto &path : stylePath) {
        if (std::filesystem::exists(path)) {
            GuiLoadStyle(path.c_str());
            loaded = true;
            break;
        }
    }
    if (!loaded)
        throw RLIsoHudRendererError("Failed to load style");
}

void gui::RLIsoHudRenderer::update(const Backend &be, RLIsoRenderer &renderer)
{
    Vec2 cursorPos;
    float sideBarHiddenX = getSideBarHiddenX();
    float sideBarShownX = getSideBarShownX();
    bool tileSelected = renderer.tileSelected(cursorPos);
    
    if (IsKeyPressed(KEY_ESCAPE))
        showSettings = !showSettings;
    if (tileSelected)
        selectedTile = &be.getTile(cursorPos);
    renderScaleF = 2 * (GetScreenWidth() / 800.0f);
    renderScale = {renderScaleF, renderScaleF};
    sideBarCurrentX = std::clamp(sideBarCurrentX, sideBarHiddenX, sideBarShownX);
    if ((sideBarCurrentX == sideBarHiddenX && !tileSelected)
        || (sideBarCurrentX == sideBarShownX && tileSelected)) {
        sideBarClock = 0;
        return;
    }
    sideBarClock += GetFrameTime();
    if (sideBarClock < sideBarMoveTime)
        return;
    sideBarClock = 0;
    if (tileSelected)
        sideBarCurrentX += sideBarSpeed * renderScaleF;
    else
        sideBarCurrentX -= sideBarSpeed * renderScaleF;
    sideBarCurrentX = std::clamp(sideBarCurrentX, sideBarHiddenX, sideBarShownX);
}

void gui::RLIsoHudRenderer::render(const Backend &be, RLIsoRenderer &renderer)
{
    drawSettingsButton(be, renderer);
    if (showSettings) 
        drawSettings(be, renderer);
    else
        drawSideBar(be, renderer, (Vector2){sideBarCurrentX, 10});
}

bool gui::RLIsoHudRenderer::isPaused() const
{
    return showSettings;
}

int gui::RLIsoHudRenderer::getSideBarHiddenX() const
{
    return -(GetScreenWidth() / 5) - 10;
}

int gui::RLIsoHudRenderer::getSideBarShownX() const
{
    return 10;
}

void gui::RLIsoHudRenderer::drawSideBar(const Backend &be, RLIsoRenderer &renderer, Vector2 position)
{
    Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
    Vec2 cursorPos;
    if (screenSize.x < 500 || screenSize.y < 500 || !selectedTile)
        return;
    std::string tilePosStr = std::to_string(selectedTile->pos.x) + " - " + std::to_string(selectedTile->pos.y);
    Rectangle rect = {
        position.x,
        position.y,
        screenSize.x / 5,
        screenSize.y - (position.y * 2)
    };
    Vector2 tileRender = {
        rect.x + (rect.width / 2) - ((renderer.getAtlas().getCellSize() * renderScaleF) / 2),
        rect.y + (25 * renderScaleF)
    };
    Vector2 textSize = MeasureTextEx(GetFontDefault(), tilePosStr.c_str(), 20 * renderScaleF, 1);
    Vector2 textPos = {
        rect.x + (rect.width / 2) - (textSize.x / 2),
        tileRender.y + (35 * renderScaleF)
    };
    Vector2 itemPos = {rect.x + (-5.0f * renderScaleF), textPos.y + (textSize.y - 10 * renderScaleF)};

    GuiPanel(rect, "Current Tile");
    renderer.drawTile(*selectedTile, tileRender, renderScale);
    DrawTextEx(GetFontDefault(), tilePosStr.c_str(), textPos, 20 * renderScaleF, 1, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    for (Item i = Item::FOOD; i <= Item::THYSTAME; i = static_cast<Item>(i + 1)) {
        if (!selectedTile->inventory[i])
            continue;
        renderer.drawItem(i, itemPos, renderScale);
        textPos.y = itemPos.y + (12 * renderScaleF);
        textPos.x = itemPos.x + (renderer.getAtlas().getCellSize() * renderScaleF / 1.3f);
        DrawTextEx(GetFontDefault(), to_string(i).c_str(), textPos, 8 * renderScaleF, 1, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
        textPos.x = (rect.x + rect.width) - (7 * renderScaleF);
        DrawTextEx(GetFontDefault(), std::to_string(selectedTile->inventory[i]).c_str(), textPos, 10 * renderScaleF, 1, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
        itemPos.y += 18 * renderScaleF;
    }
}

void gui::RLIsoHudRenderer::drawSettingsButton(const Backend &be, RLIsoRenderer &renderer)
{
    Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
    if (screenSize.x < 100 || screenSize.y < 100)
        return;
    Vector2 position = {screenSize.x - 40, 10};
    Rectangle rect = {position.x, position.y, 30, 30};

    if (GuiButton(rect, GuiIconText(ICON_PLAYER_PAUSE, NULL)))
        showSettings = !showSettings;
}

void gui::RLIsoHudRenderer::drawSettings(const Backend &be, RLIsoRenderer &renderer)
{
    Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
    if (screenSize.x < 500 || screenSize.y < 500) {
        showSettings = false;
        return;
    }
    Rectangle rect = {screenSize.x / 2 - 200, screenSize.y / 2 - 200, 400, 400};

    int closed = GuiWindowBox(rect, "Settings");
    if (closed) {
        showSettings = false;
        return;
    }
    DrawText("Zappy", rect.x + (rect.width / 2) - 53, rect.y + 30, 40, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    drawToggles(be, renderer, rect);
    drawSliders(be, renderer, rect);
}

void gui::RLIsoHudRenderer::drawSliders(const Backend &be, RLIsoRenderer &renderer, Rectangle rect)
{
    RLMusic &music = renderer.getMusic();
    Rectangle sliderRect = {rect.x + 30, rect.y + 130, rect.width - 60, 20};
    std::string volumeStr = std::to_string(static_cast<int>(volume * 100));

    GuiDrawText(GuiIconText(ICON_AUDIO, "Volume"), {sliderRect.x, sliderRect.y - 20, 100, 20}, 0, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    GuiSlider(sliderRect, volumeStr.c_str(), NULL, &volume, 0, 1);
    if (volume != music.getVolume())
        music.setVolume(volume);
}

void gui::RLIsoHudRenderer::drawToggles(const Backend &be, RLIsoRenderer &renderer, Rectangle rect)
{
    Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
    Rectangle toggleRect = {rect.x + rect.width - 50, rect.y + 170, 20, 20};
    bool showOcean = renderer.getShowOcean();
    bool showItems = renderer.getShowItems();
    bool showEggs = renderer.getShowEggs();

    GuiDrawText(GuiIconText(ICON_WATER_DROP, "Show Ocean (O)"), {rect.x + 10, toggleRect.y, 120, 20}, 0, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    GuiToggle(toggleRect, NULL, &showOcean);
    if (showOcean != renderer.getShowOcean())
        renderer.setShowOcean(showOcean);
    toggleRect.y += 40;
    GuiDrawText(GuiIconText(ICON_COIN, "Show Items (I)"), {rect.x + 10, toggleRect.y, 120, 20}, 0, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    GuiToggle(toggleRect, NULL, &showItems);
    if (showItems != renderer.getShowItems())
        renderer.setShowItems(showItems);
    toggleRect.y += 40;
    GuiDrawText(GuiIconText(ICON_DOOR, "Show Portals (P)"), {rect.x + 10, toggleRect.y, 120, 20}, 0, GetColor(GuiGetStyle(LABEL, TEXT + (guiState * 3))));
    GuiToggle(toggleRect, NULL, &showEggs);
    if (showEggs != renderer.getShowEggs())
        renderer.setShowEggs(showEggs);
}
