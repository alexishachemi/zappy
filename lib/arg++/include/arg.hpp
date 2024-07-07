/*
** EPITECH PROJECT, 2024
** arg++
** File description:
** header
*/

#pragma once

extern "C" {
    #include "arg.h"
}
#include <iostream>
#include <string>
#include <vector>

namespace arg
{
    class Argument
    {
        const arg_t *arg;

        public:
            Argument(const arg_t *arg);

            std::vector<std::string> toList() const;

            operator int() const;
            operator float() const;
            operator std::string() const;
            operator bool() const;
            operator std::vector<std::string>() const;

            class ArgumentError: public std::runtime_error
            {
                public:
                    ArgumentError(const std::string &msg) : std::runtime_error(msg) {}
            };
    };

    class Parser
    {
        argm_t argm;

        public:
            Parser();
            Parser(std::size_t args_len, const char **args);
            ~Parser();

            bool expectList(const std::string &flagName);
            bool parse(std::size_t args_len, const char **args);
            Argument get(const std::string &name) const;
            bool has(const std::string &name) const;

            Argument operator[](const std::string &name) const;

            class ParserError: public std::runtime_error
            {
                public:
                    ParserError(const std::string &msg) : std::runtime_error(msg) {}
            };
    };
}
