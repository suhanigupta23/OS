// File: multiple_children.cpp
#include <iostream>
#include <unistd.h>  
#include <sys/wait.h>
using namespace std;

int main() {
    int numChildren = 3;
    for (int i = 0; i < numChildren; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Child
            cout << "Child " << i << " PID: " << getpid() << endl;
            return 0;  // Important: child must exit loop
        }
    }

    // Parent waits for all children
    for (int i = 0; i < numChildren; i++) {
        wait(NULL);
    }

    cout << "Parent process done waiting." << endl;
    return 0;
}
