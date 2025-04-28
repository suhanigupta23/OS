#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>

const int NUM_THREADS = 3;
const int CYCLES = 5;
sem_t sems[NUM_THREADS];

void roundRobinTask(int id) {
    for (int i = 0; i < CYCLES; ++i) {
        sem_wait(&sems[id]); // Wait for turn

        std::cout << "Thread " << id << " running (Cycle " << i + 1 << ")\n";

        // Signal next thread
        sem_post(&sems[(id + 1) % NUM_THREADS]);
    }
}

int main() {
    std::vector<std::thread> threads;

    // Initialize semaphores (first one unlocked)
    for (int i = 0; i < NUM_THREADS; ++i)
        sem_init(&sems[i], 0, (i == 0) ? 1 : 0);

    // Launch threads
    for (int i = 0; i < NUM_THREADS; ++i)
        threads.emplace_back(roundRobinTask, i);

    // Join threads
    for (auto &t : threads)
        t.join();

    // Destroy semaphores
    for (int i = 0; i < NUM_THREADS; ++i)
        sem_destroy(&sems[i]);

    return 0;
}
