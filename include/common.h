#ifndef COMMON_H
#define COMMON_H

#include "ultra64.h"
#include "PR/sched.h"

typedef void (*D_8011C1C0_struct_unk18C)(s32);

typedef struct D_8011C1C0_struct_unk184{
    u32 unk0;
    u32 unk4;
    u8 unk8[0x8];
    u64 unk10;
    u64 unk18;
    u64 unk20;
    u64 unk28; 
    s32 unk30;
    u32 unk34;
    OSTask unk38;
    OSMesgQueue* unk78;
    u32 unk7C;
}D_8011C1C0_struct_unk184;

typedef struct D_8011C1C8_struct { 
    u32 viMode;
    s32 viSpFeatures;
    u32 unk8;
    u8 retraceCount;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u32 unk10;
    u8 unk14[0x4];
    u64 unk18;
    /*+28*/ OSMesgQueue unk20;
    /*+40*/ OSMesg unk38[8];
    /*+60*/ OSMesgQueue unk58;
    /*+78*/ OSMesg unk70[8];
    /*+98*/ OSMesgQueue preNMIQueue;
    /*+B0*/ OSMesg preNMIMsg[8];
    /*+D0*/ OSMesgQueue rspQueue;
    /*+E8*/ OSMesg rspMsg[8];
    /*+108*/ OSMesgQueue rdpQueue;
    /*+120*/ OSMesg rdpMsg[8];
    /*+140*/ OSMesgQueue unk138;
    /*+158*/ OSMesg unk150[8];
}D_8011C1C8_struct;

typedef struct D_8011C1C0_struct{
    u32 unk0;
    u8 unk4;
    D_8011C1C8_struct unk8;
    u16 unk178;
    u16 unk17A;
    OSScClient* clients;
    D_8011C1C0_struct_unk184* unk180;
    D_8011C1C0_struct_unk184* unk184;
    u32 unk188;
    D_8011C1C0_struct_unk18C* unk18C;
    u8 unk190[0x20];
    OSMesgQueue unk1B0;
    u8 unk1C8[0x2C];
    s32 unk1F4;
    s32 unk1F8;
}D_8011C1C0_struct;

extern D_8011C1C0_struct D_8011C1C0;

typedef struct D_80117AC8_struct{
    s16 unk0;
    s16 unk2;
}D_80117AC8_struct;

extern D_80117AC8_struct D_80117AC8;

typedef struct Unk80119FE0 {
    u64 unk0;
    u64 unk8;
    u64 unk10;
    u64 unk18;
} Unk80119FE0;

extern Unk80119FE0 D_80119FE0;

#define D_8011C1C0_sets(arg0, arg1, arg2) D_8011C1C0.unk8.viMode = (arg0);D_8011C1C0.unk8.retraceCount = (arg1);D_8011C1C0.unk8.viSpFeatures = (arg2)

#endif
