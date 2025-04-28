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
        char *args[] = {"/bin/ls", "-l", NULL};  // execv command
        execv(args[0], args);  // Replace child with 'ls' command
        cerr << "Exec failed!" << endl;
    } else {  // Parent process
        wait(NULL);  // Parent waits for child to complete
        cout << "Child process finished execution." << endl;
    }

    return 0;
}
