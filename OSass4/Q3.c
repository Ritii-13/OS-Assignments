#include <stdio.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

#define MAX_CARS 100

dispatch_semaphore_t leftSem;
dispatch_semaphore_t rightSem;
dispatch_semaphore_t bridgeSem;
int carsOnBridge = 0;

void passing(int dir, int car_num) {
    printf("Car %d from the %s side is on the bridge\n", car_num, (dir == 0) ? "left" : "right");
    sleep(1);  // Simulate crossing the bridge
    printf("Car %d from the %s side has crossed the bridge\n", car_num, (dir == 0) ? "left" : "right");
}

void* left(void* args) {
    int car_num = *((int*)args);
    dispatch_semaphore_wait(leftSem, DISPATCH_TIME_FOREVER);
    dispatch_semaphore_wait(bridgeSem, DISPATCH_TIME_FOREVER);

    passing(0, car_num);

    dispatch_semaphore_signal(bridgeSem);
    dispatch_semaphore_signal(leftSem);
    return NULL;
}

void* right(void* args) {
    int car_num = *((int*)args);
    dispatch_semaphore_wait(rightSem, DISPATCH_TIME_FOREVER);
    dispatch_semaphore_wait(bridgeSem, DISPATCH_TIME_FOREVER);

    passing(1, car_num);

    dispatch_semaphore_signal(bridgeSem);
    dispatch_semaphore_signal(rightSem);
    return NULL;
}

int main() {
    int numLeft, numRight;

    printf("Enter the number of cars on the left side: ");
    scanf("%d", &numLeft);

    printf("Enter the number of cars on the right side: ");
    scanf("%d", &numRight);

    if (numLeft > MAX_CARS || numRight > MAX_CARS || numLeft < 0 || numRight < 0) {
        printf("Invalid input. The number of cars should be between 0 and %d.\n", MAX_CARS);
        return 1;
    }

    pthread_t threads[numLeft + numRight];
    int leftCarNum[numLeft], rightCarNum[numRight];

    leftSem = dispatch_semaphore_create(5);
    rightSem = dispatch_semaphore_create(5);
    bridgeSem = dispatch_semaphore_create(5);

    for (int i = 0; i < numLeft; i++) {
        leftCarNum[i] = i + 1;
        pthread_create(&threads[i], NULL, left, &leftCarNum[i]);
    }

    for (int i = 0; i < numRight; i++) {
        rightCarNum[i] = i + 1;
        pthread_create(&threads[numLeft + i], NULL, right, &rightCarNum[i]);
    }

    for (int i = 0; i < numLeft + numRight; i++) {
        pthread_join(threads[i], NULL);
    }

    dispatch_release(leftSem);
    dispatch_release(rightSem);
    dispatch_release(bridgeSem);

    return 0;
}
