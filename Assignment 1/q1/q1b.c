#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h> 

extern int errno;

int NUMBER_OF_ROWS = 27;

int overall_total_1=0, overall_total_2=0, overall_total_3=0, overall_total_4=0, overall_total_5=0, overall_total_6=0; 
int total_no_of_students=0;

char* get_element(char* cnt, int row, int column)
{
	int tgt = (row-1)*8 + column-1;

	char *delimiter = ",\r";
	char *token = strtok(cnt, delimiter);

	for (int i=0; i<tgt; i++)
		token = strtok(NULL, delimiter);

	return token;
}

void average(char section){
    int total_1=0, total_2=0, total_3=0, total_4=0, total_5=0, total_6=0;
    int no_of_students=0;
    double avg_1, avg_2, avg_3, avg_4, avg_5, avg_6;
    bool if_section=false;

    int fo = open("student_record.csv",O_RDONLY);

    if (fo==-1){
        printf("\nError.\n");
        perror("Program");
    }
    else{
        char *s;
        s=(char*)malloc(sizeof(char)*2000);
        int sz = read(fo, s, 2000);
        s[sz] = '\0';

        char copy_content[2000];
        strcpy(copy_content, s);

        for (int i=2; i<=NUMBER_OF_ROWS; i++){
            strcpy(copy_content, s);
            if (get_element(copy_content,i,2)[0]==section){
                no_of_students++;

                strcpy(copy_content, s);
                total_1+=atoi(get_element(copy_content,i,3));

                strcpy(copy_content, s);
                total_2+=atoi(get_element(copy_content,i,4));

                strcpy(copy_content, s);
                total_3+=atoi(get_element(copy_content,i,5));

                strcpy(copy_content, s);
                total_4+=atoi(get_element(copy_content,i,6));

                strcpy(copy_content, s);
                total_5+=atoi(get_element(copy_content,i,7));

                strcpy(copy_content, s);
                total_6+=atoi(get_element(copy_content,i,8));                
            }
        }
    }

    avg_1 = (double)total_1 / (double)no_of_students;
    avg_2 = (double)total_2 / (double)no_of_students;
    avg_3 = (double)total_3 / (double)no_of_students;
    avg_4 = (double)total_4 / (double)no_of_students;
    avg_5 = (double)total_5 / (double)no_of_students;
    avg_6 = (double)total_6 / (double)no_of_students;

    printf("\nAverage of assignment 1 is %f",avg_1);
    printf("\nAverage of assignment 2 is %f",avg_2);
    printf("\nAverage of assignment 3 is %f",avg_3);
    printf("\nAverage of assignment 4 is %f",avg_4);
    printf("\nAverage of assignment 5 is %f",avg_5);
    printf("\nAverage of assignment 6 is %f",avg_6);
    printf("\n");

    total_no_of_students+=no_of_students;
    overall_total_1+=total_1;
    overall_total_2+=total_2;
    overall_total_3+=total_3;
    overall_total_4+=total_4;
    overall_total_5+=total_5;
    overall_total_6+=total_6;
    
    
}

void overall_average(){
    double oavg_1=0, oavg_2=0, oavg_3=0, oavg_4=0, oavg_5=0, oavg_6=0;

    oavg_1 = (double)overall_total_1/(double)total_no_of_students;
    oavg_2 = (double)overall_total_2/(double)total_no_of_students;
    oavg_3 = (double)overall_total_3/(double)total_no_of_students;
    oavg_4 = (double)overall_total_4/(double)total_no_of_students;
    oavg_5 = (double)overall_total_5/(double)total_no_of_students;
    oavg_6 = (double)overall_total_6/(double)total_no_of_students;

    printf("\nOverall averages:");
    printf("\nAverage of assignment 1 is %f",oavg_1);
    printf("\nAverage of assignment 2 is %f",oavg_2);
    printf("\nAverage of assignment 3 is %f",oavg_3);
    printf("\nAverage of assignment 4 is %f",oavg_4);
    printf("\nAverage of assignment 5 is %f",oavg_5);
    printf("\nAverage of assignment 6 is %f",oavg_6);
    printf("\n");
    

}

void * sec_A(void * tid){
    printf("\nWorking inside sec_A function\n");
    printf("Averages for section A:\n");
    average('A');
}

int main(){
    printf("Using threads\n");
    pthread_t tid;
    pthread_create(&tid, NULL, sec_A, NULL);
    pthread_join(tid, NULL);
    printf("\nCurrently in main function\n");
    printf("Averages for section B:\n");
    average('B');
    overall_average();
    pthread_exit(NULL);
    return 0;
}