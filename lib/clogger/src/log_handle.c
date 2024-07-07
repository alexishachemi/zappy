/*
** EPITECH PROJECT, 2023
** clogger
** File description:
** logging functions & utils
*/

#include <string.h>
#include <strings.h>
#include "clogger.h"

static const log_level_str_t log_level_str[] = {
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARN, "WARN"},
    {ERROR, "ERROR"},
    {CRITICAL, "CRITICAL"},
    {0, NULL}
};

static int count_file_lines(const char *path)
{
    int c = 0;
    size_t lines = 1;
    FILE *fs = NULL;

    fs = fopen(path, "r");
    if (!fs)
        return -1;
    c = getc(fs);
    while (c != EOF) {
        if (c == '\n')
            lines++;
        c = getc(fs);
    }
    fclose(fs);
    return lines;
}

void trim_log_file(const char *path)
{
    int lines = 0;
    FILE *fs = NULL;

    if (!path)
        return;
    lines = count_file_lines(path);
    if (lines < LOG_MAX_LINES)
        return;
    fs = fopen(path, "w");
    if (fs)
        fclose(fs);
}

bool get_log_level_str(log_level_t level, char *buf)
{
    if (!buf)
        return false;
    for (int i = 0; log_level_str[i].str; i++) {
        if (log_level_str[i].level == level) {
            strcpy(buf, log_level_str[i].str);
            return true;
        }
    }
    return false;
}

bool logger_set_level(logger_t *logger, log_level_t level)
{
    char level_str[LOG_LEVEL_SIZE];

    if (!logger)
        return false;
    if (!get_log_level_str(level, level_str))
        return false;
    LOG(logger, INFO, "Log level set to %s", level_str);
    logger->level = level;
    return true;
}

bool logger_set_level_str(logger_t *logger, const char *str)
{
    char buf[LOG_LEVEL_SIZE];

    if (!logger || !str)
        return false;
    memset(buf, 0, sizeof(buf));
    for (log_level_t level = DEBUG; level <= CRITICAL; level++) {
        if (get_log_level_str(level, buf) && strcasecmp(str, buf) == 0) {
            LOG(logger, INFO, "Log level set to %s", buf);
            logger->level = level;
            return true;
        }
    }
    return false;
}
