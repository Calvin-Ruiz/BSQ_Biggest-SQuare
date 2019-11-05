/*
** EPITECH PROJECT, 2019
** CPE_BSQ_bootstrap
** File description:
** BSQ.c
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "include/my_read.h"

typedef unsigned short uint2_t;
typedef long int i8_t;

i8_t *my_find_biggest_square(uint2_t *array, i8_t len, i8_t x, i8_t y)
{
    i8_t *rect = malloc(sizeof(i8_t) * 3);

    return (rect);
}

long int my_getnbr_raws(int fd)
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

unsigned short *my_convert_input(unsigned char *str, long int len)
{
    unsigned short *convert = malloc(256);
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

void my_write_square(long int *rect_data, char *str, i8_t col)
{
    str += rect_data[0] + rect_data[1] * col;
    long int i = -1;
    long int j = -1;

    while (++i < rect_data[2]) {
        j = -1;
        while (++j < rect_data[2]) {
            str[j] = 'x';
        }
        str += col;
    }
}

int main(int nargs, char **args)
{
    if (nargs != 2)
        return (84);
    long int len;
    int fd = open(args[1], O_RDONLY);
    if (fd == -1)
        return (84);
    long int nb_raws = my_getnbr_raws(fd);
    char *str = my_read(fd, &len);
    close(fd);
    long int i = -1;
    while (++i < len && str[i] != '\n');
    if (len != ++i * nb_raws)
        return (84);
    uint2_t *array = my_convert_input((unsigned char *)str, len);
    long int *rect = my_find_biggest_square(array, len, i, nb_raws);
    my_write_square(rect, str, i);
    write(1, str, len);
    return (0);
}
