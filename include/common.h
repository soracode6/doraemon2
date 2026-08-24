#ifndef COMMON_H
#define COMMON_H

#include "ultra64.h"

// D_800F5FB0_struct in doraemon1
typedef struct D_8011C1C8_struct { 
    u32 unk0;
    s32 unk4;
    u32 unk8;
    u8 unkC;
}D_8011C1C8_struct;

extern D_8011C1C8_struct D_8011C1C8;

typedef struct D_80117AC8_struct{
    s16 unk0;
    s16 unk2;
}D_80117AC8_struct;

extern D_80117AC8_struct D_80117AC8;

#define D_8011C1C8_sets(arg0, arg1, arg2) D_8011C1C8.unk0 = (arg0);D_8011C1C8.unkC = (arg1);D_8011C1C8.unk4 = (arg2)

#endif
