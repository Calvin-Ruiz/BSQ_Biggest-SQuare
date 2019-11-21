/*
** EPITECH PROJECT, 2019
** CPE_BSQ_bootstrap
** File description:
** my_read.h
*/

#ifndef MY_READ_H_
#define MY_READ_H_

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DATALEN 4096

typedef struct strchain {
    char *data;
    struct strchain *next;
} strchain_t;

char *my_read(const int port, long int *full_size);

#endif /* MY_READ_H_ */
