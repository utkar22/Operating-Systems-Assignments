READ ME
OS Assignment 2
Question 2
Utkarsh Arora
2020143

--System Call--
In this assignment question, we have made our own system call kernel_2d_memcpy()
First, we configured and compiled a copy of the stock kernel 
We have added this system call to the table of system calls
448  kernel_2d_memcpy()		sys_kernel_2d_memcpy()
Then we have added our syscall to sys.c in the kernel

Code for the syscall:
SYSCALL_DEFINE4(kernel_2d_memcpy, int __user *, src, int __user *, dest, int, row, int, col)
{
	int bSize = sizeof(int)*(row*col);
	int *p;
	p = (int *)kmalloc(row*col, sizeof(int),GFP_KERNEL);
	__copy_from_user(p,src,bSize);
	__copy_to_user(dest,p,bSize);
	return 0;
}

We have taken 4 inputs: source matric, destination matrix, number of rows, number of columns
This system call copies the matrix from the source matrix to the desination 
matrix inside the kernel space itself.

Finally, we compiled the kernel again.

The difference between the stock kernel and the modified kernel is in q2_kernel.patch
The difference between the entire Linux OS (stock and modified) is in q2_full.patch
q2_full.patch is large because the kernel was first configured from the stock, for our use.

--testing function--
In this function, we test if the system call is working. 
We hardcode a dummy matrix, and use the system call to copy it.

To compile: use the command "make" in the terminal
To run: type "./q2_test" in the terminal