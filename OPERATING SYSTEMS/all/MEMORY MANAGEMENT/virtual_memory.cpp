#include <iostream>
#include <vector>
using namespace std;

int main() {
    int frames, pages;
    cout << "Enter number of frames in memory: ";
    cin >> frames;
    cout << "Enter number of pages in process: ";
    cin >> pages;

    vector<int> page_references(pages);
    cout << "Enter page references:\n";
    for (int i = 0; i < pages; i++) {
        cin >> page_references[i];
    }

    vector<int> memory;
    int page_faults = 0;

    for (int i = 0; i < pages; i++) {
        bool found = false;
        for (int page : memory) {
            if (page == page_references[i]) {
                found = true;
                break;
            }
        }
        if (!found) { // page fault
            page_faults++;
            if (memory.size() < frames)
                memory.push_back(page_references[i]);
            else {
                memory.erase(memory.begin()); // FIFO Replacement
                memory.push_back(page_references[i]);
            }
        }
    }

    cout << "Total page faults: " << page_faults << endl;
    cout << "Total hits: " << pages - page_faults << endl;

    return 0;
}

