#include <iostream>
#include <thread>
#include <vector>

void computeFactorial(int n) {
    long long fact = 1;
    for (int i = 2; i <= n; ++i)
        fact *= i;

    std::cout << "Factorial of " << n << " is " << fact << std::endl;
}

int main() {
    std::vector<int> numbers = {5, 7, 10, 12};
    std::vector<std::thread> threads;

    for (int num : numbers)
        threads.emplace_back(computeFactorial, num);

    for (auto &t : threads)
        t.join();

    return 0;
}
