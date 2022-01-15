#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mesg_info{
    int first_id;
    char msg_str[21];
};

struct mesg_buffer{
    long id;
    struct mesg_info info;
};

int main(){
    /*To generate an array (of size 50) of strings (of length 4)*/ 
    int i=0, j=0;

    int r_key;
	char str[5];
	char arr[50][5];

	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 4; j++)
		{
			r_key = rand()%26 + 65;
			str[j] = (char)(r_key);
		}   
		str[5] = '\0';
		strcpy(arr[i], str);
	}

    /*Prints the contents of the array*/
    printf("P1: The contents of the array are\n");
    for (i = 0; i<50; i++){
        printf("%s\n", arr[i]);
    }

    /*Accessing and using the queues*/

    int first_id = 0;

    key_t m_key, m_key2;
    int msg_id, msg_id2;

    m_key = ftok("progfile", 65);
    msg_id = msgget(m_key, 0666 | IPC_CREAT);

    m_key2 = ftok("progfile2", 65);
    msg_id2 = msgget(m_key2, 0666 | IPC_CREAT);

    while (1){
        struct mesg_buffer message;

        message.id = 2;
        
        strcat(message.info.msg_str, arr[first_id]);
        strcat(message.info.msg_str, arr[first_id + 1]);
        strcat(message.info.msg_str, arr[first_id + 2]);
        strcat(message.info.msg_str, arr[first_id + 3]);
        strcat(message.info.msg_str, arr[first_id + 4]);

        message.info.first_id = first_id;
        

        msgsnd(msg_id, &message, sizeof(message), 0);
        printf("P1: Message sent with index %i\n", first_id);

        struct mesg_buffer new_message;
        msgrcv(msg_id2, &new_message, sizeof(new_message), 2, 0);
        first_id = new_message.info.first_id;

        printf("P1: Message recieved with index %i\n", first_id);

        memset(message.info.msg_str, 0, strlen(message.info.msg_str));

        first_id++;
        if (first_id >= 49){
            break;
        }
    }

    return 0;
    
}