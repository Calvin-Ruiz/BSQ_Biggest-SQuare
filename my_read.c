/*
** EPITECH PROJECT, 2019
** CPE_BSQ_bootstrap
** File description:
** my_read.c
*/
#include "include/my_read.h"

static char *my_extractor(strchain_t *chain, long int len)
{
    long int dec = (len / DATALEN) * DATALEN;
    long int i = -1;
    strchain_t *temp;
    char *buffer = malloc(len + 1);

    while (len > DATALEN) {
        while (++i < DATALEN)
            buffer[i] = chain->data[i];
        len -= DATALEN;
        buffer += DATALEN;
        temp = chain->next;
        free(chain);
        chain = temp;
        i = -1;
    }
    while (++i < len)
        buffer[i] = chain->data[i];
    free(chain);
    buffer[i] = '\0';
    return (buffer - dec);
}

char *my_read(const int port, long int *full_size)
{
    strchain_t *chain;
    strchain_t *temp;
    char *buff = malloc(DATALEN);
    int size = read(port, buff, DATALEN);
    if (size == -1)
        return (NULL);
    *full_size = size;
    chain = malloc(sizeof(*chain));
    temp = chain;
    chain->data = buff;
    while (size == DATALEN) {
        buff = malloc(DATALEN);
        size = read(port, buff, DATALEN);
        temp->next = malloc(sizeof(*temp));
        temp = temp->next;
        temp->data = buff;
        *full_size += size;
    }
    char *buffer = my_extractor(chain, *full_size);
    return (buffer);
}
