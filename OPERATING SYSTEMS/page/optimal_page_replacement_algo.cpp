#include <iostream>
using namespace std;

int predict(int pages[], int frames[], int n, int currentIndex, int capacity) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        // If the page is never referenced again
        if (j == n)
            return i;
    }
    return (index == -1) ? 0 : index;
}

void optimalPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int pageFaults = 0, pageHits = 0;
    int filled = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        bool found = false;

        // Check if page is already present
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                pageHits++;
                break;
            }
        }

        if (!found) {
            if (filled < capacity) {
                frames[filled++] = pages[i];
            } else {
                int pos = predict(pages, frames, n, i + 1, capacity);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }

        // Display frames after each page insertion
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

    optimalPageReplacement(pages, n, capacity);

    return 0;
}
