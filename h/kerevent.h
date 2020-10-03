/*
 * kerevent.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_

#include "PCB.h"
#include "kersem.h"
#include "event.h"

typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv (IVTNo n);
	~KernelEv ();

	IVTNo ivtNo;
	KernelSem* mySem;
	PCB* myPCB;

	void wait ();
	void signal();
};



#endif /* KEREVENT_H_ */
