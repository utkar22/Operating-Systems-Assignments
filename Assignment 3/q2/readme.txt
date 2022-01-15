OS Assignment 3
Name: Utkarsh Arora
Roll No: 2020143

Question 2:

There are 6 .c files in the project:
fifo_p1.c
fifo_p2.c
queue_p1.c
queue_p2.c
socket_p1.c
socket_p2.c

We have to run the makefile, by using the 'make' command in the terminal.

-->Generating Random Strings
We have generated 50 random strings and stored them in an array. This is done
for each part of the question.
We create an empty array of strings. We loop through each element of the array.
For each element, we loop through each character of the string. Inside every 
iteration, we generate a random number. We modulo the random number by 26
(because there are 26 letters), and add 65 (65 is the ASCII value of 'A').
Thus, we generate an array of size 50, with strings of size 4.

-->Message Queue
We make use of Message Queue IPC to send a message from file P1 to P2.
On a queue, we send messages by using a structure, mesg_buffer.
The structure can only have two items; the first of them has to be of type long.
For the other object, we use another object. In that object, we have the
array index of the first string we send, and the concatenation of the 5 strings
we're sending.
We access two queues.
On the first, from P1 we send a message having the first array index and the
concatenation of the 5 strings; using msgsnd()
In P2, we recieve this message using msgrcv().
We print out the 5 strings (using looping and such) in P2.
Then we send a message from P2 containing the last array index (of the currently
sent strings) to P1.
We use a while loop, and break it when the array index reaches 49.

We have to run 'queue_p2' before 'queue_p1'.

-->FIFO
We use a very similar form to Message Queues here. However, we do not use a 
structure. Instead, we add the array index to the string. Also, at the
beginning we keep a number, that tells us whether the array index is a single
digit number or a double digit.
In FIFO, or a named Pipe, we store the messages in a temporary storage file.
Both the files read and write to that file to share messages.
Other than that, it is similar to message queues.

We have to run 'fifo_p1' before 'fifo_p2'.

-->Sockets
Sockets are a way of connecting two nodes on a network to communicate with each
other. The server node (P2) listens on a particular port, while the client node
(P1) reaches out to form a connection.
We have used this form of programming in the sockets part of the question.

We have created a socket using the socket function, and this is binded. This
listens to requests and accepts request. In P1 we use socket command and 
connect. Thus we are connected by a socket pair. For this part, we have used a
Unix-Domain socket.

P1 generates the messages and uses write() to send them. Then, we read these
messages in P2, and create a confirmation message which is written back into
the same socket. P1 acknowledges this and sends the next batch of message.

The formation of string in P1, and printing it out in P2 is done the same way
as in the code for the FIFO part of the question. 

We have to run 'socket_p1' before 'socket_p2'.