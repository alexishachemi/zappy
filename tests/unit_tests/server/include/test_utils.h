/*
** EPITECH PROJECT, 2024
** linked
** File description:
** test_utils
*/

#ifndef TEST_UTILS_H_
    #define TEST_UTILS_H_

void destroy_int(void *data);
void *allocate_int(void);
void print_int(void *data);
void sum_int(void *acc, void *data);
void inc_int(void *data);
bool int_gt(void *data, void *data2);
bool int_lt(void *data, void *data2);

#endif /* !TEST_UTILS_H_ */
