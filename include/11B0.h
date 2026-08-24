#ifndef _11B0_H
#define _11B0_H

#include "ultra64.h"

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

#endif
