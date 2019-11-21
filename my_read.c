/*
** EPITECH PROJECT, 2019
** CPE_BSQ_bootstrap
** File description:
** my_read.c
*/
#include "include/my_read.h"

static strchain_t *my_reader(const int port, long *full, char *buff, int size)
{
    strchain_t *temp;
    strchain_t *chain;
    chain = malloc(sizeof(*chain));
    if (chain == NULL)
        return (NULL);
    temp = chain;
    chain->data = buff;
    while (size == DATALEN) {
        buff = malloc(DATALEN);
        if (buff == NULL)
            return (NULL);
        size = read(port, buff, DATALEN);
        temp->next = malloc(sizeof(*temp));
        if (temp->next == NULL)
            return (NULL);
        temp = temp->next;
        temp->data = buff;
        *full += size;
    }
    return (chain);
}

static void my_extractor(strchain_t *chain, char *buffer, long int len)
{
    long int i = -1;

    strchain_t *temp;
    while (len > DATALEN) {
        while (++i < DATALEN)
            buffer[i] = chain->data[i];
        len -= DATALEN;
        buffer += DATALEN;
        temp = chain->next;
        free(chain->data);
        free(chain);
        chain = temp;
        i = -1;
    }
    while (++i < len)
        buffer[i] = chain->data[i];
    free(chain->data);
    free(chain);
}

char *my_read(const int port, long int *full_size)
{
    char *buff = malloc(DATALEN);

    if (buff == NULL)
        return (NULL);
    int size = read(port, buff, DATALEN);
    if (size == -1)
        return (NULL);
    *full_size = size;
    strchain_t *chain = my_reader(port, full_size, buff, size);
    if (chain == NULL)
        return (NULL);
    char *buffer = malloc(*full_size);
    if (buffer == NULL)
        return (NULL);
    my_extractor(chain, buffer, *full_size);
    return (buffer);
}
