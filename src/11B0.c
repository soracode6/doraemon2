#include "11B0.h"
#include "2130.h"
#include "2A90.h"
#include "2D90.h"
#include "3210.h"
#include "5070.h"
#include "6EE0.h"
#include "D370.h"
#include "10340.h"
#include "segments.h"
#include "macros.h"
#include "common.h"

extern s16 D_803B5000[][0x12C00];

extern OSMesgQueue      faultMsgQ;
extern OSMesg           faultMsgBuf;

extern OSMesgQueue piMesgQueue;
extern OSMesg piMsg[200];

extern OSMesgQueue D_80117810;
extern OSMesg D_80103588[1];

static regDesc_t causeDesc[] = {
	{ CAUSE_BD,	CAUSE_BD,		"BD" },
	{ CAUSE_IP8,	CAUSE_IP8,		"IP8" },
	{ CAUSE_IP7,	CAUSE_IP7,		"IP7" },
	{ CAUSE_IP6,	CAUSE_IP6,		"IP6" },
	{ CAUSE_IP5,	CAUSE_IP5,		"IP5" },
	{ CAUSE_IP4,	CAUSE_IP4,		"IP4" },
	{ CAUSE_IP3,	CAUSE_IP3,		"IP3" },
	{ CAUSE_SW2,	CAUSE_SW2,		"IP2" },
	{ CAUSE_SW1,	CAUSE_SW1,		"IP1" },
	{ CAUSE_EXCMASK,EXC_INT,
			"Interrupt" },
	{ CAUSE_EXCMASK,EXC_MOD,
			"TLB modification exception" },
	{ CAUSE_EXCMASK,EXC_RMISS,
			"TLB exception on load or instruction fetch" },
	{ CAUSE_EXCMASK,EXC_WMISS,
			"TLB exception on store" },
	{ CAUSE_EXCMASK,EXC_RADE,
			"Address error on load or instruction fetch" },
	{ CAUSE_EXCMASK,EXC_WADE,
			"Address error on store" },
	{ CAUSE_EXCMASK,EXC_IBE,
			"Bus error exception on instruction fetch" },
	{ CAUSE_EXCMASK,EXC_DBE,
			"Bus error exception on data reference" },
	{ CAUSE_EXCMASK,EXC_SYSCALL,
			"System call exception" },
	{ CAUSE_EXCMASK,EXC_BREAK,
			"Breakpoint exception" },
	{ CAUSE_EXCMASK,EXC_II,
			"Reserved instruction exception" },
	{ CAUSE_EXCMASK,EXC_CPU,
			"Coprocessor unusable exception" },
	{ CAUSE_EXCMASK,EXC_OV,
			"Arithmetic overflow exception" },
	{ CAUSE_EXCMASK,EXC_TRAP,
			"Trap exception" },
	{ CAUSE_EXCMASK,EXC_VCEI,
			"Virtual coherency exception on intruction fetch" },
	{ CAUSE_EXCMASK,EXC_FPE,
			"Floating point exception (see fpcsr)" },
	{ CAUSE_EXCMASK,EXC_WATCH,
			"Watchpoint exception" },
	{ CAUSE_EXCMASK,EXC_VCED,
			"Virtual coherency exception on data reference" },
	{ 0,		0,		"" }
};


static regDesc_t srDesc[] = {
	{ SR_CU3,	SR_CU3,		"CU3" },
	{ SR_CU2,	SR_CU2,		"CU2" },
	{ SR_CU1,	SR_CU1,		"CU1" },
	{ SR_CU0,	SR_CU0,		"CU0" },
	{ SR_RP,	SR_RP,		"RP" },
	{ SR_FR,	SR_FR,		"FR" },
	{ SR_RE,	SR_RE,		"RE" },
	{ SR_BEV,	SR_BEV,		"BEV" },
	{ SR_TS,	SR_TS,		"TS" },
	{ SR_SR,	SR_SR,		"SR" },
	{ SR_CH,	SR_CH,		"CH" },
	{ SR_CE,	SR_CE,		"CE" },
	{ SR_DE,	SR_DE,		"DE" },
	{ SR_IBIT8,	SR_IBIT8,	"IM8" },
	{ SR_IBIT7,	SR_IBIT7,	"IM7" },
	{ SR_IBIT6,	SR_IBIT6,	"IM6" },
	{ SR_IBIT5,	SR_IBIT5,	"IM5" },
	{ SR_IBIT4,	SR_IBIT4,	"IM4" },
	{ SR_IBIT3,	SR_IBIT3,	"IM3" },
	{ SR_IBIT2,	SR_IBIT2,	"IM2" },
	{ SR_IBIT1,	SR_IBIT1,	"IM1" },
	{ SR_KX,	SR_KX,		"KX" },
	{ SR_SX,	SR_SX,		"SX" },
	{ SR_UX,	SR_UX,		"UX" },
	{ SR_KSU_MASK,	SR_KSU_USR,	"USR" },
	{ SR_KSU_MASK,	SR_KSU_SUP,	"SUP" },
	{ SR_KSU_MASK,	SR_KSU_KER,	"KER" },
	{ SR_ERL,	SR_ERL,		"ERL" },
	{ SR_EXL,	SR_EXL,		"EXL" },
	{ SR_IE,	SR_IE,		"IE" },
	{ 0,		0,		"" }
};


static regDesc_t fpcsrDesc[] = {
	{ FPCSR_FS,	FPCSR_FS,	"FS" },
	{ FPCSR_C,	FPCSR_C,	"C" },
	{ FPCSR_CE,	FPCSR_CE,	"Unimplemented operation" },
	{ FPCSR_CV,	FPCSR_CV,	"Invalid operation" },
	{ FPCSR_CZ,	FPCSR_CZ,	"Division by zero" },
	{ FPCSR_CO,	FPCSR_CO,	"Overflow" },
	{ FPCSR_CU,	FPCSR_CU,	"Underflow" },
	{ FPCSR_CI,	FPCSR_CI,	"Inexact operation" },
	{ FPCSR_EV,	FPCSR_EV,	"EV" },
	{ FPCSR_EZ,	FPCSR_EZ,	"EZ" },
	{ FPCSR_EO,	FPCSR_EO,	"EO" },
	{ FPCSR_EU,	FPCSR_EU,	"EU" },
	{ FPCSR_EI,	FPCSR_EI,	"EI" },
	{ FPCSR_FV,	FPCSR_FV,	"FV" },
	{ FPCSR_FZ,	FPCSR_FZ,	"FZ" },
	{ FPCSR_FO,	FPCSR_FO,	"FO" },
	{ FPCSR_FU,	FPCSR_FU,	"FU" },
	{ FPCSR_FI,	FPCSR_FI,	"FI" },
	{ FPCSR_RM_MASK,FPCSR_RM_RN,	"RN" },
	{ FPCSR_RM_MASK,FPCSR_RM_RZ,	"RZ" },
	{ FPCSR_RM_MASK,FPCSR_RM_RP,	"RP" },
	{ FPCSR_RM_MASK,FPCSR_RM_RM,	"RM" },
	{ 0,		0,		"" }
};

void func_80025DB0(){
    s32 i;
    s16* p;
    
    osCreatePiManager(OS_PRIORITY_PIMGR, &piMesgQueue, piMsg, ARRAY_COUNT(piMsg)); 
    osCreateMesgQueue(&D_80117810, &D_80103588, ARRAY_COUNT(D_80103588));

    D_80117AC8.unk0 = 0;
    D_80117AC8.unk2 = 1;

    p = &D_803B5000;

    for (i = 0; i < 0x25800; i++) {
        *p = 0;
    }
} 

void func_80025E30(){
    romCopy(SEGMENT(D_CBE40), &D_80121050, SEGMENT_SIZE(D_CBE40), &D_80117810);
    func_80026E6C(0);
    func_80027990();
    func_80032188();
    func_80034F40();
    func_80027830(NULL);
    func_80027E10(7777);
}

int printFaultData(OSThread* t){
    s32 i;
    char buf[60];
    __OSThreadContext* tc = &t->context;
    
    osSyncPrintf("\nFault in thread %d:\n\n", t->id);
    osSyncPrintf("epc\t\t0x%08x\n", tc->pc);
    
    printRegister(tc->cause, "cause", causeDesc);
    printRegister(tc->sr, "sr", srDesc);

    osSyncPrintf("badvaddr\t0x%08x\n\n", tc->badvaddr);
    
    osSyncPrintf("at      0x%016llx v0(r2)  0x%016llx v1(r3)  0x%016llx\n", tc->at, tc->v0, tc->v1);
    osSyncPrintf("a0(r4)  0x%016llx a1(r5)  0x%016llx a2(r6)  0x%016llx\n", tc->a0, tc->a1, tc->a2);
    osSyncPrintf("a3(r7)  0x%016llx t0(r8)  0x%016llx t1(r9)  0x%016llx\n", tc->a3, tc->t0, tc->t1);
    osSyncPrintf("t2(r10) 0x%016llx t3(r11) 0x%016llx t4(r12) 0x%016llx\n", tc->t2, tc->t3, tc->t4);
    osSyncPrintf("t5(r13) 0x%016llx t6(r14) 0x%016llx t7(r15) 0x%016llx\n", tc->t5, tc->t6, tc->t7);
    osSyncPrintf("s0(r16) 0x%016llx s1(r17) 0x%016llx s2(r18) 0x%016llx\n", tc->s0, tc->s1, tc->s2);
    osSyncPrintf("s3(r19) 0x%016llx s4(r20) 0x%016llx s5(r21) 0x%016llx\n", tc->s3, tc->s4, tc->s5);
    osSyncPrintf("s6(r22) 0x%016llx s7(r23) 0x%016llx t8(r24) 0x%016llx\n", tc->s6, tc->s7, tc->t8);
    osSyncPrintf("t9(r25) 0x%016llx gp(r28) 0x%016llx sp(r29) 0x%016llx\n", tc->t9, tc->gp, tc->sp);
    osSyncPrintf("s8      0x%016llx ra(r31) 0x%016llx\n\n", tc->s8, tc->ra);
    
    printRegister(tc->fpcsr, "fpcsr", fpcsrDesc);

    for(i = 0; i < 2; i++){
        sprintf(buf, "Fault in thread %d:", t->id);
        sprintf(buf, "epc 0x%08x", tc->pc);
        sprintf(buf, "ra(r31) 0x%016llx", tc->ra);
        sprintf(buf, "cause   0x%08x", tc->cause);
        sprintf(buf, "fpcsr   0x%08x", tc->fpcsr);
        cmPrintDriver(D_803B5000[i]);
    }

    osSyncPrintf("\nf0  %.7e f2  %.7e f4  %.7e f6  %.7e\n", tc->fp0.f.f_even, tc->fp2.f.f_even, tc->fp4.f.f_even, tc->fp6.f.f_even);
    osSyncPrintf("f8  %.7e f10 %.7e f12 %.7e f14 %.7e\n", tc->fp8.f.f_even, tc->fp10.f.f_even, tc->fp12.f.f_even, tc->fp14.f.f_even);
    osSyncPrintf("f16 %.7e f18 %.7e f20 %.7e f22 %.7e\n", tc->fp16.f.f_even, tc->fp18.f.f_even, tc->fp20.f.f_even, tc->fp22.f.f_even);
    osSyncPrintf("f24 %.7e f26 %.7e f28 %.7e f30 %.7e\n\n", tc->fp24.f.f_even, tc->fp26.f.f_even, tc->fp28.f.f_even, tc->fp30.f.f_even);

    osSyncPrintf("d0  %.15e\td2  %.15e\n", tc->fp0.d, tc->fp2.d);
    osSyncPrintf("d4  %.15e\td6  %.15e\n", tc->fp4.d, tc->fp6.d);
    osSyncPrintf("d8  %.15e\td10 %.15e\n", tc->fp8.d, tc->fp10.d);
    osSyncPrintf("d12 %.15e\td14 %.15e\n", tc->fp12.d, tc->fp14.d);
    osSyncPrintf("d16 %.15e\td18 %.15e\n", tc->fp16.d, tc->fp18.d);
    osSyncPrintf("d20 %.15e\td22 %.15e\n", tc->fp20.d, tc->fp22.d);
    osSyncPrintf("d24 %.15e\td26 %.15e\n", tc->fp24.d, tc->fp26.d);
    osSyncPrintf("d28 %.15e\td30 %.15e\n", tc->fp28.d, tc->fp30.d);
}

void printRegister(u32 regValue, char *regName, regDesc_t *regDesc)
{
	int first = 1;

	osSyncPrintf("%s\t\t0x%08x ", regName, regValue);
	osSyncPrintf("<");
    
	while (regDesc->mask != 0) {
		if ((regValue & regDesc->mask) == regDesc->value) {
			if (first)
				first = 0;
			else
				osSyncPrintf(",");
			osSyncPrintf("%s", regDesc->string);
		}
		regDesc++;
	}
	osSyncPrintf(">\n");
}

void faultproc(){
    OSMesg msg;
    static OSThread *curr, *last;

    osSetEventMesg(OS_EVENT_FAULT, &faultMsgQ, (OSMesg)MSG_FAULT);

    last = (OSThread *)NULL;
    while (1) {
        (void) osRecvMesg(&faultMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);

        if (curr = __osGetCurrFaultedThread()) {
            printFaultData(curr);
        }
    }
}
