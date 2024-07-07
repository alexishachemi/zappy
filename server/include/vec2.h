/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Vector2
*/

#pragma once
#include <stdbool.h>

#define VEC2_UP ((vec2_t){0, 1})
#define VEC2_DOWN ((vec2_t){0, -1})
#define VEC2_LEFT ((vec2_t){-1, 0})
#define VEC2_RIGHT ((vec2_t){1, 0})

typedef struct {
    int x;
    int y;
} vec2_t;

typedef struct {
    unsigned int id;
    vec2_t direction;
} direction_map_t;

typedef struct {
    vec2_t up;
    int ids[8];
} id_map_t;

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_mul(vec2_t a, vec2_t b);
vec2_t vec2_div(vec2_t a, vec2_t b);

int vec2_direction_to_id(vec2_t direction);
int vec2_rotate_id(unsigned int id, vec2_t current_up, vec2_t desired_up);
vec2_t vec2_rotate_dir_left(vec2_t a);
vec2_t vec2_rotate_dir_right(vec2_t a);
int vec2_dir_to_gui_orientation(vec2_t vec);

void vec2_print(vec2_t vec);
bool vec2_eq(vec2_t a, vec2_t b);
bool vec2_ptr_eq(void *v1, void *v2);
void *alloc_vec2(void);
