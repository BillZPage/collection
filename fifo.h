
#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

struct fifo_t {
    uint8_t *buffer;
    uint32_t capacity;
    uint32_t current;
    uint32_t size;
};

struct fifo_t *fifo_alloc(uint32_t size);
void fifo_put(struct fifo_t *fifo, uint8_t *buffer, uint32_t len);
int fifo_get(struct fifo_t *fifo, uint8_t *buffer, uint32_t len);
void fifo_reset(struct fifo_t *fifo);

#endif // FIFO_H
