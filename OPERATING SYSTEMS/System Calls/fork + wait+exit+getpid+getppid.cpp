#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return -1;
    }

    if (pid == 0) {  // Child process
        cout << "Child process PID: " << getpid() << ", Parent PID: " << getppid() << endl;
        exit(0);  // Child exits
    } else {  // Parent process
        int status;
        wait(&status);  // Parent waits for child to exit
        cout << "Parent process PID: " << getpid() << ", Child exit status: " << status << endl;
    }

    return 0;
}
