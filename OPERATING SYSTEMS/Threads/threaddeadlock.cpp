#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex lockA;
std::mutex lockB;

void thread1() {
    lockA.lock();
    std::cout << "Thread 1 acquired Lock A\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lockB.lock(); // waiting for Lock B
    std::cout << "Thread 1 acquired Lock B\n";

    // Unlock in reverse order
    lockB.unlock();
    lockA.unlock();
}

void thread2() {
    lockB.lock();
    std::cout << "Thread 2 acquired Lock B\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    lockA.lock(); // waiting for Lock A
    std::cout << "Thread 2 acquired Lock A\n";

    lockA.unlock();
    lockB.unlock();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
