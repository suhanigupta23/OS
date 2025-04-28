#include <iostream>
using namespace std;

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int pointer = 0;  // Points to the frame to be replaced
    int pageFaults = 0, pageHits = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;
        
        // Check if page already exists (hit)
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                pageHits++;
                break;
            }
        }

        // If page not found, replace at pointer position (fault)
        if (!found) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % capacity; // Move pointer circularly
            pageFaults++;
        }

        // For visualization
        cout << "Page frames after inserting " << pages[i] << ": ";
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                cout << frames[j] << " ";
            else
                cout << "- ";
        }
        if (found)
            cout << " (Hit)";
        else
            cout << " (Fault)";
        cout << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pageHits << endl;
    cout << "Hit Ratio: " << (float)pageHits/n << endl;
    cout << "Fault Ratio: " << (float)pageFaults/n << endl;
}

int main() {
    int n, capacity;
    cout << "Enter the number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    cout << "Enter the number of frames (capacity): ";
    cin >> capacity;

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
