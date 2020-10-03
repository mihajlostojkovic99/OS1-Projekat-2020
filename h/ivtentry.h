/*
 * ivtentry.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "kerevent.h"
typedef unsigned char IVTNo;
typedef void interrupt (*InterruptRoutine)(...);

#define PREPAREENTRY(ivtno, flag)\
    void interrupt intr##ivtno(...);\
    IVTEntry ivtE##ivtno(ivtno, &intr##ivtno);\
    void interrupt intr##ivtno(...){\
        if(flag) ivtE##ivtno.oldIntr();\
		ivtE##ivtno.myEvent->signal();\
		dispatch();\
    }


class IVTEntry{
public:
	IVTEntry(IVTNo n, InterruptRoutine i);
	~IVTEntry();

	static IVTEntry* IVTable[256];
	static IVTEntry* getEntry(IVTNo n);
	InterruptRoutine oldIntr, newIntr;
	IVTNo myIvtNo;
	KernelEv* myEvent;
	void addEvent(KernelEv* k);
};



#endif /* IVTENTRY_H_ */
