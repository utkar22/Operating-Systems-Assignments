READ ME
OS Assignment 2
Question 1
Utkarsh Arora
2020143

To compile: type make on the terminal, this will build and compile all the files
To run: type "./q1"

For this question, 3 files have been made
q1_new.c (main file)
e1.c (SR process)
e2.c (ST process)

Explanations:

For q1_new.c (Main file)
>The main process is forked and S1 process is created
>The PID of S1 process is stored in the local variable S1_pid
>It is then converted to a string, as only strings can be passed as arguments
in execl
>Inside the parent process, we first create the SR process by forking
>>SR Process will open the e1 file
>Then we create the ST process by forking
>>ST Process will open the e2 file
>In the process S1, we try to catch signals
>Handler for SIGTERM will print numbers and time whenever the kill signal is
sent from e1 and e2
>Handlers for SIGUSR1 and SIGUSR2 signals will store numbers in a global 
variable, which will be printed using the SIGTERM handler

For e1.c (For SR Process)
>Program recieves PID from S1 parent process, which is used to send back data
to the S1 Process
>A 64 bit random number is generated using inline assembly
>This number is sent back to the S1 process using sigqueue() and is printed in S1
>SIGUSR1 is used, which is a harmless signal. It is caught by S1's child process
which is stored using handler
>Kill instruction passes SIGTERM signal to S1 which is caught and handler prints
the random number generated

For e2.c (For ST Process)
>Same functionality as e1.c; generates CPU timestamp instead of random number. 
