#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> maxNeed(n, vector<int>(m));
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter Maximum Need Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maxNeed[i][j];
        }
    }

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    vector<bool> finished(n, false);
    vector<int> safeSequence;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state!\n";
            return 0;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << "P" << safeSequence[i];
        if (i != safeSequence.size() - 1)
            cout << " -> ";
    }
    cout << endl;

    return 0;
}
