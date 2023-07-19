# Philosophers-POSIX-Threads

**Philosophers Dining Problem**

## Overview

"Philosophers Dining Problem" is a fascinating personal project I developed during my journey as a software developer. It takes inspiration from the classic dining philosophers problem in computer science, showcasing my expertise in concurrent programming, problem-solving, and algorithm design.

## Description

The "Philosophers Dining Problem" project presents a well-implemented solution to the classical synchronization problem, featuring a group of philosophers sitting around a round table. Each philosopher has a plate of spaghetti and a fork on either side. They alternate between thinking and eating, but to diner, they must acquire both forks simultaneously. However, this situation poses a challenge of avoiding deadlock and starvation, which may arise if every philosopher tries to pick up their left fork at the same time, leading to a deadlock situation.

In this project, I employed various synchronization techniques, such as mutexes and semaphores, to ensure that the philosophers could enjoy their meals without encountering issues like deadlock or starvation. The implementation primarily utilizes C and expertly handles multiple threads to represent the philosophers and their actions.

## Key Features

- **Concurrent Programming with Threads**: The project demonstrates my proficiency in working with multiple threads and effectively managing their execution.

- **Synchronization Mechanisms**: I skillfully implemented mutexes and semaphores to handle shared resources (forks) and prevent conflicts among the philosophers.

- **Deadlock Prevention**: Through meticulous design, I ensured that the philosophers never enter a state of deadlock, enabling smooth progress in their dining process.

- **Starvation Avoidance**: Smart strategies were applied to prevent any philosopher from being stuck in an indefinite waiting state, effectively avoiding starvation scenarios.

## Outcome

Completing the "Philosophers Dining Problem" project has provided me with profound insights into the challenges of concurrent programming and synchronization problems. It showcases my ability to design robust algorithms and manage shared resources within a multi-threaded environment.

## Technologies Used

- C
- POSIX Threads (pthreads)

## Usage

To run the "Philosophers Dining Problem" project, follow these steps:

1. Clone the repository to your local machine.
2. Compile the C code using a C compiler with support for POSIX threads.
3. Run the compiled executable.

## Note

As a personal project, the primary focus was on learning and practical application. The project was not intended for commercial use but rather to demonstrate my skills in concurrent programming and problem-solving.
