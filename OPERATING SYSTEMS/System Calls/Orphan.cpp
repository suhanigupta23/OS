#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(5);  // Child sleeps, parent dies
        cout << "Child process after parent died. PID: " << getpid() << endl;
    } else if (pid > 0) {
        cout << "Parent exiting immediately." << endl;
        exit(0);
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
