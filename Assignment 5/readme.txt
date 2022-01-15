Operating Systems (CSE 231)
Assignment 5 (Bonus Assignment)
Utkarsh Arora
2020143

In this assignment, we have solved the Dining Philosopher's Problem.
In this problem, 5 philosophers are seated at a round table, and there
are 5 forks lying on the table.
We index the philosophers as 0,1,2,3,4. We also index the forks as
0,1,2,3,4; such that the fork lying on the left of a philosopher is i,
and the fork lying on the right is (i+1)%5.
We have implemented the 5 philosophers as threads.
We have used an array of semaphores to represent the forks.
For parts 2 and 3 of the problem, we have used a counting semaphore to 
represent the sauce bowls.

The structure and paradigm of all 3 parts of the problem is similar,
with differences based on the question.

In each part of the question, I have added a sleep(4) timer, to demonstrate
the solution better.

--PART 1--
Each Philosopher needs to pick up two forks, the one on his left and the one
on his right. The Philosophers pick up first the fork on the left, and then
the fork on the right. All philosopher threads are synchronised, and the
threads cannot communicate with each other. Thus, all philosophers will pick
up the fork on their left. Then they will try to pick up the fork on their
right, but the fork on the right is already unavailable. Each philosopher will
wait for the philosopher on their right to put down their fork, which will
never happen, leading to a deadlock scenario.
To fix this deadlock, the Philosopher 4 tries to pick up the fork on his right
first. Thus, Fork 0 will be picked up by Philosopher 0, and Philosopher 4 will 
wait for P0 to put down the fork. Thus, P3 will be able to pick up both F3 and
F4, eat, and put them both down. Then, P2 will be able to pick up both F2 and
F3, and eat, and so on and so forth. Thus, the deadlock is solved, meaning that
all the philosophers can eat.

--PART 2--
In this part, we have four Sauce Bowls on the table. Each Philosopher needs one
fork and one sauce bowl.
Since each Philosopher needs one fork to eat, there is no chance of a deadlock.

There was no code needed for this part as there is no deadlock, but for 
thoroughness and self satifaction, I have coded this part as well.

Each Philosopher picks up the fork on their left. Each Philosopher also tries
to pick up a sauce bowl. However, after 4 Sauce Bowls are picked up, the
counting semaphore locks, and is only unlocked after a sauce bowl is put back.

Thus, there is no chance of a deadlock.

--PART 3--
In this part, we again have four Sauce Bowls on the table, and each philosopher
needs two forks and one sauce bowl to eat.

Thus, for the solution of this part, we have combined the solutions of part 1
and part 2, to remove deadlocks.

Reference: https://medium.com/swlh/the-dining-philosophers-problem-solution-in-c-90e2593f64e8