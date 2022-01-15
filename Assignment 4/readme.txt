OS Assignment 4
Utkarsh Arora
2020143

In this assignment, we have created a kernel driven producer-consumer.
For this, we have created two system call in sys.c.
We have made two system calls, reader() and writer(long data) in sys.c, and made entries for them in the system call table.
Inside the kernel (sys.c), we have created a queue. I have used the same code for this that I used in refresher module assignment 2, but here I have used kmalloc and kfree instead of malloc and free.
The writer function enqueues data in the queue, and the reader function dequeues data from the queue.
The Producer Consumer problem is that both the processes might try to access the queue at the same time. 
Another problem is that an empty queue might be tried to be dequeued, or a full queue be tried to enqueued.
To solve this problem, we have made the use of semaphores and mutex.
We have defined 3 semaphores in sys.c. Semaphores in the kernel space have different implementation in the kernel space, however they work the same.
To make sure only one process is accessing the queue, we have made the use of a binary semaphore, which may also be called a mutex. While accessing the queue, the semaphore is downed, which means no other process can access the queue. When the work is done, the semaphore is upped again.
We have two other semaphores, empty and full. We set empty to 8, and full to 0; signifying there are 8 empty slots in the queue, and 0 full slots in the queue.
While enqueuing in the queue, we down the empty slot. If it is 0, it waits for the empty semaphore to be upped; thus a queue cannot be overloaded beyond it's capacity.
It works similarly for dequeuing the queue, with the full semaphore. Thus, a queue cannot be dequeued when it's empty.
After writing these system calls, the queue, and these semaphores, we compile the kernel using the 'make -j4' command.
After compiling the kernel, we are able to use these system calls in the userspace.
We make two processes P.c and C.c, that utilise these system calls.

We have also made a patch file, comparing the difference between the stock kernel, and the kernel we have modified. 