#include <stdio.h>
#include <stdlib.h>
#include <asm/unistd.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>

#define sys_kernel_2d_memcpy 448

int main(int arc, char** argv){
    long sc_v;
    unsigned int rows, columns;
    rows = 3;
    columns = 3;

    float arr_1[rows][columns] = {{1,2,3},{4,5,6},{7,8,9}};
    float arr_cpy[rows][columns];

    void **src, **dest;

    src = arr_1;
    dest = arr_cpy;

    sc_v = syscall(448, src, dest, rows);
    printf("System Call returned %l\n",sc_v);

    printf("First array: %p",src);
    printf("Copied array: %p",dest);

}