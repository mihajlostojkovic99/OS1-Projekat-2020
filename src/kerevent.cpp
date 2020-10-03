/*
 * kerevent.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */
#include "kerevent.h"
#include "kernel.h"
#include "ivtentry.h"

KernelEv::KernelEv(IVTNo n) {

#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	ivtNo = n;
	mySem = new KernelSem(0);
	myPCB = (PCB*) Kernel::running;
	IVTEntry::IVTable[n]->addEvent(this);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

KernelEv::~KernelEv() {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	delete mySem;
	IVTEntry::getEntry(ivtNo)->addEvent(0);
	myPCB = 0;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void KernelEv::wait() {
	if (myPCB != Kernel::running || mySem->val() == -1) return;
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	mySem->wait(0);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void KernelEv::signal() {
	if(mySem->val() == 1) return;
	#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	mySem->signal(0);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}
