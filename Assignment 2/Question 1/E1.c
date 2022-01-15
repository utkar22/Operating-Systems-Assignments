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

pid_t pid_int;

int signal_catcher(int signum, void (*handler)(int)) {
    struct sigaction act; 
    act.sa_handler = handler; 
    sigemptyset(&act.sa_mask); 
    act.sa_flags = 0;
    return sigaction (signum, &act, NULL); 
}

void randNoGen(int sig){
	uint64_t randNo;
	asm("rdrand %0\n\t" : "=a"(randNo): :);
    printf("The generated random is ");
	printf("%lu", randNo);
    printf("\n");
    union sigval n;
    n.sival_ptr = (void*)randNo;

    if(sigqueue(pid_int , SIGUSR1 , n) == -1){
        //perror("ERROR: SIGUSR1 was failed in sending");
        //exit(2);
    }
    
    if (kill(pid_int,SIGTERM) == -1){
        fprintf(stderr, "ERROR : there was an error while killing");
        exit(2);
    }
    //send a harmless signal here(SIGUSR1 IS A HARMLESS SIGNAL)
    //directly add to the queue from here
    //we can't return any number from here since the parameter of the catch_signal handler has to be void.
}



int main(int argc, char *argv[]){
    pid_int = (pid_t)atoi(argv[1]);
    signal_catcher(SIGALRM , randNoGen);

    struct itimerval itVal;
    itVal.it_value.tv_sec=2;
    itVal.it_value.tv_usec=0;
    itVal.it_interval = itVal.it_value;
    int setitimer_retval = setitimer(ITIMER_REAL, &itVal, 0);
    if(setitimer_retval == -1){
        //if there is an error while creating the error
        fprintf(stderr, "ERROR : Error while creating the timer");
        exit(1);
    }
    while(1){
        pause();
    }
    return 0;

}