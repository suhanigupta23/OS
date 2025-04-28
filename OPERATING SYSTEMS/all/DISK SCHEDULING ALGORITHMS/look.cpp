#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void manualSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

int main() {
    int n, head;
    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests:\n";
    for (int i = 0; i < n; ++i) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    int seek = 0;
    vector<int> left, right;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    manualSort(left);
    manualSort(right);

    cout << "LOOK Order: ";
    for (int i = 0; i < right.size(); i++) {
        cout << right[i] << " ";
        seek += abs(head - right[i]);
        head = right[i];
    }
    for (int i = left.size() - 1; i >= 0; i--) {
        cout << left[i] << " ";
        seek += abs(head - left[i]);
        head = left[i];
    }

    cout << "\nTotal seek operations = " << seek << endl;

    return 0;
}
