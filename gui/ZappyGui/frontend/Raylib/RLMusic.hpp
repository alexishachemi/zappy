/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLMusic
*/

#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "raylib.h"
#include "error.hpp"
#include "Vec2.hpp"

namespace gui
{
    class RLMusic
    {
        bool loaded = false;
        bool playing = false;
        bool paused = false;
        float volume = 1.0f;
        Music music;

        public:
            ~RLMusic();
            bool load(const std::filesystem::path &path);
            bool load(const std::vector<std::filesystem::path> &path);
            void unload();
            void play();
            void stop();
            void pause();
            void resume();
            void update();
            void setVolume(float volume);
            float getVolume() const;
            bool isPlaying() const;

            NEW_ERROR(RLMusicError);
    };
}
