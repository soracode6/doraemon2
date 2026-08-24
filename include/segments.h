#ifndef SEGMENTS_H
#define SEGMENTS_H

#include "ultra64.h"

#define DECLARE_SEGMENT(name) \
extern u8 name##_start[];\
extern u8 name##_end[];

#define SEGMENT(segment) segment##_start
#define SEGMENT_SIZE(segment) ((u32)segment##_end - (u32)segment##_start)

DECLARE_SEGMENT(D_CBE40); // 0x48110

extern u8* D_80121050;

#endif
