/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** strmcat
*/

#include <stdlib.h>
#include <string.h>

char *strmcat(char **dest_ptr, const char *src)
{
    size_t dest_size = 0;
    size_t src_size = 0;

    if (!dest_ptr)
        return NULL;
    if (!src || !*src)
        return *dest_ptr;
    dest_size = *dest_ptr ? strlen(*dest_ptr) : 0;
    src_size = strlen(src);
    *dest_ptr = realloc(*dest_ptr, src_size + dest_size + 1);
    if (!*dest_ptr)
        return NULL;
    memset(*dest_ptr + dest_size, 0, src_size);
    return strcat(*dest_ptr, src);
}
