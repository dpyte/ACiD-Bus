#include <frame.h>

uchar calc_fcs(const uchar *payload, unsigned char len) {
    unsigned char result = 0;
    while (len--) result ^= *payload++;
    return result;
}
