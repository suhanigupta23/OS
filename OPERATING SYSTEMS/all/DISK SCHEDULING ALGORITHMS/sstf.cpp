#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
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
    vector<bool> visited(n, false);

    cout << "SSTF Order: ";
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX, idx = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - requests[j]) < min_distance) {
                min_distance = abs(head - requests[j]);
                idx = j;
            }
        }
        visited[idx] = true;
        seek += abs(head - requests[idx]);
        head = requests[idx];
        cout << head << " ";
    }

    cout << "\nTotal seek operations = " << seek << endl;

    return 0;
}
