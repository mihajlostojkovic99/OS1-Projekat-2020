/*
 * semaphor.cpp
 *
 *  Created on: Sep 10, 2020
 *      Author: OS1
 */
#include "semaphor.h"
#include "kersem.h"

Semaphore::Semaphore(int init){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	myImpl = new KernelSem(init);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

Semaphore::~Semaphore(){
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

int Semaphore::wait(Time maxTimeToWait) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	int ret = myImpl->wait(maxTimeToWait);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	return ret;
}

int Semaphore::signal(int n) {
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	int ret = myImpl->signal(n);
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
	return ret;
}

int Semaphore::val() const {
	return myImpl->val();
}


