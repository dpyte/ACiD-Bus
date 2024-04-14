#ifndef BUS_TYPES_H
#define BUS_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef unsigned char uchar;

#ifndef null
#   define null ((void*) 0)
#endif

#endif //BUS_TYPES_H
