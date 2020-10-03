/*
 * Thread.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */
#include "thread.h"
#include "queue.h"
#include "PCB.h"
#include "kernel.h"
#include "SCHEDULE.h"
#include <iostream.h>
#include "Idle.h"

void Thread::start() {
	//syncPrintf("In start() of PCB %d \n", myPCB->id);
	if (myPCB->status == NEW) {

#ifndef BCC_BLOCK_IGNORE
		lock
#endif
		myPCB->status = READY;
		if (myPCB->id != Kernel::idle->getId()) {
			Scheduler::put(myPCB);
		}

#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
	}
}

void Thread::waitToComplete() {
	//syncPrintf("In waitToComplete() of PCB %d \n", myPCB->id);
	if (this->myPCB->id == Kernel::idle->getId() || this->myPCB->status == FINISHED || this->myPCB->status == NEW) return;
#ifndef BCC_BLOCK_IGNORE
		lock
#endif

		Kernel::running->status = BLOCKED;
		this->myPCB->waiting->add((PCB*)Kernel::running);

#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
		dispatch();
}

Thread::~Thread() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif

	waitToComplete();
	if (myPCB!=0) delete myPCB;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

ID Thread::getId() {
	return this->myPCB->id;
}

ID Thread::getRunningId() {
	return Kernel::running->id;
}
Thread* Thread::getThreadById(ID idT) {
	Thread* t = 0;
	for(allPCB.reset();allPCB.currentExists();allPCB.next()){
		PCB* tmp = allPCB.getCurrent();
		if(tmp->id == idT){
			t = (tmp->myThread);
			break;
		}
	}
	return t;
}

Thread::Thread (StackSize stackSize, Time timeSlice) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif

	myPCB = new PCB(timeSlice, stackSize, this);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	//syncPrintf("dispatch() called\n");
	Kernel::context_switch_on_demand = 1;
	Kernel::timer();
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
