#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>

#define MAX_PASSENGERS 50 // Increase the maximum passengers if needed

dispatch_semaphore_t loadSemaphore;
dispatch_semaphore_t unloadSemaphore;
dispatch_semaphore_t boardSemaphore;
dispatch_semaphore_t offboardSemaphore;
int capacity, totalPassengers;

// Function declarations
void* car(void* args);
void* passenger(void* args);
void load();
void unload();
void board(int id);
void offboard(int id);

void* car(void* args) {
    while (1) {
        load();
        for (int i = 0; i < capacity; i++) {
            dispatch_semaphore_signal(loadSemaphore); // Signal passengers to board
        }
        for (int i = 0; i < capacity; i++) {
            dispatch_semaphore_wait(boardSemaphore, DISPATCH_TIME_FOREVER); // Wait for all passengers to board
        }
        // Simulate ride duration
        sleep(2);
        unload();
        for (int i = 0; i < capacity; i++) {
            dispatch_semaphore_signal(unloadSemaphore); // Signal passengers to offboard
        }
        for (int i = 0; i < capacity; i++) {
            dispatch_semaphore_wait(offboardSemaphore, DISPATCH_TIME_FOREVER); // Wait for all passengers to offboard
        }
    }
}

void* passenger(void* args) {
    int id = *(int*)args;
    while (1) {
        dispatch_semaphore_wait(loadSemaphore, DISPATCH_TIME_FOREVER); // Wait for car to load
        board(id);
        dispatch_semaphore_signal(boardSemaphore); // Notify car that passenger has boarded
        dispatch_semaphore_wait(unloadSemaphore, DISPATCH_TIME_FOREVER); // Wait for car to unload
        offboard(id);
        dispatch_semaphore_signal(offboardSemaphore); // Notify car that passenger has offboarded
    }
}

void load() {
    printf("Car is loading...\n");
    sleep(1);
}

void unload() {
    printf("Car is unloading...\n");
    sleep(1);

}

void board(int id) {
    printf("Passenger %d is boarding...\n", id);
    sleep(1);
}

void offboard(int id) {
    printf("Passenger %d is offboarding...\n", id);
    sleep(1);
}

int main() {
    printf("Enter the total number of passengers: ");
    scanf("%d", &totalPassengers);
    printf("Enter the capacity of the car: ");
    scanf("%d", &capacity);

    if (totalPassengers > MAX_PASSENGERS) {
        printf("The number of passengers exceeds the maximum limit of %d.\n", MAX_PASSENGERS);
        return 1;
    }
    if (capacity > totalPassengers) {
        printf("Car capacity cannot be more than the total number of passengers.\n");
        return 1;
    }

    pthread_t carThread, passengerThreads[MAX_PASSENGERS];
    loadSemaphore = dispatch_semaphore_create(0);
    unloadSemaphore = dispatch_semaphore_create(0);
    boardSemaphore = dispatch_semaphore_create(0);
    offboardSemaphore = dispatch_semaphore_create(0);

    pthread_create(&carThread, NULL, car, NULL);
    for (int i = 0; i < totalPassengers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&passengerThreads[i], NULL, passenger, (void*)id);
    }

    pthread_join(carThread, NULL);
    for (int i = 0; i < totalPassengers; i++) {
        pthread_join(passengerThreads[i], NULL);
    }

    return 0;
}