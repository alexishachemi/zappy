/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GraphicsFactory
*/

#pragma once

#include <vector>
#include <functional>
#include "SFMLGraphics.hpp"
#include "error.h"

namespace gui
{
    class GraphicsFactory
    {
        public:
            using CreatorFunction = std::function<std::unique_ptr<IGraphics>()>;

            GraphicsFactory();
            void registerGraphics(const std::string &name, CreatorFunction creator);
            void removeGraphcis(const std::string &name);
            std::unique_ptr<IGraphics> createGraphics(const std::string &name);

            NEW_ERROR(GraphicsFactoryError);

        private:
            std::vector<std::pair<std::string, CreatorFunction>> creators;
    
            CreatorFunction &getCreator(const std::string &name);
    };
}