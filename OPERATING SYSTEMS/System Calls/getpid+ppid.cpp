#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        cout << "Child PID: " << getpid() << ", Parent PID: " << getppid() << endl;
    } else {  // Parent process
        cout << "Parent PID: " << getpid() << ", Parent's Parent PID: " << getppid() << endl;
    }

    return 0;
}
