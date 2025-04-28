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

    for (int i = 0; i < n; i++) { // for each process
        int worstIndex = -1;
        for (int j = 0; j < m; j++) { // search worst fit
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
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
