/*
** EPITECH PROJECT, 2023
** clogger
** File description:
** log writing functions
*/

#include <string.h>
#include "clogger.h"

static void log_buf(FILE *fs, const char *buf)
{
    if (!fs || !buf)
        return;
    fwrite(buf, strlen(buf), 1, fs);
    fwrite("\n", 1, 1, fs);
    fflush(fs);
}

void logger_va_log(logger_t *l, log_level_t lvl, const char *f, va_list args)
{
    char line[LOG_SIZE];
    char level_str[LOG_LEVEL_SIZE];
    size_t written = 0;

    if (!l || lvl < l->level || !f)
        return;
    if (!get_log_level_str(lvl, level_str))
        return;
    written = sprintf(line, "%s%s", level_str, SEP);
    vsnprintf(line + written, LOG_SIZE - written, f, args);
    log_buf(l->fs, line);
    log_buf(l->os, line);
}

void logger_log(logger_t *l, log_level_t lvl, const char *f, ...)
{
    va_list args;

    if (!l || lvl < l->level || !f)
        return;
    va_start(args, f);
    logger_va_log(l, lvl, f, args);
    va_end(args);
}

bool logger_log_true(logger_t *l, log_level_t lvl, const char *f, ...)
{
    va_list args;

    if (!l || lvl < l->level || !f)
        return true;
    va_start(args, f);
    logger_va_log(l, lvl, f, args);
    va_end(args);
    return true;
}

bool logger_log_false(logger_t *l, log_level_t lvl, const char *f, ...)
{
    va_list args;

    if (!l || lvl < l->level || !f)
        return false;
    va_start(args, f);
    logger_va_log(l, lvl, f, args);
    va_end(args);
    return false;
}

void *logger_log_null(logger_t *l, log_level_t lvl, const char *f, ...)
{
    va_list args;

    if (!l || lvl < l->level || !f)
        return NULL;
    va_start(args, f);
    logger_va_log(l, lvl, f, args);
    va_end(args);
    return NULL;
}
