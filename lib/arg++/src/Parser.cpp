/*
** EPITECH PROJECT, 2024
** arg++
** File description:
** Parser
*/

#include "arg.hpp"

arg::Parser::Parser()
{
    argm_init(&argm);
}

arg::Parser::Parser(std::size_t args_len, const char **args)
{
    argm_init(&argm);
    if (!argm_parse(&argm, args_len, args))
        throw ParserError("Failed to parse arguments at initialization");
}

arg::Parser::~Parser()
{
    argm_deinit(&argm);
}

bool arg::Parser::expectList(const std::string &flagName)
{
    return argm_expect_list(&argm, flagName.c_str());
}

bool arg::Parser::parse(std::size_t args_len, const char **args)
{
    return argm_parse(&argm, args_len, args);
}

arg::Argument arg::Parser::get(const std::string &name) const
{
    return Argument(argm_get(&argm, name.c_str()));
}

bool arg::Parser::has(const std::string &name) const
{
    return argm_has(&argm, name.c_str());
}

arg::Argument arg::Parser::operator[](const std::string &name) const
{
    return get(name);
}
