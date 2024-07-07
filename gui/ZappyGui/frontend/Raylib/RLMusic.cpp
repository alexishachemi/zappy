/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** RLMusic
*/

#include "RLMusic.hpp"

gui::RLMusic::~RLMusic()
{
    unload();
}

bool gui::RLMusic::load(const std::filesystem::path &path)
{
    if (loaded)
        unload();
    music = LoadMusicStream(path.string().c_str());
    if (!music.stream.buffer)
        return false;
    loaded = true;
    return true;
}

bool gui::RLMusic::load(const std::vector<std::filesystem::path> &path)
{
    for (const auto &p : path) {
        if (load(p))
            return true;
    }
    return false;
}

void gui::RLMusic::unload()
{
    if (loaded) {
        stop();
        UnloadMusicStream(music);
        loaded = false;
    }
}

void gui::RLMusic::play()
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    if (playing)
        return;
    PlayMusicStream(music);
    playing = true;
    paused = false;
}

void gui::RLMusic::stop()
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    if (!playing)
        return;
    StopMusicStream(music);
    playing = false;
}

void gui::RLMusic::pause()
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    if (!playing || paused)
        return;
    PauseMusicStream(music);
    paused = true;
}

void gui::RLMusic::resume()
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    if (!playing || !paused)
        return;
    ResumeMusicStream(music);
    paused = false;
}

void gui::RLMusic::update()
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    if (!playing)
        return;
    UpdateMusicStream(music);
}

void gui::RLMusic::setVolume(float volume)
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    SetMusicVolume(music, volume);
}

float gui::RLMusic::getVolume() const
{
    if (!loaded)
        throw RLMusicError("Music not loaded");
    return volume;
}

bool gui::RLMusic::isPlaying() const
{
    return playing;
}
