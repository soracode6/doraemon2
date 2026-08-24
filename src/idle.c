#include "idle.h"
#include "thread.h"
#include "common.h"

#include "11B0.h"

extern OSThread D_8011A690;
extern OSThread D_80120D98;

extern OSMesgQueue faultMsgQ;
extern OSMesg D_80117720;

extern u8 D_8011C860[];

void func_80025CB0(){
    func_80025DB0();
    D_8011C1C8_sets(2, 1, 90);
    
    func_80026500(&idle_thread, &D_800D9D28);
    
    osCreateThread(&D_8011A690, D_800D9D28[1].thread_id, D_800D9D28[1].entry, NULL, D_800D9D28[1].stackPtr, D_800D9D28[1].thread_priority);
    osStartThread(&D_8011A690);

    osCreateMesgQueue(&faultMsgQ, &D_80117720, 1);
    
    osCreateThread(&D_80120D98, THREAD_ID_FAULT, faultproc, NULL, D_8011C860, THREAD_PRIORITY_FAULT);
    osStartThread(&D_80120D98);

    osSetThreadPri(NULL, 0);

    while(TRUE);
}