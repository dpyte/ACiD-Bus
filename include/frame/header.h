#ifndef BUS_HEADER_H
#define BUS_HEADER_H

#include <types.h>

typedef enum {
    Positive = 1,
    Negative = 0,
} action_dir_t;

typedef enum {
    Pos = 0b01,
    Mot = 0b10,
} action_type_t;

/**
 * +--------+----------------------+
 * | length |        command       |
 * +--------+----------------------+
 *
 * @var length: length of the payload (1 byte)
 * @var command: command details (1 byte)
 */
typedef struct {
    u8 length;
    u8 command;
} header_t;

extern header_t header_from_bytes(const uchar* data);
extern action_type_t header_action_type(const header_t *header);
extern action_dir_t header_action_direction(const header_t *header);
extern void header_unpack(const header_t *header, u8 *data);

#endif //BUS_HEADER_H
