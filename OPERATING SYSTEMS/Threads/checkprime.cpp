#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>

std::mutex printLock;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i)
        if (n % i == 0) return false;
    return true;
}

void checkPrimes(int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (isPrime(i)) {
            std::lock_guard<std::mutex> lock(printLock);
            std::cout << i << " is prime\n";
        }
    }
}

int main() {
    const int RANGE_START = 1;
    const int RANGE_END = 100;
    const int NUM_THREADS = 4;
    int chunk = (RANGE_END - RANGE_START + 1) / NUM_THREADS;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = RANGE_START + i * chunk;
        int end = (i == NUM_THREADS - 1) ? RANGE_END : start + chunk - 1;
        threads.emplace_back(checkPrimes, start, end);
    }

    for (auto &t : threads)
        t.join();

    return 0;
}
