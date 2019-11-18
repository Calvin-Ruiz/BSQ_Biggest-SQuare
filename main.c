/*
** EPITECH PROJECT, 2019
** BSQ
** File description:
** main.c
*/
#include "include/my_read.h"
#include "include/main.h"

static long int my_getnbr_raws(int fd)
{
    long int v = 0;
    char c[1];
    int size = read(fd, c, 1);

    if (size == -1)
        return (0);
    while (*c != '\n' && size) {
        if (v < 922337203685477580 && *c >= '0' && *c <= '9') {
            v = *c - '0' + v * 10;
        } else
            return (0);
        size = read(fd, c, 1);
    }
    return (v);
}

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

static int my_find_and_put_bsq(char *str, long int len, long int i)
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
    if (str == NULL)
        return (84);
    long int i = -1;
    while (++i < len && str[i] != '\n');
    long int j = i;
    while (j < len && str[i] == '\n')
        j += i;
    if (len != ++i * nb_raws && j == len)
        return (84);
    int exit_mode = my_find_and_put_bsq(str, len, i);
    return (exit_mode);
}
