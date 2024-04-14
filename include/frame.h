#ifndef BUS_FRAME_H
#define BUS_FRAME_H

#include <types.h>

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
