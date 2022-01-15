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

int if_E1_recieved = 0, if_E2_recieved = 0; //basically boolean values

int E1_val = 0, E2_val = 0;


int signal_catcher(int signum, void (*handl)(int)){
    struct sigaction act;
    act.sa_handler = handl; 
    sigemptyset(&act.sa_mask); 
    act.sa_flags = 0;
    
    return sigaction (signum, &act, NULL); 
}

int signal_catcher2(int signum, void (*handl)(int , siginfo_t * , void *)) {
    struct sigaction act; 
    act.sa_sigaction = handl; 
    sigemptyset(&act.sa_mask); 
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    
    return sigaction (signum, &act, NULL); 
}

void printer(int signum){
    if (if_E1_recieved == 1){
        printf("The random number is ");
        printf("%llu",(long long unsigned) E1_val);
        printf("\n");

        if_E1_recieved = 0;
    }
    else if (if_E2_recieved == 1){
        printf("The random number is ");
        printf("%llu",(long long unsigned) E2_val);
        printf("\n");

        if_E2_recieved = 0;
    }
    else{
        ;
    }
}

void output_no(int signal, siginfo_t *key , void* khaali_lmao){ 

    if (signal == SIGUSR1)
    {
        E1_val = (uint64_t)key->si_value.sival_ptr;
        if_E1_recieved = 1;
    }

    if (signal == SIGUSR2)
    {
        E2_val = (uint64_t)key->si_value.sival_ptr;
        if_E2_recieved = 1;
    }
}

int main(){
    pid_t pid_S1 = fork();
    pid_t S1pid = pid_S1; //Local variable which stores the PID of S1

    char buff[8];
    sprintf(buff, "%d", pid_S1);

    if (pid_S1>0){
        //Parent Process
        pid_t pid_SR = fork();
        if (pid_SR>0){
            //Parent Process
            pid_t pid_ST = fork();
            if (pid_ST>0){
                ;
            }
            else if(pid_ST==0){
                printf("Inside ST Process");
                execl("e2","e2",buff,NULL);
            }
            else{
                printf("There was an error while forking\n");
            }
        }
        else if (pid_SR == 0){
            printf("Inside SR process\n");
            execl("e1","e1",buff,NULL);
        }
        else{
            printf("There was an error while forking\n");
        }
    }
    else if (pid_S1==0){
        printf("Inside S1 process\n");
        int n1, n2, n3;

        n1 = signal_catcher(SIGTERM, printer);
        n2 = signal_catcher2(SIGUSR1, output_no);
        n3 = signal_catcher2(SIGUSR2, output_no);
        
        if (n1==-1){
            perror("There was an error while creating the signal handler");
            exit(2);
        }
        if (n2!=0){
            perror("There was an error while creating the signal handler");
            exit(2);
        }
        if (n3!=0){
            perror("There was an error while creating the signal handler");
            exit(2);
        }

        //Empty while loop
        while (1){
            ;
        }
    }
    else{
        perror("There was an error while forking");
        exit(2);
    }

    return 0;
}