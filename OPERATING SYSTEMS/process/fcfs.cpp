#include <iostream>
#include <vector>
using namespace std;

// Define a structure for Process
struct Process {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

int main() {
    int n;
    float total_tat = 0, total_wt = 0;

    // Input
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
    }

    // Manually sort based on arrival time (using simple Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    // Calculate Completion Times
    processes[0].ct = processes[0].at + processes[0].bt;
    for (int i = 1; i < n; i++) {
        if (processes[i].at > processes[i - 1].ct) {
            processes[i].ct = processes[i].at + processes[i].bt;
        } else {
            processes[i].ct = processes[i - 1].ct + processes[i].bt;
        }
    }

    // Calculate TAT and WT
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        total_tat += processes[i].tat;
        total_wt += processes[i].wt;
    }

    // Output
    cout << "\nPId\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t"
             << processes[i].at << "\t"
             << processes[i].bt << "\t"
             << processes[i].ct << "\t"
             << processes[i].tat << "\t"
             << processes[i].wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << (total_tat / n) << endl;
    cout << "Average Waiting Time = " << (total_wt / n) << endl;

    return 0;
}