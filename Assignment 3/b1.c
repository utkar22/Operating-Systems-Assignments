#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    /*Connect to FIFO*/
    int file_add;

    char fifo_add[20] = "fifo_temp";
    mkfifo(fifo_add, 0666);

    /*To generate an array (of size 50) of strings (of length 4)*/ 

    int i=0, j=0;

    int r_key;
	char str_2[5];
	char arr[50][5];
    char *finalstring[50];

	for (i = 0; i < 50; i++){
		for (j = 0; j < 4; j++){
			r_key = (i*3+j*8)%26 + 65;
			str_2[j] = (char)(r_key);
		}
		str_2[5] = '\0';
		strcpy(arr[i], str_2);
	}    

    /*Using FIFO*/
    for (i = 0; i < 50; i++){
        finalstring[i]= (char*)malloc(100*sizeof(char));
        strcpy(finalstring[i], arr[i]);
        char hehe[2];
        sprintf(hehe,"%d",i);
        //strncat(finalstring[i], hehe, 2);
        //printf("%s\n", finalstring[i]);

    }
    int m = 0;

    for(int i = 0; i<50; i++){
       char stringGroup[100] = " Index: ";
       
        char ind[5];
        sprintf(ind,"%d", i);
        strncat(stringGroup, ind , 5);
        strncat(finalstring[i], stringGroup, 10);
        m++;
        // printf("%s\n Maximum Index received is : ");
       // printf("%s\n", finalstring[i]);
        file_add = open(fifo_add, O_WRONLY);
        write(file_add, finalstring[i], strlen(finalstring[i])+1);
        close(file_add);
        char maximum[10];
        file_add=open(fifo_add, O_RDONLY);
        read(file_add, maximum, 5);
        int x = atoi(maximum);
        if(x<50){
            printf("Maximum ID returned: %d \n", x);
        }
        close(file_add);
        
    }

    
    /*while (1){
        char str[24]="";

        int flag;
        if (index<10){
            flag = 1;
        }
        else{
            flag = 2;
        }

        char char_flag[4];
        sprintf(char_flag, "%d", flag);
        strcat(str, char_flag);

        char char_id[4];
        sprintf(char_id, "%d", index);
        strcat(str, char_id);

        strcat(str, arr[index]);
        strcat(str, arr[index + 1]);
        strcat(str, arr[index + 2]);
        strcat(str, arr[index + 3]);
        strcat(str, arr[index + 4]);
        
        file_add = open(fifo_add, O_WRONLY);
        write(file_add, str, sizeof(str));
        close(file_add);
        
        printf("P1: Sent with index %i\n", index);



        char new_id[5];
        int file_add = open(fifo_add, O_RDONLY);
        read(file_add, new_id, 3);
        close(file_add);

        index = atoi(new_id);
        index++;
        printf("P1: Recieved index %i\n", index);

        if (index>48){
            break;
        }
        index++;        
        
    }*/


    return 0;
}
