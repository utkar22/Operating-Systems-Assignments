#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h> 

extern int errno;

int NUMBER_OF_ROWS = 0;
char *s;

char* get_element(char* cnt, int row, int column){
	int tgt = (row-1)*8 + column-1;

	char *delimiter = ",\r";
	char *token = strtok(cnt, delimiter);

	for (int i=0; i<tgt; i++)
		token = strtok(NULL, delimiter);

	return token;
}

void get_from_file(){
    int fo = open("student_record.csv",O_RDONLY);

    if (fo==-1){
        printf("\nError.\n");
        perror("Program");
    }
    else{
        s=(char*)malloc(sizeof(char)*2000);
        int sz = read(fo, s, 2000);
        s[sz] = '\0';

        for (int j = 0; j<sz; j++){
            if (s[j]=='\n'){
                NUMBER_OF_ROWS++;
            }
        }
    }
}

void average(char section){
    int total_1=0, total_2=0, total_3=0, total_4=0, total_5=0, total_6=0;
    int no_of_students=0;
    double avg_1, avg_2, avg_3, avg_4, avg_5, avg_6;
    bool if_section=false;

    for (int i=2; i<=NUMBER_OF_ROWS; i++){
        char copy_content[2000];
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
    
}

int main(){
    printf("Using forks\n");
    get_from_file();
    pid_t pid = fork();
    if (pid>0){
        int status; 
        waitpid(pid, &status, 0);
        printf("\nParent process:\n");
        printf("Computing averages for section B\n");
        average('B');
    }
    else{
        printf("\nChild process:\n");
        printf("Computing averages for section A\n");
        average('A');
        exit(1);
    }
    return 0;
}