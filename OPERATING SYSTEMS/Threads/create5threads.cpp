#include <iostream>
#include <thread>
#include <vector>

void threadFunction(int threadNum) {
    std::cout << "Hello from Thread " << threadNum 
              << " (std::thread::id = " << std::this_thread::get_id() << ")\n";
}

int main() {
    const int NUM_THREADS = 5;
    std::vector<std::thread> threads;

    // Create 5 threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(threadFunction, i + 1);
    }

    // Join all threads
    for (auto &t : threads) {
        t.join();
    }

    std::cout << "All threads have finished.\n";
    return 0;
}
