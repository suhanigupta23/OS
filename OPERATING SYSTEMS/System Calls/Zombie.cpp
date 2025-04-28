#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child process exiting..." << endl;
        exit(0);
    } else if (pid > 0) {
        cout << "Parent sleeping for 10 seconds..." << endl;
        sleep(10);  // Child has exited, parent sleeps = zombie created
        cout << "Parent finished sleeping." << endl;
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
