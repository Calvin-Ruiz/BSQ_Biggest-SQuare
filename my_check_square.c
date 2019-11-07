/*
** EPITECH PROJECT, 2019
** BSQ
** File description:
** my_check_square.c
*/
#include "include/main.h"

long int my_check_square(uint2_t *array, uint2_t *array0, i8_t *rect, i8_t x)
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
