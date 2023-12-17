# OS 

This repository contains three examples of concurrent programming using pthreads and dispatch semaphores in C. Each example simulates a different concurrency problem.

## 1. Dining Philosophers

### Overview
The Dining Philosophers problem is a classic example of concurrent programming and synchronization. The code simulates a scenario where philosophers alternate between thinking and eating, using mutex locks to avoid deadlock.

### How it Works
- Each philosopher is represented by a thread.
- Mutex locks are used to manage access to forks and a shared bowl.
- Philosophers acquire forks in a specific order to avoid deadlock.
- The code demonstrates how to implement synchronized access to shared resources.

## 2. Amusement Park Simulation

### Overview
The Amusement Park Simulation simulates an amusement park ride with a car and passengers. The code uses dispatch semaphores to control the loading, unloading, boarding, and offboarding of passengers.

### How it Works
- The program consists of a car thread and multiple passenger threads.
- Dispatch semaphores are used to synchronize the various stages of the ride.
- Passengers signal the car to board, and the car signals passengers to offboard.
- The code demonstrates how to coordinate multiple threads using semaphores.

## 3. Bridge Crossing Problem

### Overview
The Bridge Crossing Problem simulates cars trying to cross a bridge from both sides. Dispatch semaphores are used to coordinate the crossing of cars and avoid collisions on the bridge.

### How it Works
- The program has threads representing cars approaching the bridge from the left and right sides.
- Dispatch semaphores control access to the bridge, allowing a limited number of cars to cross simultaneously.
- The code demonstrates how to use semaphores to prevent conflicts in a shared resource.

## How to Compile and Run
- make
- ./Q1
- ./Q2
- ./Q3