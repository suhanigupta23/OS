#include <iostream>
#include <queue>
using namespace std;

int S = 1;  // initial semaphore value
queue<string> waitingQueue;

void wait(string processName) {
    S--;
    cout << processName << " calls wait. S = " << S << endl;
    if (S < 0) {
        cout << processName << " is BLOCKED and added to waiting queue.\n";
        waitingQueue.push(processName);
    }
}

void signal(string processName) {
    S++;
    cout << processName << " calls signal. S = " << S << endl;
    if (S <= 0 && !waitingQueue.empty()) {
        string wakingProcess = waitingQueue.front();
        waitingQueue.pop();
        cout << wakingProcess << " is UNBLOCKED from waiting queue.\n";
    }
}

int main() {
    wait("P1");
    wait("P2");
    wait("P3");
    signal("P1");
    signal("P2");
}
