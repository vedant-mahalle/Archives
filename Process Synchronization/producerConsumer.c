#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 10

sem_t s, empty, full;

int in = 0, out = 0, buffer[N];

int produce_item() { return rand() % 100; }

void insert_item(int item) {
  buffer[in] = item;
  in = (in + 1) % N;
}

int remove_item() {
  int item = buffer[out];
  out = (out + 1) % N;
  return item;
}

void *Producer() {
  while (1) {
    int item = produce_item();
    sem_wait(&empty);  // Wait if buffer is full
    sem_wait(&s);      // Enter critical section
    insert_item(item);
    printf("Producer Produced %d\n", item);
    sem_post(&s);      // Exit critical section
    sem_post(&full);   // Signal that there is a new item in the buffer
    sleep(2);
  }
}

void *Consumer() {
  while (1) {
    sem_wait(&full);   // Wait if buffer is empty
    sem_wait(&s);      // Enter critical section
    int item = remove_item();
    printf("Consumer Consumed %d\n", item);
    sem_post(&s);      // Exit critical section
    sem_post(&empty);  // Signal that there is space in the buffer
    sleep(1);
  }
}

int main() {
  pthread_t producer, consumer;
  
  sem_init(&s, 0, 1);    // Semaphore for mutual exclusion
  sem_init(&empty, 0, N); // Semaphore to track empty slots in buffer
  sem_init(&full, 0, 0);  // Semaphore to track full slots in buffer

  pthread_create(&producer, NULL, Producer, NULL);
  pthread_create(&consumer, NULL, Consumer, NULL);
  
  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);
  
  sem_destroy(&s);
  sem_destroy(&empty);
  sem_destroy(&full);
  
  return 0;
}
