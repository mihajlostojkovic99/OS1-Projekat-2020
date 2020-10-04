# OS1-Project-2020
*Simple kernel for multi-threaded operating system with time-sharing capability*

**Project for Operating Systems 1 class at ETF.**

This project has an implemented thread management subsystem. This subsystem provides the concepts of:
- Threads, thread creation and start services
- Semaphores for synchronization
- Events which are tied to interrupts

Kernel is realized in such a way that the user program and the kernel itself share the same address space, or basically they represent a singular program (.exe).

The provided user program represents a system of a set number of producer threads and one consumer thread which exchange data (char) through a bounded buffer. Bounded buffer is realized as a passive object with mutual exclusion and conditional synchronization which are provided by concept of semaphores. Consumer takes a char from the buffer and prints it to standard output. One special thread is activated upon pressing a keyboard button and puts that key letter in the buffer. Pressing ESC will end the program. 

*This Kernel runs on 32 bit Windows host system as a console application. Code is written without the use of specific libraries of host system  or DLLs, only standard C++ libraries were used. It is compiled with Borland C++ compiler in Eclipse.*
