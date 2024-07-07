/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Backend
*/

#pragma once

#include <map>
#include <memory>
#include "Tile.hpp"
#include "Player.hpp"
#include "Inventory.hpp"
#include "Egg.hpp"

namespace gui
{
    class Backend
    {
        public:
            using Team = std::pair<std::size_t, std::string>;

            Backend();

            void setMapSize(Vec2 size);
            Vec2 getMapSize() const;
            Player &addPlayer(std::size_t id, Vec2 pos, Orientation orient, std::size_t level, const std::string &team);
            Player &getPlayer(std::size_t id);
            void removePlayer(std::size_t id);
            Egg &addEgg(std::size_t id, Vec2 pos, std::size_t teamId);
            Egg &getEgg(std::size_t id);
            void removeEgg(std::size_t id);
            std::size_t addTeam(const std::string &name);
            std::size_t getTeamId(const std::string &name) const;
            std::size_t getTeamId(const std::string &name);
            Tile &addTile(Vec2 pos);
            Tile &getTile(Vec2 pos);
            const Tile &getTile(Vec2 pos) const;
            const std::string &getTeamName(std::size_t id) const;
            void setFrequency(std::size_t freq);
            std::size_t getFrequency() const;

            const std::vector<std::unique_ptr<Player>> &getPlayers() const;
            const std::vector<std::unique_ptr<Egg>> &getEggs() const;
            const std::vector<Team> &getTeams() const;

            const std::vector<Tile>::const_iterator begin() const;
            const std::vector<Tile>::const_iterator end() const;
        
            NEW_ERROR(BackendError);

        private:
            Vec2 mapSize;
            std::size_t freq;
            std::vector<Tile> tiles;
            std::vector<std::unique_ptr<Player>> players;
            std::vector<std::unique_ptr<Egg>> eggs;
            std::vector<Team> teams;

            void resizeMap(Vec2 size);
            void addToMap(Player &player);
            void addToMap(Egg &egg);
    };
}
