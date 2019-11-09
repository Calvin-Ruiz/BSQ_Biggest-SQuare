/*
** EPITECH PROJECT, 2019
** BSQ
** File description:
** my_find_biggest_square.c
*/
#include "include/main.h"
#include <stdlib.h>

static i8_t my_check_square(uint2_t *array, uint2_t *array0, i8_t *rect, i8_t x)
{
    uint2_t *array_base_pos = array;
    long int i = -1;

    while (i++ < rect[1]) {
        if (*array <= rect[1])
            return (*array + 1);
        array += x;
    }
    rect[0] = array_base_pos - array0;
    rect[1]++;
    return (0);
}

i8_t *my_find_biggest_square(uint2_t *array, i8_t len, i8_t x)
{
    if (array == NULL)
        return (NULL);
    uint2_t *array_end = array + len;
    uint2_t *array_begin = array;
    i8_t *rect = malloc(sizeof(i8_t) * 2);

    if (rect == NULL)
        return (NULL);
    rect[0] = 0;
    rect[1] = 0;
    while (array < (array_end - rect[1] * x))
        array = array + my_check_square(array, array_begin, rect, x);
    free(array_begin);
    return (rect);
}
