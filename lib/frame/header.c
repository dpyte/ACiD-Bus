#include "frame/header.h"

static size_t buffer_size(const u8 *data) {
    return (size_t)sizeof(data) / sizeof(* data);
}

header_t header_from_bytes(const uchar *data) {
    header_t retval = {.length = data[0], .command = data[1]};
    return retval;
}

action_type_t header_action_type(const header_t *header) {
    const u8 retval = (header->command & 0b11000000) >> 6;
    return retval == 1 ? Pos : Mot;
}

action_dir_t header_action_direction(const header_t *header) {
    const u8 retval = (header->command & 0b00010000) >> 4;
    return (action_dir_t)retval;
}

void header_unpack(const header_t *header, u8 *data) {
    size_t size = buffer_size(data);
    if (size < 8) return;

    data[0] = header->length;
    data[1] = header->command;
}

