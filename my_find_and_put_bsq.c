/*
** EPITECH PROJECT, 2019
** BSQ
** File description:
** my_find_biggest_square.c
*/
#include "include/main.h"
#include <stdlib.h>

static uint2_t *my_convert_input(unsigned char *str, long int len, uint2_t *chk)
{
    uint2_t *convert = malloc(sizeof(uint2_t) * 256);
    long int i = -1;
    uint2_t *array = malloc(sizeof(uint2_t) * len);
    if (array == NULL || convert == NULL)
        return (NULL);
    while (++i < 256)
	convert[i] = 2;
    convert['.'] = 0;
    convert['\n'] = 1;
    convert['o'] = 1;
    i = -1;
    while (++i < len) {
	array[i] = convert[str[i]];
        *chk = *chk | array[i];
    }
    free(convert);
    i = len;
    while (i-- > 0)
        array[i] = array[i] ? 0 : array[i + 1] + 1;
    return (array);
}

static void my_write_square(long *rect_data, char *str, i8_t col)
{
    str += rect_data[0];
    long int i = -1;
    long int j = -1;

    while (++i < rect_data[1]) {
        j = -1;
        while (++j < rect_data[1])
            str[j] = 'x';
        str += col;
    }
}

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

static i8_t *my_find_biggest_square(uint2_t *array, i8_t len, i8_t x)
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

int my_find_and_put_bsq(char *str, long int len, long int i)
{
    unsigned short check = 0;
    uint2_t *array = my_convert_input((unsigned char *)str, len, &check);
    long int *rect = my_find_biggest_square(array, len, i);

    if (rect == NULL || (check & 2)) {
        free(str);
        return (84);
    }
    my_write_square(rect, str, i);
    write(1, str, len);
    free(str);
    free(rect);
    return (0);
}
