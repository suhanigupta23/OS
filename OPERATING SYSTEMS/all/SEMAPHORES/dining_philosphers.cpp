#include <iostream>
using namespace std;

#define N 5

bool forkAvailable[N] = {true, true, true, true, true}; // All forks are free initially

void takeForks(int i) {
    int left = i;
    int right = (i + 1) % N;

    if (forkAvailable[left] && forkAvailable[right]) {
        forkAvailable[left] = false;
        forkAvailable[right] = false;
        cout << "Philosopher " << i << " takes forks " << left << " and " << right << " and starts eating.\n";
    } else {
        cout << "Philosopher " << i << " cannot eat now (forks not available).\n";
    }
}

void putForks(int i) {
    int left = i;
    int right = (i + 1) % N;

    if (!forkAvailable[left] && !forkAvailable[right]) {
        forkAvailable[left] = true;
        forkAvailable[right] = true;
        cout << "Philosopher " << i << " puts down forks " << left << " and " << right << ". Now thinking.\n";
    } else {
        cout << "Philosopher " << i << " was not eating.\n";
    }
}

int main() {
    int choice, philosopher;
    while (true) {
        cout << "\n1. Take Forks (Start Eating)\n2. Put Forks (Stop Eating)\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter philosopher number (0 to 4): ";
                cin >> philosopher;
                if (philosopher >= 0 && philosopher < N)
                    takeForks(philosopher);
                else
                    cout << "Invalid philosopher number.\n";
                break;

            case 2:
                cout << "Enter philosopher number (0 to 4): ";
                cin >> philosopher;
                if (philosopher >= 0 && philosopher < N)
                    putForks(philosopher);
                else
                    cout << "Invalid philosopher number.\n";
                break;

            case 3:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
