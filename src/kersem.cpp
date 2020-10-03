/*
 * kersem.cpp
 *
 *  Created on: Sep 10, 2020
 *      Author: OS1
 */
#include "kersem.h"
#include "semQueue.h"
#include "kernel.h"
#include "PCB.h"
#include "SCHEDULE.H"

semQueue allSem;

KernelSem::KernelSem(int init){
	value = init;
	allSem.add(this);
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	myThreads = new Queue();
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
KernelSem::~KernelSem() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	delete myThreads;

	allSem.reset();
	while (allSem.currentExists()) {
		if (allSem.getCurrent() == this) {
			allSem.deleteCurrent();
			//syncPrintf("Semaphore deleted\n");
			break;
		}
		allSem.next();
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
int KernelSem::wait(Time maxTimeToWait) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	Kernel::running->timedUnblock = 0;
	//syncPrintf("In wait with value %d \n", value);
	if ((--value) < 0) {
		//syncPrintf("Semaphore blocking PCB %d \n", Kernel::running->id);
		Kernel::running->status = BLOCKED;

		Kernel::running->timeToWait = maxTimeToWait;
		myThreads->add((PCB*)Kernel::running);
		dispatch();
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	return !Kernel::running->timedUnblock;

}

int KernelSem::signal(int n) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	//syncPrintf("In signal with n %d \n", n);
	if (n<0) return n;
	int ret = 0;
	if (n == 0) value++;
	if((value+n) <= 0){
		ret = n;
		value+=n;
		do {
			n--;
			PCB* tmp = myThreads->popFirst();
			tmp->status = READY;
			tmp->timedUnblock = 0;
			Scheduler::put(tmp);
		} while (n>0);
	} else if (value < 0) {
		value+=n;
		while (myThreads->getFirst() != 0){
			PCB* tmp = myThreads->popFirst();
			tmp->status = READY;
			tmp->timedUnblock = 0;
			Scheduler::put(tmp);
			ret++;
		}
	} else value+=n;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	return ret;
}

int KernelSem::val() const {
	return value;
}

void KernelSem::tick() {
	for (allSem.reset(); allSem.currentExists(); allSem.next()) {

		KernelSem* tmp = allSem.getCurrent();

		for (tmp->myThreads->reset(); tmp->myThreads->currentExists(); ) {
			PCB* pcb = tmp->myThreads->getCurrent();
			pcb->timeToWait--;
			if (pcb->timeToWait == 0) {
				pcb->timedUnblock = 1;
				pcb->status = READY;
				Scheduler::put(pcb);
				tmp->value++;
				tmp->myThreads->deleteCurrent();
				continue;
			}
			tmp->myThreads->next();
		}

	}
}

