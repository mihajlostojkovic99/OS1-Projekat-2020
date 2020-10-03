/*
 * kernel.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "Thread.h"
#include "semaphor.h"


extern int syncPrintf (const char* format, ... );

#define lock asm {pushf; cli;}
#define unlock asm {popf;}

typedef void interrupt(*pInterrupt)(...);
extern pInterrupt oldISR;


int userMain(int argc, char* argv[]);

class Kernel {
public:
static volatile int context_switch_on_demand;
static volatile int cntr;
static Idle* idle;
static PCB* mainPCB;

static volatile PCB* running;

static void interrupt timer(...);
static void inic();
static void restore();
};





#endif /* KERNEL_H_ */
