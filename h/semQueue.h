/*
 * semQueue.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef SEMQUEUE_H_
#define SEMQUEUE_H_
#include "kersem.h"

class semQueue {
public:

struct Elem{
		KernelSem* semaphore;
		Elem * next;
		Elem(KernelSem* d): semaphore(d), next(0){}
};
	Elem *head, *tail,*current;

semQueue();
~semQueue();


void add(KernelSem* d);

void reset();
void next();
int currentExists() const;

KernelSem* getCurrent();

KernelSem* popFirst();

void deleteFirst();
void deleteCurrent();
};


#endif /* SEMQUEUE_H_ */
