/*
** EPITECH PROJECT, 2019
** BSQ
** File description:
** main.c
*/
#include "include/my_read.h"
#include "include/main.h"

static i8_t *my_find_biggest_square(uint2_t *array, i8_t len, i8_t x)
{
    uint2_t *array_end = array + len;
    uint2_t *array_begin = array;
    i8_t *rect = malloc(sizeof(i8_t) * 2);

    rect[0] = 0;
    rect[1] = 0;
    while (array < (array_end - rect[1] * x)) {
        array = array + my_check_square(array, array_begin, rect, x);
    }
    return (rect);
}

static long int my_getnbr_raws(int fd)
{
    long int v = 0;
    char c[1];
    int size = read(fd, c, 1);
    while (*c != '\n' && size) {
        if (v < 922337203685477580 && *c >= '0' && *c <= '9') {
            v = *c - '0' + v * 10;
        } else
            return (0);
        size = read(fd, c, 1);
    }
    return (v);
}

static unsigned short *my_convert_input(unsigned char *str, long int len)
{
    uint2_t *convert = malloc(sizeof(uint2_t) * 256);
    int i = -1;
    unsigned short *array = malloc(sizeof(short) * len);

    while (++i < 256)
        convert[i] = 1;
    convert['.'] = 0;
    i = -1;
    while (++i < len) {
        array[i] = convert[str[i]];
    }
    free(convert);
    i = len;
    while (i-- > 0) {
        array[i] = array[i] ? 0 : array[i + 1] + 1;
    }
    return (array);
}

static void my_write_square(long int *rect_data, char *str, i8_t col)
{
    str += rect_data[0];
    long int i = -1;
    long int j = -1;

    while (++i < rect_data[1]) {
        j = -1;
        while (++j < rect_data[1]) {
            str[j] = 'x';
        }
        str += col;
    }
}

int main(int nargs, char **args)
{
    if (nargs != 2)
        return (84);
    int fd = open(args[1], O_RDONLY);
    if (fd == -1)
        return (84);
    long int len;
    long int nb_raws = my_getnbr_raws(fd);
    char *str = my_read(fd, &len);
    close(fd);
    long int i = -1;
    while (++i < len && str[i] != '\n');
    if (len != ++i * nb_raws)
        return (84);
    uint2_t *array = my_convert_input((unsigned char *)str, len);
    long int *rect = my_find_biggest_square(array, len, i);
    my_write_square(rect, str, i);
    write(1, str, len);
    return (0);
}
