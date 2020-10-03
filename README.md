# OS1-Project-2020
Simple kernel for multithreaded operating system with time-sharing capability

Project for Operating Systems 1 class at ETF.

This project has an implemented thread management subsystem. This subsystem provides the concept of threads as well as thread creation and launch services, concept of semaphore, event tied to interrupt and time sharing support.
Kernel is realized in such a way that the user program (application) and the kernel itself share the same address space, or basically they represent a singular program (.exe).

This Kernel runs on 32 bit Windows host system as a console application. Code is written in C++ without the use of specific libraries of host system  or DLLs, only standard C++ libraries were used. It is compiled with Borlan C++ compiler in Eclipse.
