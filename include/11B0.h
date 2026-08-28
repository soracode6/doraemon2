#ifndef _11B0_H
#define _11B0_H

#include "ultra64.h"
#include "PR/sched.h"

struct D_8011C1C0_struct_unk184;
struct Scheduler;
struct ThreadInfo;

#define MSG_FAULT	0x10

typedef struct {
	u32 mask;
	u32 value;
	char* string;
} regDesc_t;

void func_80025DB0(void);
void func_80025E30(void);
int printFaultData(OSThread* t);
void printRegister(u32 regValue, char *regName, regDesc_t *regDesc);
void faultproc(void);
void func_80026500(struct Scheduler* sc, struct ThreadInfo* info);
void drScdEvent(void* arg0);
void osScAddClient(OSScClient* c, OSMesgQueue* msgQ, u16 arg2);
void osScRemoveClient(OSScClient* c);
void func_8002694C(void* arg0);
void func_80026B10(struct D_8011C1C0_struct_unk184* arg0);
void func_80026B94(void* arg0);


#endif
