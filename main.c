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

static int my_checker(long int i, long int len, long int nb_raws, char *str)
{
    long int j = i - 1;

    while (j < len && str[j] == '\n')
        j += i;
    if (len != i-- * nb_raws || j < len)
        return (84);
    j = 1;
    while (++i < len)
        j += str[i] == '\n';
    if (j != nb_raws)
        return (84);
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
    if (my_checker(++i, len, nb_raws, str)) {
        free(str);
        return (84);
    }
    int exit_mode = my_find_and_put_bsq(str, len, i);
    return (exit_mode);
}
