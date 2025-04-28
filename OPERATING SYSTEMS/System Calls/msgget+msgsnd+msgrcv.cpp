#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        cerr << "Message Queue creation failed!" << endl;
        return -1;
    }

    // Send message
    msg_buffer message;
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from parent!");
    msgsnd(msgid, &message, sizeof(message), 0);

    // Receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    cout << "Received Message: " << message.msg_text << endl;

    // Destroy message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
