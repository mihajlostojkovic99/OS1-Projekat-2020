/*
 * Idle.h
 *
 *  Created on: Sep 6, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include <iostream.h>
#include "thread.h"
extern int syncPrintf (const char* format, ... );

class Idle : public Thread {
public:

	Idle(): Thread(256, 2) {};

	void run() {
		while(1) ;
	}
};

#endif /* IDLE_H_ */
