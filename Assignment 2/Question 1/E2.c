#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

pid_t pid_S1;

void time_gen(int signum){
	unsigned long low;
    unsigned long high;
    union sigval n;

	asm( "rdtsc" : "=a" (low), "=d" (high) ); 
	uint64_t tim =  low | (high << 32);

	printf("Time is ");
    printf("%lu", tim);
    printf("\n");

    
    n.sival_ptr = (void*)tim;
    sigqueue(pid_S1 , SIGUSR2 , n);
    if (kill(pid_S1,SIGTERM) == -1){
        fprintf(stderr, "ERROR : there was an error while killing");
    }
}

int signal_catcher(int signum, void (*handl)(int)) 
{
    struct sigaction act; 
    act.sa_handler = handl; 
    sigemptyset(&act.sa_mask); 
    act.sa_flags = 0;
    return sigaction (signum, &act, NULL); 
}

int main(int argc, char *argv[]){
    pid_S1 = (pid_t)atoi(argv[1]);
    if (signal_catcher(SIGALRM , time_gen) == -1) 
    {
        fprintf(stderr, "Can't map the handler"); 
        exit(2);
    }

    struct itimerval itVal;
    itVal.it_value.tv_sec=2;
    itVal.it_value.tv_usec=0;
    itVal.it_interval = itVal.it_value;
    int setitimer_retval = setitimer(ITIMER_REAL, &itVal, 0);
    if(setitimer_retval == -1){
        fprintf(stderr, "ERROR : There was an error in creating the timer");
    }
    while(1){
        pause();
    }

}