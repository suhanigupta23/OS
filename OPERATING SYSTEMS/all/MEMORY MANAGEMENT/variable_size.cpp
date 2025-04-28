#include <iostream>
using namespace std;

int main() {
    int segments;
    cout << "Enter number of segments: ";
    cin >> segments;

    int base[segments], limit[segments];
    for (int i = 0; i < segments; i++) {
        cout << "Enter base address and limit (size) for segment " << i << ": ";
        cin >> base[i] >> limit[i];
    }

    int seg_num, offset;
    cout << "Enter segment number and offset: ";
    cin >> seg_num >> offset;

    if (seg_num >= segments || offset >= limit[seg_num]) {
        cout << "Invalid memory access (Segmentation Fault)" << endl;
    } else {
        int physical_address = base[seg_num] + offset;
        cout << "Physical Address: " << physical_address << endl;
    }

    return 0;
}
