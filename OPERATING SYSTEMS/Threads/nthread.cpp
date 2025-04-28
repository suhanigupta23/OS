#include <iostream>
#include <thread>
#include <vector>

void printThreadID(int id) {
    std::cout << "Thread ID: " << id << " (std::thread::id = " << std::this_thread::get_id() << ")\n";
}

int main() {
    const int N = 5; // Change this to create more threads
    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i) {
        threads.emplace_back(printThreadID, i);
    }

    for (auto &t : threads) {
        t.join(); // Wait for all threads to finish
    }

    return 0;
}
