#include <iostream>
using namespace std;

class BinarySemaphore {
private:
    int value; 

public:
    BinarySemaphore() {
        value = 1; 
    }

    void wait() {
        while (value <= 0) {
            
        }
        value--;
    }

    void signal() {
        value++;
    }

    int getValue() {
        return value;
    }
};

int main() {
    BinarySemaphore sem;

    cout << "Initial semaphore value: " << sem.getValue() << endl;

    cout << "Trying to acquire semaphore...\n";
    sem.wait(); 

    cout << "Semaphore acquired. Value: " << sem.getValue() << endl;

    cout << "Releasing semaphore...\n";
    sem.signal(); 

    cout << "Semaphore released. Value: " << sem.getValue() << endl;

    return 0;
}
