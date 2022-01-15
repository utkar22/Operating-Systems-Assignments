#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern void B(unsigned long long int);

void A(){
    printf("Currently inside function A");
    printf("\n");
    B(0x6969696969696969LL);
}

int main(){
    A();
    return 0;
}