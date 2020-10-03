/*
 * ivtentry.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */
#include "ivtentry.h"
#include <dos.h>

IVTEntry* IVTEntry::IVTable[256] = { 0 };

IVTEntry::IVTEntry(IVTNo n, InterruptRoutine i) {
	myIvtNo = n;
	newIntr = i;
	IVTable[myIvtNo] = this;
	myEvent = 0;
}

IVTEntry::~IVTEntry() {
	oldIntr();
	#ifndef BCC_BLOCK_IGNORE
		setvect(myIvtNo,oldIntr);
	#endif
		oldIntr = 0;
		IVTable[myIvtNo] = 0;
		myEvent = 0;
}

void IVTEntry::addEvent(KernelEv* k) {
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	myEvent = k;
	#ifndef BCC_BLOCK_IGNORE
		oldIntr = getvect(myIvtNo);
		setvect(myIvtNo, newIntr);
	#endif

#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
}

IVTEntry* IVTEntry::getEntry(IVTNo n) {
	return IVTable[n];
}
