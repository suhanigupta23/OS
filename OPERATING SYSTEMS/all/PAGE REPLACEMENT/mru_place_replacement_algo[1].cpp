#include <iostream>
using namespace std;

void mruPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int lastUsed[capacity]; // Track last used time
    int pageFaults = 0, pageHits = 0;
    int time = 0;
    int filled = 0;

    // Initialize frames and last used time
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;
        time++;

        // Check if page already exists (hit)
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                pageHits++;
                lastUsed[j] = time; // Update last used time on hit
                break;
            }
        }

        if (!found) {
            // If empty frame is available
            if (filled < capacity) {
                frames[filled] = pages[i];
                lastUsed[filled] = time;
                filled++;
            }
            else {
                // Find the most recently used page
                int mruIndex = 0;
                for (int j = 1; j < capacity; j++) {
                    if (lastUsed[j] > lastUsed[mruIndex])
                        mruIndex = j;
                }
                frames[mruIndex] = pages[i];
                lastUsed[mruIndex] = time;
            }
            pageFaults++;
        }

        // Print frame status after each page
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
    cout << "Hit Ratio: " << (float)pageHits / n << endl;
    cout << "Fault Ratio: " << (float)pageFaults / n << endl;
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

    mruPageReplacement(pages, n, capacity);

    return 0;
}
