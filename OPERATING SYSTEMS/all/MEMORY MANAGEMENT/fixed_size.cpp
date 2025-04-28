#include <iostream>
using namespace std;

int main() {
    int memory_size, frame_size, pages;
    cout << "Enter total memory size: ";
    cin >> memory_size;
    cout << "Enter frame size: ";
    cin >> frame_size;

    int frames = memory_size / frame_size;
    cout << "Total frames available: " << frames << endl;

    cout << "Enter number of pages of process: ";
    cin >> pages;

    if (pages > frames) {
        cout << "Memory is not enough to accommodate all pages!" << endl;
    } else {
        cout << "Memory Allocation (Paging):\n";
        for (int i = 0; i < pages; i++) {
            cout << "Page " << i << " -> Frame " << i << endl;
        }
    }

    return 0;
}
