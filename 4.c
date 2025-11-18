#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t room;
sem_t chopstick[5];
void * philosopher(void *);
void eat(int);
int main()
{
int i, a[5];
pthread_t tid[5];
/*limits the number of philosophers who can enter the "room" (try to pick up
chopsticks) to 4. This prevents all 5 from picking up one chopstick and deadlocking.*/
sem_init(&room,0,4);
for(i=0; i<5; i++)
//One semaphore for each chopstick, initialized to 1 (available)
sem_init(&chopstick[i], 0, 1);
for(i=0; i<5; i++)
{
a[i]=i;
//Each philosopher runs as a separate thread
pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
}
for(i=0;i<5;i++)
pthread_join(tid[i], NULL); 
}
void * philosopher(void * num)
{
int phil=*(int *)num;
sem_wait(&room);
printf("\nPhilosopher %d has entered room",phil);
sem_wait(&chopstick[phil]); // Pick left chopstick
sem_wait(&chopstick[(phil+1)%5]); // Pick right chopstick
eat(phil);
sleep(2); // Simulate eating time
printf("\nPhilosopher %d has finished eating", phil);
sem_post(&chopstick[(phil+1)%5]); // Put down right chopstick
sem_post(&chopstick[phil]); // Put down left chopstick
sem_post(&room); // Leave room
}
//Eating Function
void eat(int phil)
{
printf("\nPhilosopher %d is eating",phil);
}