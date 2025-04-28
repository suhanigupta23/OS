#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        cout << "Parent process, PID: " << getpid() << endl;
    } else if (pid == 0) {
        cout << "Child process, PID: " << getpid() << endl;
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
