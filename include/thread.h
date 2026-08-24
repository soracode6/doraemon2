#ifndef THREAD_H
#define THREAD_H

#include "ultra64.h"

#define THREAD_ID_IDLE 0
#define THREAD_ID_FAULT 20
#define THREAD_PRIORITY_FAULT 125

typedef struct ThreadInfo {
    s32 thread_id;
    s32 thread_priority;
    void (*entry)(void*);
    void* stackPtr;
} ThreadInfo;

extern OSThread idle_thread; 

extern ThreadInfo D_800D9D28[];


#endif
