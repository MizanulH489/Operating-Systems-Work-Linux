R//==========================================================
//
// Title:     Long Lab 2: Sync: Producer-Consumer
// Course:     CSC 4420
// Lab Number: Long Lab 2
// Author:     Mizanul Haque, Oke Amuwha
// Date:      10/13/22
// Description:
//  This program uses producer and consumer threads to do it's tasks. It ultimately serves to solve bounded buffer problems given by the lab.
// 
// Task: Mizanul Haque- Created Semaphore for mutex, full.  Created Buffer and Producer/Consumer Threads, and helped work on it.
//              Did Thread creation, as well as mutex.
//       Oke Amuwha- Helped on Semaphore for mutex, full, created semaphore for semaphore empty.
//                 Created Buffer and Producer/Consumer Threads, and helped work on it. Helped run test trials for the code. Worked on
//                 Did Thread creation, as well as mutex. Compiled the code    
//
//   Instructions: 1.link the pthread package two special libraries to provide multithreaded and 
//semaphore support using the command “gcc -lpthread <files>”
//                 2. Compile
//
//==========================================================




#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

//define values 
#define N_THREADS 3
#ifndef true
#define true 1
#define false 0
#endif


// Set semaphore
sem_t empty; // semaphore for when it is empty
sem_t full; // semaphore when bounded is full

// Create Mutex
pthread_mutex_t mutex;
buffer_item buffer[BUFFER_SIZE];

// buffer index
int ind = 0;

// insert item into buffer
int insert_item(buffer_item item) {

// overflow
if (ind == BUFFER_SIZE)
return -1;
buffer[ind++] = item;
return 0;
}

// remove item from buffer item 
int remove_item(buffer_item *item) {


if (ind == 0 || item == NULL) // if loop to do underflow
return -1;
in--;
return 0;
}

// Producer Thread
void *producer(void *param) {
buffer_item item;
while (true) {
item = rand() % 100;
sem_wait(&empty);
pthread_mutex_lock(&mutex);
if (insert_item(item))
printf("Can't insert item\n");
else
printf("Producer %d: produced %d\n", *((int*)param), item);
pthread_mutex_unlock(&mutex);
sem_post(&full);
}
}

// Consumer Thread
void *consumer(void *param) {
while (true) {
buffer_item item = NULL;
if (ind > 0)
item = buffer[ind - 1];
sem_wait(&full);
pthread_mutex_lock(&mutex);
if (remove_item(&item))
printf("Can't remove item\n");
else
printf("Consumer %d: consumed %d\n", *((int*)param), item);
pthread_mutex_unlock(&mutex);
sem_post(&empty);
}
}

int main(int argc, char* argv[]) {
pthread_t prod[N_THREADS], con[N_THREADS];
pthread_mutex_init(&mutex, NULL);
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);

// Create threads
int number[N_THREADS];

for (int i = 0;i < N_THREADS;i++) {

// Thread label
number[i] = i + 1;

// Create Producer and Consumer Threads
pthread_create(&prod[i], NULL, (void*)producer, (void*)&number[i]); // craete producer thread 
pthread_create(&con[i], NULL, (void*)consumer, (void*)&number[i]); // craete consumer threads
}

for (int i = 0;i < N_THREADS;i++) {
pthread_join(con[i], NULL);
pthread_join(prod[i], NULL);
}

// Free memory
pthread_mutex_destroy(&mutex);
sem_destroy(&empty);
sem_destroy(&full);

return 0;
}