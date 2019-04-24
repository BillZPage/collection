
#include "fifo.h"

#include <stdlib.h>
#include <stdio.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

struct fifo_t *fifo_alloc(uint32_t size)
{
    struct fifo_t *fifo = (struct fifo_t *)malloc(sizeof(struct fifo_t));
    fifo->buffer = (uint8_t *)malloc(size);
    fifo->capacity = size;
    fifo->current = 0;
    fifo->size = 0;

    return fifo;
}

void fifo_free(struct fifo_t *fifo)
{
    free(fifo->buffer);
    free(fifo);
}

void fifo_put(struct fifo_t *fifo, uint8_t *buffer, uint32_t len)
{
    uint32_t copy;

    if(fifo == NULL || buffer == NULL || len > fifo->capacity) {
            printf("invalid fifo put para\n");
            return;
    }

    copy = min(len, fifo->capacity - fifo->current);

    memcpy(fifo->buffer + fifo->current, buffer, copy);
    fifo->current += copy;
    if(fifo->current == fifo->capacity)
        fifo->current = 0;

    memcpy(fifo->buffer + fifo->current, buffer + len - copy, len - copy);
    fifo->current += len - copy;

    fifo->size += len;
    if(fifo->size > fifo->capacity)
        fifo->size = fifo->capacity;
}

int fifo_get(struct fifo_t *fifo, uint8_t *buffer, uint32_t len)
{
    uint32_t copy;

    if(fifo == NULL || buffer == NULL || len > fifo->capacity) {
            printf("invalid fifo put para\n");
            return;
    }

    if(fifo->size < len)
    {
        printf("fifo do not have enough data\n");
        return -1;
    }

    copy = min(fifo->current, len);
    memcpy(buffer + len - copy, fifo->buffer + fifo->current - copy, copy);
    fifo->current -= copy;
    if(fifo->current == 0)
        fifo->current = fifo->size;

    memcpy(buffer, fifo->buffer + fifo->current - (len - copy), len - copy);

    fifo->size -= len;

    return 0;
}

void fifo_reset(struct fifo_t *fifo)
{
    memset(fifo->buffer, 0, fifo->capacity);
    fifo->current = 0;
    fifo->size = 0;
}
