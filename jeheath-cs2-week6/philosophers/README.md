John Heath
CS2 Assignment 6

Greedy Algorithm:
When the greedy algorithm is run in the terminal, each philospher is shown to have one 
dirty left fork, and then the program hits a standstill (deadlock). Since each 
philosopher thread is run independantly, and the first step in the greedy function is to
grab a left fork, it makes sense thay each philosopher would grab a left fork at the 
same time. However, since there are only 5 forks on the table, and the next command is
to grab a right fork, all philosphers will stall until a right fork frees. This will never 
happen so long as no philospher puts down their left fork, unlocking the mutex that 
prevents other philosophers from grabbing it. 

The maximum number of philosophers that can sit at the table while we are guaranteed
to avoid deadlock is 4. This idea is simple: deadlock will only occur if there is a situation
where a philosopher will never release their fork. If there are 4 philosophers at the 
table, all forks can be reached, so at least one philosopher has access to two forks at 
all times. After eating wth the forks, the philosophers will be obligated to return the 
forks and any nearby philosopher waiting for that fork will grab it immediatly. With
four philosophers, there can never be a situation where the forks are not returned. 

If this situation began with each philosopher holding a left, dirty fork, they would each 
request a fork from their right neighbor. Having recieved a request from their left 
neighbor, the fork is dirty, so they would each clean it and then pass it to their left. Each 
philosopher would then be able to pick up a clean fork from their right, after which they
would all request a fork from their left. This time their right fork is clean, so they would
all refuse to surrender their fork. This would lead to a deadlock