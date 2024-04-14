#ifndef BUS_FRAME_H
#define BUS_FRAME_H

#include <types.h>
#include <frame/header.h>
#include <frame/general.h>

typedef struct {
    u8 sof;
    general_t general;
    u8 fcs;
    bool invalid_frame;
    bool invalid_checksum;
} transport_frame_t;

extern transport_frame_t transport_frame_unpack(u8 *data, u8 len);
extern void transport_pack(transport_frame_t *frame, u8 *data);

/**
 * @brief Calculate the Frame Check Sequence (FCS).
 *
 * This function calculates the FCS for a given payload.
 * FCS is calculated based on payload length.
 *
 * @param payload Pointer to the payload data.
 * @param len Length of the payload data.
 * @return Calculated FCS.
 */
extern uchar calc_fcs(const uchar *payload, unsigned char len);


#endif //BUS_FRAME_H
