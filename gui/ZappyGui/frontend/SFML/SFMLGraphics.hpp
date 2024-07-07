/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** frontend
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <sstream>
#include "IGraphics.hpp"
#include "error.hpp"
#include "ThemeManager.hpp"

namespace gui
{
    class SFMLGraphics: public IGraphics
    {
        public:
            SFMLGraphics();
            ~SFMLGraphics();

            /// @brief create window
            /// @param win window variable
            /// @return 0 for success or 1 for error
            int initWindow();

            /// @brief close window
            void deinitWindow();

            /// @brief define the zoom of the window
            void windowZoom(const Backend &b);

            /// @brief window loop
            /// @param b backend datas
            bool update(const Backend &b) override;

            /// @brief draw main funcction
            /// @param b backend datas
            void draw(const Backend &b);

            /// @brief draw map tiles
            /// @param b backend datas
            void drawMap(const Backend &b);

            /// @brief initialisation of the outline tiles sprites
            void initCorner();

            /// @brief draw outline map tiles
            /// @param b backend datas
            void drawCorner(const Backend &b);

            /// @brief initalisation of the ressources sprites
            void initResources();

            /// @brief draw the sprite of all the ressources
            /// @param b backend datas
            /// @param tile tile where we want to draw his ressourses
            void drawResources(const Backend &b, const Tile &tile);

            /// @brief initalisation of the player sprites
            void initPlayer();

            /// @brief draw the sprite of all the players
            /// @param b backend datas
            /// @param tile tile where we want to draw the player if he is here
            void drawPlayer(const Backend &b, const Tile &tile);

            /// @brief initialisation of the egg sprite
            void initEgg();

            /// @brief draw the egg of all the egg
            /// @param b backend datas
            /// @param tile tile where the egg could be
            void drawEgg(const Backend &b, const Tile &tile);

            sf::Sprite CreateSprite(sf::Texture &texture, gui::Vec2 recPos);

            /// @brief draw the sprite given in parametter at the right positions
            /// @param b backend datas
            void drawSprite(sf::Sprite sprite, sf::Vector2f pos);

            void drawTileInfo(const Backend &b);

            /// @brief event handler
            /// @param b backend datas
            void eventHandler(const Backend &b);
            bool DefaultMod();
            bool DoomMod();
            bool MinecraftMod();

            /// @brief initialisation of the mouse
            void initMouse();

            /// @brief mouse event handler
            void handleMouseEvents(const Backend &b);

            /// @brief keyboard event handler
            void handleKeyboardEvents(const Backend &b);

            /// @brief loadTexture asset
            /// @return  // true if the texture is loaded
            sf::Texture loadTexture(std::string path);

            /// @brief setting up sprite and orientation
            /// @return  // true if the texture is loaded
            sf::Sprite loadSprite(sf::Texture text, sf::Vector2f pos);

            sf::Font loadFont(std::string path);

            /// @brief window
            sf::RenderWindow _win;

            void initSound();
            sf::SoundBuffer loadSound(const std::string &path);
            void playLevelUpSound();

            sf::Sound CreateSound(std::string path);
    
        private:
    
            /// @brief loaders variables
            bool texture_loaded = true;
            bool sprite_loaded = false;
            bool font_loaded = false;
            sf::Texture *textureA;
            sf::Sprite spriteA;
            sf::Font font;

            /// @brief sprite rect of the differents entity
            std::map<gui::Item, sf::IntRect> resourceRects;
            std::map<gui::Orientation, std::map<int, sf::IntRect>> playerRects;
            std::map<gui::Orientation, std::map<int, sf::IntRect>> elevatingPlayerRects;
            sf::IntRect EggRects;
            std::map<int, sf::IntRect> CornerRect;

            /// @brief other variables
            int tileSize = 64;
            sf::Event _event;
            sf::Vector2f mouse;
            sf::View view;
            bool mouseOnTile;
            sf::Vector2f mousePosOnTile;
            bool clickedOnTile = false;
            gui::Vec2 clickedTilePos;
            sf::Color bgColor;

            /// @brief theme
            int volume = 30;
            sf::SoundBuffer SoundBuffer;

            bool grid = true;
            ThemeManager themeManager;
            void updateAtlas();
    };
    NEW_ERROR(ErrorTextureLoading);
    NEW_ERROR(ErrorFontLoading);
}
