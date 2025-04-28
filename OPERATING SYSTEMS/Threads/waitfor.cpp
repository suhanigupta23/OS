#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mtx;
bool dataReady = false;

void waitingThread() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Waiting for data...\n";
    cv.wait(lock, [] { return dataReady; });
    std::cout << "Data received, proceeding!\n";
}

void signalingThread() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> lock(mtx);
        dataReady = true;
        std::cout << "Data is ready. Notifying...\n";
    }
    cv.notify_one();
}

int main() {
    std::thread t1(waitingThread);
    std::thread t2(signalingThread);

    t1.join();
    t2.join();

    return 0;
}
