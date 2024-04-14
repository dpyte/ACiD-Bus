#include <frame.h>
#include <stdbool.h>
#include <memory.h>

static size_t buffer_size(const u8 *data) {
    return (size_t)sizeof(data) / sizeof(data[0]);
}

static void cpy_general_frame(u8 *general, u8 *data, u8 data_len) {
    memcpy(general, data+1, data_len - 2);
}

transport_frame_t transport_frame_unpack(u8 *data, u8 len) {
    transport_frame_t result = { .invalid_frame = false, .invalid_checksum = false };
    if (len <= 2) {
        result.invalid_frame = true;
        return result;
    }

    u8 general[len-2];
    cpy_general_frame(general, data, len);

    uchar checksum = calc_fcs(general, len-2);
    if (data[len-1] != checksum) {
        result.invalid_frame = true;
        result.invalid_checksum = true;
        return result;
    }

    result.general = general_unpack(general);
    return result;
}

void transport_pack(transport_frame_t *frame, u8 *data) {
    if (frame == null || frame->invalid_frame) return;

    frame->sof = 0xFE;

    u8 gen_len = 2 + frame->general.payload_size;

    u8 general[gen_len];
    general_pack(&frame->general, general);
    frame->fcs = calc_fcs(general, gen_len);

    data[0] = frame->sof;
    memcpy(data+1, general, gen_len);
    data[gen_len+1] = frame->fcs;
}

uchar calc_fcs(const uchar *payload, unsigned char len) {
    unsigned char result = 0;
    if (payload == null) return result;
    while (len--) result ^= *payload++;
    return result;
}
