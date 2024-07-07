/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** error
*/

#pragma once

#include <string>
#include <iostream>

#define NEW_ERROR(name)                                                 \
    class name : public std::runtime_error                              \
    {                                                                   \
        public:                                                         \
            name(const std::string &msg) : std::runtime_error(msg) {}   \
    };
