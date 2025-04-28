#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return -1;
    }

    if (pid == 0) {  // Child process
        cout << "Child PID: " << getpid() << endl;
        sleep(10);  // Simulate long-running process
    } else {  // Parent process
        sleep(2);  // Allow child to start
        cout << "Parent sending signal to child..." << endl;
        kill(pid, SIGKILL);  // Send kill signal to child
        wait(NULL);  // Wait for child to exit
        cout << "Parent process finished." << endl;
    }

    return 0;
}
