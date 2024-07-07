/*
** EPITECH PROJECT, 2023
** clogger
** File description:
** initializing functions
*/

#include <string.h>
#include "clogger.h"

bool logger_init(logger_t *l, const char *path,
    bool clear_file, FILE *os)
{
    if (!l)
        return false;
    memset(l, 0, sizeof(logger_t));
    l->level = INFO;
    l->os = os;
    if (!path)
        return true;
    if (clear_file) {
        l->fs = fopen(path, "w");
        if (l->fs)
            fclose(l->fs);
    }
    trim_log_file(path);
    l->fs = fopen(path, "a");
    return l->fs != NULL;
}

void logger_deinit(logger_t *l)
{
    if (l && l->fs) {
        fclose(l->fs);
        l->fs = NULL;
    }
    if (l)
        l->os = NULL;
}
