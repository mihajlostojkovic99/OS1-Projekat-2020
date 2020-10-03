/*
 * semQueue.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */
#include "semQueue.h"
#include "STDIO.H"


semQueue::semQueue() {
	head = tail= current = 0;
}

semQueue::~semQueue() {
	while (head) {
		deleteFirst();
	}
	head = tail= current = 0;
}

void semQueue::add(KernelSem* d) {
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	if (!head) tail=head=new Elem(d);
		else {
			tail->next = new Elem(d);
			tail = tail->next;
		}
#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
}

void semQueue::reset(){
	current = head;
}
void semQueue::next(){
	if (current) current = current->next;
}
int semQueue::currentExists() const{

	if (current) return 1;
	else return 0;
}

KernelSem* semQueue::getCurrent(){
	if (currentExists()) return current->semaphore; else return 0;
}

KernelSem* semQueue::popFirst() {
	if(!head) return 0;
	Elem* del = head;
	KernelSem* tmp = head->semaphore;
	head = head->next;
	delete del;
	return tmp;
}

void semQueue::deleteFirst(){
	Elem* tmp = head;
	if (current == head) current = head->next;
	head = head->next;
	delete tmp;
}
void semQueue::deleteCurrent(){
	Elem* prev = 0;
	if (current == 0) return;
	if (current != head) {
		prev = head;
		while (1) {
			if (prev->next == current) break;
			prev = prev->next;
		}
	}

	Elem* tmp = current;
	current = current->next;
	if (!prev) head = current;
	else prev->next = current;
	if (!current) tail = 0;
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	delete tmp;
#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
}


