#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "ultra64.h"
#include "PR/sched.h"

typedef struct Scheduler{
    OSThread idleThread;
    OSThread unk1B0;
    OSThread unk360;
    OSThread unk510;
    OSThread unk6C0;
}Scheduler;

#endif
