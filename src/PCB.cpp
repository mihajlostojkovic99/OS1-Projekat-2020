/*
 * PCB.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */
#include "iostream.h"
#include <dos.h>
#include "PCB.h"
#include "kernel.h"
#include "SCHEDULE.h"
#include "queue.h"
#define maxStackSize 65536

int IDgen = 0;
Queue allPCB;

PCB::PCB(Time tslice, StackSize sSize, Thread* myT) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if (sSize>=0 && sSize<=maxStackSize) {
	stackSize = sSize / sizeof(unsigned);
	}
	else {
		stackSize = maxStackSize/sizeof(unsigned);
	}
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
	stack[stackSize - 12] = 0; // bp na vrhu stack-a = 0

		#ifndef BCC_BLOCK_IGNORE

				stack[stackSize - 2] = FP_SEG(PCB::wrapper);
				stack[stackSize - 3] = FP_OFF(PCB::wrapper);

				ss = FP_SEG(stack + stackSize - 12);
				sp = FP_OFF(stack + stackSize - 12);

		#endif

	bp = sp;
	status = NEW;
	timeSlice = tslice;
	timeToWait = 0;
	timedUnblock = 0;
	myThread = myT;
	id = IDgen++;

	waiting = new Queue();
	allPCB.add(this);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

PCB::~PCB() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	for(allPCB.reset();allPCB.currentExists(); allPCB.next()){
			PCB* tmp= allPCB.getCurrent();
			if(tmp->id == this->id){
				allPCB.deleteCurrent();
				break;
			}
		}


	delete waiting;
	delete []stack;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void PCB::wrapper() {
	//syncPrintf("PCB wrapper() called\n");
	Kernel::running->myThread->run();
#ifndef BCC_BLOCK_IGNORE
	lock
#endif

	Kernel::running->status = FINISHED;
	if (Kernel::running->waiting->head){
	for(Kernel::running->waiting->reset();Kernel::running->waiting->currentExists() != 0;){

			PCB * tmp= Kernel::running->waiting->getCurrent();
			if (tmp == 0) {break;}
			tmp->status= READY;
			//if (tmp != 0) syncPrintf("-------PCB %d-------\n", tmp->id);
			Scheduler::put(tmp);
			tmp=0;
			Kernel::running->waiting->deleteCurrent();

		}
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	dispatch();
}

