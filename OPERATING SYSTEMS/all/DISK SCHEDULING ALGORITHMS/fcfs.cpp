#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n, head;
    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests:\n";
    for (int i = 0; i < n; ++i) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    int seek = 0;

    cout << "FCFS Order: ";
    for (int req : requests) {
        cout << req << " ";
        seek += abs(head - req);
        head = req;
    }
    cout << "\nTotal seek operations = " << seek << endl;

    return 0;
}
