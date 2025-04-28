#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

const int NUM_THREADS = 4;
const int TOTAL_ITERATIONS = 1e8;

void threadTask(int start, int end, long long &result) {
    for (int i = start; i < end; ++i) {
        result += i;
    }
}

int main() {
    // ---------- Single-threaded ----------
    auto start1 = std::chrono::high_resolution_clock::now();

    long long sum1 = 0;
    for (int i = 0; i < TOTAL_ITERATIONS; ++i) {
        sum1 += i;
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "[Single Thread] Sum: " << sum1 << ", Time: " << duration1.count() << " seconds\n";

    // ---------- Multi-threaded ----------
    auto start2 = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    std::vector<long long> partialSums(NUM_THREADS, 0);
    int chunk = TOTAL_ITERATIONS / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * chunk;
        int end = (i == NUM_THREADS - 1) ? TOTAL_ITERATIONS : start + chunk;
        threads.emplace_back(threadTask, start, end, std::ref(partialSums[i]));
    }

    for (auto &t : threads) {
        t.join();
    }

    long long totalSum = 0;
    for (auto val : partialSums) {
        totalSum += val;
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "[Multi Thread] Sum: " << totalSum << ", Time: " << duration2.count() << " seconds\n";

    return 0;
}
