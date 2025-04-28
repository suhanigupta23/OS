#include <iostream>
#include <thread>
#include <vector>

void computeSquare(int num) {
    int square = num * num;
    std::cout << "Square of " << num << " is " << square << "\n";
}

int main() {
    std::vector<int> numbers = {2, 3, 4, 5, 6}; // Input numbers
    std::vector<std::thread> threads;

    for (int num : numbers) {
        threads.emplace_back(computeSquare, num);
    }

    for (auto &t : threads) {
        t.join();
    }

    return 0;
}
