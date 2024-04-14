#include <memory.h>
#include "frame/general.h"

static size_t buffer_size(const u8 *data) {
    return (size_t)sizeof(data) / sizeof(* data);
}

general_t general_unpack(u8 *data) {
    general_t result;
    result.invalid_frame = false;

    u8 header[2] = {data[0], data[1]};
    result.header = header_unpack(header);
    result.payload_size = header_payload_length(&result.header);

    if (result.payload_size <= 0)
        return result;

    memcpy(result.payload, data + 2, result.payload_size);
    return result;
}

void general_pack(general_t *general, u8 *data) {
    if (general == null || general->invalid_frame) return;

    data[0] = general->header.length;
    data[1] = general->header.command;

    if (general->payload_size < 1) return;
    memcpy(data+2, general->payload, general->payload_size);
}
