#include <frame/buffer.h>
#include <memory.h>


buffer_t buffer_from_data(u8 *data, u8 len) {
    buffer_t retval = { .len = 0 };
    if (data == null) return retval;

    memcpy(&retval.data, data, len);

    return retval;
}

u8 buffer_length(buffer_t *buffer) {
    if (buffer == null) return 0;
    return buffer->len;
}

void buffer_data(u8 *dst, buffer_t *buffer) {
    if (buffer == null) return;
    memcpy(dst, buffer->data, buffer->len);
}

void buffer_append_data(buffer_t *buffer, u8 data) {
    if (buffer == null) return;
    // todo: avoid pitfall here
    buffer->len++;
    buffer->data[buffer->len] = data;
}

void buffer_append_arr(buffer_t *buffer, u8 *data, u8 len) {
    if (buffer == NULL || data == NULL) return;
    // todo: avoid pitfall here
    memcpy(&buffer->data[buffer->len], data, len);
    buffer->len += len;
}

void buffer_clear(buffer_t *buffer) {
    if (buffer == null) return;
    memset(buffer->data, 0x0, buffer->len);
    buffer->len = 0;
}

u8 buffer_at(buffer_t *buffer, u8 loc) {
    if (buffer == null || loc > buffer->len) return 0;
    return buffer->data[loc];
}
