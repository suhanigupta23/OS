#include <iostream>
#include <thread>
#include <cmath>
#include <vector>

void computeSqrt(int start, int end) {
    for (int i = start; i <= end; ++i) {
        std::cout << "sqrt(" << i << ") = " << std::sqrt(i) << std::endl;
    }
}

int main() {
    const int RANGE_START = 1;
    const int RANGE_END = 100;
    const int NUM_THREADS = 4;

    int chunkSize = (RANGE_END - RANGE_START + 1) / NUM_THREADS;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = RANGE_START + i * chunkSize;
        int end = (i == NUM_THREADS - 1) ? RANGE_END : start + chunkSize - 1;
        threads.emplace_back(computeSqrt, start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
