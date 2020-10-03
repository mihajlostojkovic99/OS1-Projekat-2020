/*
 * PCB.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
enum PCBstatus {NEW, READY, BLOCKED, FINISHED};

class Queue;
extern Queue allPCB;

class PCB {

public:

		unsigned* stack;
		unsigned ss;
		unsigned sp;
		unsigned bp;
		PCBstatus status; 		// 0-new, 1-ready, 2-blocked, 3-finished
		ID id;

		Thread *myThread;
		Time timeSlice;
		Time timeToWait;
		int timedUnblock;
		StackSize stackSize;

		Queue* waiting;

		PCB(Time tSlice, StackSize sSize, Thread* myT);

		~PCB();

		static void wrapper();
};
extern int IDgen;




#endif /* PCB_H_ */
