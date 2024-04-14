#ifndef BUS_GENERAL_H
#define BUS_GENERAL_H

#include <stdbool.h>
#include "header.h"

typedef struct {
    header_t header;
    u8 payload[250];
    u8 payload_size;
    bool invalid_frame;
} general_t;

extern general_t general_unpack(u8 *data);
extern void general_pack(general_t *general, u8 *data);

#endif //BUS_GENERAL_H
