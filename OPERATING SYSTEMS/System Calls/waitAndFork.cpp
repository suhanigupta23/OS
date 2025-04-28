#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child process running. PID: " << getpid() << endl;
        sleep(2);  // simulate child work
        cout << "Child process finished." << endl;
    } else if (pid > 0) {
        cout << "Parent process waiting for child to finish..." << endl;
        wait(NULL); // wait for child to finish
        cout << "Child finished, parent resuming." << endl;
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
