#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

int main() {
    key_t key = ftok("progfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1) {
        cerr << "Shared Memory creation failed!" << endl;
        return -1;
    }

    char *str = (char*)shmat(shmid, (void*)0, 0);

    if (str == (char*)(-1)) {
        cerr << "Shared Memory attachment failed!" << endl;
        return -1;
    }

    // Parent writes into shared memory
    strcpy(str, "Hello from shared memory!");

    cout << "Parent wrote: " << str << endl;

    // Detach shared memory
    shmdt(str);

    return 0;
}
