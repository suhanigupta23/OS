#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    int priority = nice(10);  // Increase priority (lower priority number = higher priority)
    if (priority == -1) {
        cerr << "Failed to set priority!" << endl;
    } else {
        cout << "New priority value: " << priority << endl;
    }
    
    return 0;
}
