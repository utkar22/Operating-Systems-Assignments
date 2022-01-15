#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
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
    key_t m_key, m_key2;
    int msg_id, msg_id2;

    m_key = ftok("progfile", 65);
    msg_id = msgget(m_key, 0666 | IPC_CREAT);

    m_key2 = ftok("progfile2", 65);
    msg_id2 = msgget(m_key2, 0666 | IPC_CREAT);

    struct mesg_buffer message;


    while (1){
        msgrcv(msg_id, &message, sizeof(message), 2, 0);

        int curr_index = message.info.first_id;
        int arr_index = 0;

        printf("P2: Message recieved with index %i\n",curr_index);

        int i, j;
        for  (i = 0; i<5; i++){
            printf("P2: Index %d: ",curr_index);
            for (j = 0; j<4; j++){
                printf("%c",message.info.msg_str[arr_index]);
                arr_index++;
            }
            printf("\n");
            curr_index++;
        }

        struct mesg_buffer new_message;
        new_message.id = 2;

        curr_index--;
        new_message.info.first_id = curr_index;

        msgsnd(msg_id2, &new_message, sizeof(new_message), 0);
        printf("P2: Message sent with index %i\n",curr_index);

        if (curr_index >= 49){
            break;
        }
    }
    
    return 0;
}