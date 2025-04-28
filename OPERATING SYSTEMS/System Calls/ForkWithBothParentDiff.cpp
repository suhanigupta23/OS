#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child process: Calculating 5 + 3 = " << (5 + 3) << endl;
    } else if (pid > 0) {
        cout << "Parent process: Calculating 10 * 2 = " << (10 * 2) << endl;
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
