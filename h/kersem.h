/*
 * kersem.h
 *
 *  Created on: Sep 10, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "semaphor.h"
#include "queue.h"
class semQueue;

extern semQueue allSem;

class KernelSem {
public:

	int value;
	Queue* myThreads;

	KernelSem(int init = 1);
	~KernelSem();
	int wait(Time maxTimeToWait);
	int signal(int n = 0);
	int val() const; // Returns the current value of the semaphore
	static void tick();
};

#endif /* KERSEM_H_ */
