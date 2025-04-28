#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <mutex>

std::mutex sumLock;
long long totalSum = 0;

void partialSum(int start, int end) {
    long long localSum = 0;
    for (int i = start; i <= end; ++i)
        localSum += i;

    std::lock_guard<std::mutex> lock(sumLock);
    totalSum += localSum;
}

int main() {
    const int N = 1000;
    const int NUM_THREADS = 4;
    int chunk = N / NUM_THREADS;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * chunk + 1;
        int end = (i == NUM_THREADS - 1) ? N : start + chunk - 1;
        threads.emplace_back(partialSum, start, end);
    }

    for (auto &t : threads)
        t.join();

    std::cout << "Sum from 1 to " << N << " is: " << totalSum << std::endl;
    return 0;
}
