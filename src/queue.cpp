/*
 * queue.cpp
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */
#include "queue.h"


Queue::Queue() {
	head = tail = current = 0;
}

Queue::~Queue() {
	while (head) {
		deleteFirst();
	}
	head = tail = current = 0;
}

void Queue::add(PCB* d) {
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

void Queue::reset(){
	current = head;
}
void Queue::next(){
	if (current) current = current->next;
}
int Queue::currentExists(){

	if (current) return 1;
	else return 0;
}

PCB* Queue::getCurrent(){
		if (currentExists()) return current->pcb; else return 0;
}

PCB* Queue::getFirst(){
	if (head) return head->pcb; else return 0;
}

PCB* Queue::popFirst() {
	if(!head) return 0;
	Elem* del = head;
	PCB* tmp = head->pcb;
	head = head->next;
	delete del;
	return tmp;
}

void Queue::deleteFirst(){
	Elem* tmp = head;
	if (current == head) current = head->next;
	head = head->next;
	delete tmp;
}
void Queue::deleteCurrent(){
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
	if (!current) tail = prev;
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	delete tmp;
#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
}
