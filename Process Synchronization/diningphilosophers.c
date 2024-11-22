#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (id + 4) % NUM_PHILOSOPHERS
#define RIGHT (id + 1) % NUM_PHILOSOPHERS

int state[NUM_PHILOSOPHERS];
int philosopher_id[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

sem_t mutex, spoon[NUM_PHILOSOPHERS];

void test(int id) {
  if (state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[id] = EATING;
    printf("Philosopher %d takes spoon from %d and %d\n", id + 1, LEFT + 1, id + 1);
    printf("Philosopher %d is eating\n", id + 1);
    sem_post(&spoon[id]);
  }
}

void *pick_spoon(int id) {
  sem_wait(&mutex);
  state[id] = HUNGRY;
  printf("Philosopher %d is hungry\n", id + 1);
  test(id);
  sem_post(&mutex);
  sem_wait(&spoon[id]);
}

void *put_spoon(int id) {
  sem_wait(&mutex);
  state[id] = THINKING;
  printf("Philosopher %d is putting spoon %d and %d down\n", id + 1, LEFT + 1, id + 1);
  printf("Philosopher %d is thinking\n", id + 1);
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void *philosopher_activity(void *num) {
  int *id = (int *)num;
  while (1) {
    usleep(1000);  // Simulate thinking for 1 millisecond
    pick_spoon(*id);
    usleep(1000);  // Simulate eating for 1 millisecond
    put_spoon(*id);
  }
}

int main() {
  int i;
  pthread_t threads[NUM_PHILOSOPHERS];

  sem_init(&mutex, 0, 1);
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&spoon[i], 0, 0);
  }

  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_create(&threads[i], NULL, philosopher_activity, &philosopher_id[i]);
    printf("Philosopher %d is thinking\n", i + 1);
  }

  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_destroy(&mutex);
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_destroy(&spoon[i]);
  }

  return 0;
}
