# Buddy-Memory-Allocator

                               Problem Statement
Computers have become an essential part of our daily life. Engineers, Doctors, and Students all
rely on the system for product development, medical diagnosis, and much more. All computers
have an operating system which is the program initially loaded by the boot program which
manages all the other application programs. Now, for any operation to be performed by the
operating system, every instruction has to be fetched from memory before it can be executed, and
most instructions involve retrieving data from memory or storing data in memory or both.
Memory management is the process of controlling and coordinating a computer's main memory. It
ensures that blocks of memory space are properly managed and allocated so the operating system
(OS), applications, and other running processes have the memory they need to carry out their
operations.
Multi-tasking OS compounds the complexity of memory management because processes are
swapped in and out of the CPU, all at high speeds and without interfering with any other
processes. Shared memory, virtual memory, the classification of memory as read-only versus
read-write, and concepts like copy-on-write forking all further complicate the issue
To make the memory management process efficient, we require techniques for it.

                                Introduction
The two smaller parts of the memory block are of equal size and are called buddies. The buddy
system is a procedure in which two individual buddies operate together as a single unit so that
they can monitor and help each other. Similarly, one of the two buddies will further divide into
smaller parts until the request is fulfilled. The buddy system maintains a list of the free blocks of
each size (called a free list) so that it is easy to find a block of the desired size if one is available.
If no block of the requested size is available, Allocate searches for the first non-empty list for
blocks of at least the size requested. In either case, a block is removed from the free list.
Motivation
Buddy memory management is easy to implement, it allocates blocks of the correct size and is
easy to merge adjacent holes. In comparison to other simpler techniques such as dynamic
allocation, the buddy memory system has little external fragmentation. The buddy memory
allocation system is implemented with the use of a binary tree to represent used or unused split
memory blocks.

                                 Objective
The objective of this project is to implement a binary buddy system and analyze how a system
allocates processes in the memory and also how it releases when the system doesn't need that
process
