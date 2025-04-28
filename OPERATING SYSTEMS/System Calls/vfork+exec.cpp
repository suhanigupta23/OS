#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = vfork();  // Use vfork for creating a child process

    if (pid < 0) {
        cerr << "vFork failed!" << endl;
        return -1;
    }

    if (pid == 0) {  // Child process
        char *args[] = {"/bin/ls", "-l", NULL};
        execv(args[0], args);  // Replace child process with ls command
        cerr << "Exec failed!" << endl;
    } else {
        // Parent does nothing, just exits
        cout << "Parent process exiting." << endl;
    }

    return 0;
}
