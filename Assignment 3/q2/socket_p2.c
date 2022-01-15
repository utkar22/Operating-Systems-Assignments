// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	while (1){
		char inp[2000];

		read(sock, inp, 2000);

		//Printing stuff
        int counter;

        char char_id[20];
        int curr_index;

        if (inp[0]=='1'){
            curr_index = inp[1] - '0';
            counter = 2;
        }
        else if (inp[0]=='2'){
            curr_index = 10*(inp[1] - '0') + (inp[2] - '0');
            counter = 3;
        }

        printf("P2: Recieved current index %i\n", curr_index);
        
        int i, j;
        for  (i = 0; i<5; i++){
            printf("P2: Index %d: ",curr_index);
            for (j = 0; j<4; j++){
                printf("%c",inp[counter]);
                counter++;
            }
            printf("\n");
            curr_index++;
        }

        curr_index--;

        char new_id[20];
        sprintf(new_id, "%d", curr_index-1);

		send(sock, new_id, 20, 0);
        printf("P2: Sent current index %i\n", curr_index);

        if (curr_index>48){
            break;
        }
	}
	return 0;
}
