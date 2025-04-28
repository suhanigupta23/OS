#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    vector<int> blockSize(m);
    cout << "Enter size of each block:\n";
    for (int i = 0; i < m; i++) cin >> blockSize[i];

    cout << "Enter number of processes: ";
    cin >> n;
    vector<int> processSize(n);
    cout << "Enter size of each process:\n";
    for (int i = 0; i < n; i++) cin >> processSize[i];

    vector<int> allocation(n, -1); // initially all unallocated
    int lastAllocated = 0;

    for (int i = 0; i < n; i++) { // for each process
        bool allocated = false;
        for (int j = lastAllocated; j < m; j++) { // search from last allocated block
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j; // update last allocated block
                allocated = true;
                break;
            }
        }

        if (!allocated) { // If not allocated, search from the beginning
            for (int j = 0; j < lastAllocated; j++) {
                if (blockSize[j] >= processSize[i]) {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    lastAllocated = j;
                    break;
                }
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }

    return 0;
}
