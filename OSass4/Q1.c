#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define THINKING_TIME 1
#define EATING_TIME 2

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t bowl_mutex;
pthread_cond_t bowl_cond = PTHREAD_COND_INITIALIZER;
int bowl_available = 2; // Two bowls are available

void* philosopher(void* args);
void eating(int philosopher_number);
void thinking();

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    pthread_mutex_init(&bowl_mutex, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void*)(long)i);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void* philosopher(void* args) {
    int philosopher_number = (int)(long)args;

    while (1) {
        thinking();
        eating(philosopher_number);
    }
}

void eating(int philosopher_number) {
    // Acquire forks in a specific order to avoid deadlock
    int left_fork = philosopher_number;
    int right_fork = (philosopher_number + 1) % NUM_PHILOSOPHERS;

    pthread_mutex_lock(&forks[left_fork]);
    pthread_mutex_lock(&forks[right_fork]);

    // Acquire a bowl
    pthread_mutex_lock(&bowl_mutex);
    while (bowl_available == 0) {
        pthread_cond_wait(&bowl_cond, &bowl_mutex);
    }
    bowl_available--;
    pthread_mutex_unlock(&bowl_mutex);

    printf("Philosopher %d is eating.\n", philosopher_number);
    sleep(EATING_TIME);

    // Release the bowl
    pthread_mutex_lock(&bowl_mutex);
    bowl_available++;
    pthread_cond_signal(&bowl_cond);
    pthread_mutex_unlock(&bowl_mutex);

    // Release forks
    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);
}

void thinking() {
    sleep(THINKING_TIME);
}