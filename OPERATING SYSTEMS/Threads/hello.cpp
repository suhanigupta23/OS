#include <iostream>
#include <thread>

void sayHello() {
    std::cout << "Hello from thread" << std::endl;
}

int main() {
    std::thread t(sayHello); // Create 1 thread
    t.join();                // Wait for it to finish

    return 0;
}
