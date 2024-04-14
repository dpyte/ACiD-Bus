#ifndef BUS_BUFFER_H
#define BUS_BUFFER_H

#include "types.h"

typedef struct {
    u8 data[255];
    u8 len;
} buffer_t;

extern buffer_t buffer_from_data(u8 *data, u8 len);
extern u8 buffer_length(buffer_t *buffer);
extern u8 buffer_at(buffer_t *buffer, u8 loc);
extern void buffer_data(u8 *dst, buffer_t *buffer);
extern void buffer_append_data(buffer_t *buffer, u8 data);
extern void buffer_append_arr(buffer_t *buffer, u8 *data, u8 len);
extern void buffer_clear(buffer_t *buffer);

#endif //BUS_BUFFER_H
