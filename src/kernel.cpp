/*
 * kernel.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */
#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "Idle.h"
#include <dos.h>
#include <iostream.h>
#include "kersem.h"

typedef void interrupt(*pInterrupt)(...);
pInterrupt oldISR;

volatile int Kernel::context_switch_on_demand = 0;
volatile int Kernel::cntr = 20;

volatile PCB* Kernel::running = 0;
Idle* Kernel::idle = 0;
PCB* Kernel::mainPCB;

extern void tick();


void interrupt Kernel::timer(...) {
	//syncPrintf("Timer interrupt started\n");
	static unsigned tsp;
	static unsigned tss;
	static unsigned tbp;
	if (!context_switch_on_demand) {
		cntr--;
		KernelSem::tick();
	}
	if (context_switch_on_demand || cntr == 0) {

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif

		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;

		if (running->status == READY && running!=idle->myPCB) {Scheduler::put((PCB*)running);/*cout<< "u timer- put"<<endl;*/}

		running = Scheduler::get();



		if (running == 0) {running = idle->myPCB;}

		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif

		cntr = running->timeSlice;

	}
	if (!context_switch_on_demand) {
				(*oldISR)();
				tick();
			}
	context_switch_on_demand = 0;
}

void Kernel::inic() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	mainPCB =new PCB(0, 0, 0);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	mainPCB->status = READY;
	Kernel::running = mainPCB;
	syncPrintf("\n-------Main PCB created.------\n\n");
	#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	idle = new Idle();
	idle->start();
	syncPrintf("\n-------Idle Thread created.------\n\n");
#ifndef BCC_BLOCK_IGNORE
	oldISR = getvect(0x8);
	setvect(0x8, Kernel::timer);
	unlock
#endif
}

void Kernel::restore() {
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(0x8, oldISR);
#endif
	delete idle;
	delete mainPCB;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
