#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child process replacing itself with 'ls' command." << endl;
        execl("/bin/ls", "ls", NULL);
        cerr << "Exec failed!" << endl;
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
        cout << "Parent process after child finished." << endl;
    } else {
        cerr << "Fork failed!" << endl;
        exit(1);
    }
    return 0;
}
