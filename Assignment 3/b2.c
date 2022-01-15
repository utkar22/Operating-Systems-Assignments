#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
    int file_add;
    
    char fifo_add[20] = "fifo_temp";
    int maxID = -1;
    int kl = 0;

    for(int i = 0; i<50; i++){
        char inp[2000];
        file_add = open(fifo_add, O_RDONLY);
        read(file_add, inp, 2000);
        close(file_add);
        printf(" %s\n",inp);
        

        maxID+=5;
        char new_id[10];
        char id[10];
        sprintf(id, "%d", maxID);

        file_add = open(fifo_add, O_WRONLY);
        write(file_add, id, strlen(id)+1);
        close(file_add);
        // printf("%d",i);
        // printf("P2: Recieved current index %i\n", maxID+1);
        // printf("P2: Sent current index %i\n", maxID);S
        
    }

    return 0;
}


















































































































































































































































