#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int turn = 1;
const int CYCLES = 5;

void runInOrder(int id) {
    for (int i = 0; i < CYCLES; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [id] { return turn == id; });

        std::cout << "Thread " << id << " is running (Cycle " << i + 1 << ")\n";

        turn = (id % 3) + 1;
        cv.notify_all();
    }
}

int main() {
    std::thread t1(runInOrder, 1);
    std::thread t2(runInOrder, 2);
    std::thread t3(runInOrder, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
