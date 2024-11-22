#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t writ, rea;
int reader_count = 0;

void *reader(void *arg) {
    sem_wait(&rea);
    reader_count++;
    if (reader_count == 1) {
        sem_wait(&writ);  // First reader locks the writer
    }
    sem_post(&rea);

    printf("Reader is reading\n");
    sleep(1);

    sem_wait(&rea);
    reader_count--;
    if (reader_count == 0) {
        sem_post(&writ);  // Last reader unlocks the writer
    }
    sem_post(&rea);
    return NULL;
}

void *writer(void *arg) {
    sem_wait(&writ);
    printf("Writer is writing\n");
    sleep(1);
    sem_post(&writ);
    return NULL;
}

int main() {
    pthread_t r, w;
    sem_init(&writ, 0, 1);
    sem_init(&rea, 0, 1);

    while (1) {
        pthread_create(&r, NULL, reader, NULL);
        pthread_create(&w, NULL, writer, NULL);
        sleep(2);
    }

    pthread_join(r, NULL);
    pthread_join(w, NULL);
    sem_destroy(&writ);
    sem_destroy(&rea);
    return 0;
}
