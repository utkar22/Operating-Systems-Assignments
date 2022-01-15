#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t forks[5];
sem_t sauce_bowl;

void eat(int phil_no){
    printf("Philosopher %d is eating.\n",phil_no);
    sleep(4);
    printf("Philosopher %d has finished eating.\n",phil_no);
}

void * philosopher(void * num){
	int phil_no=*(int *)num;

    int fork_1;

    fork_1 = phil_no;

    sem_wait(&sauce_bowl);
    printf("Philospher %d has picked up a sauce bowl\n", phil_no);
	sem_wait(&forks[fork_1]);
    printf("Philosopher %d has picked up fork %d\n",phil_no,fork_1);

	eat(phil_no);

	sem_post(&forks[fork_1]);
    printf("Philosopher %d has put down fork %d\n",phil_no,fork_1);
    sem_post(&sauce_bowl);
    printf("Philospher %d has put down a sauce bowl\n", phil_no);
}

int main(){
    printf("There is no deadlock possible in this part of the problem.\n");
    printf("Regardless, I have coded the solution for this question.\n\n");

	int i,a[5];
	pthread_t t_id[5];

    sem_init(&sauce_bowl, 0, 4);
	
	for(i=0;i<5;i++){
		sem_init(&forks[i],0,1);
    }

    printf("Dinner has commenced\n");
		
	for(i=0;i<5;i++){
		pthread_create(&t_id[i],NULL,philosopher,(void *)&i);
	}

	for(i=0;i<5;i++){
		pthread_join(t_id[i],NULL);
    }

    printf("Dinner has been concluded. All Philosophers have eaten and there was no deadlock.\n");
}