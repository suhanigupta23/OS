#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference sequence:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    vector<int> memory;
    vector<int> frequency;
    int page_faults = 0;
    int page_hits = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < memory.size(); j++) {
            if (memory[j] == pages[i]) {
                frequency[j]++;
                found = true;
                break;
            }
        }

        if (found) {
            page_hits++;
        } else {
            if (memory.size() < frames) {
                memory.push_back(pages[i]);
                frequency.push_back(1);
            } else {
                int lfu_index = 0;
                for (int j = 1; j < frequency.size(); j++) {
                    if (frequency[j] < frequency[lfu_index]) {
                        lfu_index = j;
                    }
                }
                memory[lfu_index] = pages[i];
                frequency[lfu_index] = 1;
            }
            page_faults++;
        }

        cout << "Frame content after page " << pages[i] << ": ";
        for (int x : memory)
            cout << x << " ";
        cout << endl;
    }

    cout << "\nTotal Page Faults = " << page_faults << endl;
    cout << "Total Page Hits = " << page_hits << endl;

    return 0;
}
