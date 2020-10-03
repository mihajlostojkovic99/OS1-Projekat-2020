/*
 * queue.h
 *
 *  Created on: May 7, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.h"
#include "iostream.h"

#define lock asm {pushf; cli;}
#define unlock asm {popf;}


class Queue {
public:

struct Elem{
		PCB* pcb;
		Elem * next;
		Elem(PCB* d): pcb(d), next(0){}
};
	Elem *head, *tail,*current;

Queue();
~Queue();


void add(PCB* d);

void reset();
void next();
int currentExists();

PCB* getCurrent();

PCB* getFirst();
PCB* popFirst();

void deleteFirst();
void deleteCurrent();
};



#endif /* QUEUE_H_ */
