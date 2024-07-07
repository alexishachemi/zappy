/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** read
*/

#include <string.h>
#include <stdlib.h>
#include "socknet_dev.h"

static void validate_line(char *line)
{
    char *end = NULL;

    if (!line)
        return;
    end = strchr(line, '\r');
    if (end)
        *end = 0;
}

static char *handle_read_fail(char *line)
{
    if (line)
        free(line);
    return NULL;
}

char *net_read_fd(int fd)
{
    size_t max_size = 0;
    int size = 0;
    char buf[DATA_CHUNK + 1];
    char *line = NULL;

    memset(buf, 0, DATA_CHUNK + 1);
    while (!line || size == DATA_CHUNK) {
        size = read(fd, buf, DATA_CHUNK);
        if (size <= 0)
            return handle_read_fail(line);
        buf[size] = 0;
        line = realloc(line, max_size + size + 1);
        if (!line)
            return NULL;
        memset(line + max_size, 0, size);
        strcat(line, buf);
        max_size += size;
    }
    validate_line(line);
    return line;
}
