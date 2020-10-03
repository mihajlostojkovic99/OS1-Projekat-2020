/*
 * main.cpp
 *
 *  Created on: Sep 6, 2020
 *      Author: OS1
 */
#include "kernel.h"
#include "iostream.h"

extern int syncPrintf (const char* format, ... );

class userThread : public Thread {
	int argc;
	char **argv;
public:
	userThread(int argc, char **argv) : Thread(), argc(argc), argv(argv) {value = 0;}
	int value;
	virtual void run() {value = userMain(argc, argv);}
};

int main (int argc, char* argv[]) {
	Kernel::inic();
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	userThread* uThread = new userThread(argc, argv);
#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
	uThread->start();

	syncPrintf("\n-------User Thread created.------\n\n");

	uThread->waitToComplete();
	int value = uThread->value;
#ifndef BCC_BLOCK_IGNORE
		lock
#endif
	delete uThread;
#ifndef BCC_BLOCK_IGNORE
		unlock
#endif
	Kernel::restore();
	syncPrintf("main() finished\n");
	return value;
}



