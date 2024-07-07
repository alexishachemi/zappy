/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Argument
*/

#include "arg.hpp"

arg::Argument::Argument(const arg_t *arg)
    : arg(arg)
{
    if (!arg)
        throw ArgumentError("Initializer arg_t is NULL. "
            "Perhaps you tried to get a flag that wasn't parsed ?");
}

std::vector<std::string> arg::Argument::toList() const
{
    list_t list;
    std::vector<std::string> strList;

    list_init(&list);
    if (!arg_as_list(arg, &list))
        throw std::bad_alloc();
    for (node_t *n = list.head; n; n = n->next) {
        strList.push_back((char *)n->data);
    }
    list_clear_free(&list);
    return strList;
}

arg::Argument::operator int() const
{
    return arg_as_int(arg);
}

arg::Argument::operator float() const
{
    return arg_as_float(arg);
}

arg::Argument::operator std::string() const
{
    return arg_as_string(arg);
}

arg::Argument::operator bool() const
{
    return arg_as_bool(arg);
}

arg::Argument::operator std::vector<std::string>() const
{
    return toList();
}
