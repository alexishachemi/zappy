/*
** EPITECH PROJECT, 2023
** clogger
** File description:
** test
*/

#include "clogger.h"

int main(void)
{
    logger_t logger;

    if (!logger_init(&logger, NULL, true, stdout))
        return 84;
    LOG(&logger, WARN, "Hello, world!");
    logger_deinit(&logger);
    return 0;
}
