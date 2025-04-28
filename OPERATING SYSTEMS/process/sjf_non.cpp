#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    vector<bool> isCompleted(n, false);

    // Input arrival time and burst time
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
    }

    int current_time = 0;
    int completed = 0;
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;

        // Find process with minimum burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].at <= current_time) {
                if (processes[i].bt < minBurst) {
                    minBurst = processes[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++; // No process has arrived yet
        } else {
            processes[idx].ct = current_time + processes[idx].bt;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;

            isCompleted[idx] = true;
            completed++;
            current_time = processes[idx].ct;

            total_tat += processes[idx].tat;
            total_wt += processes[idx].wt;
        }
    }

    // Output
    cout << "\nPId\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t"
             << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << (total_tat / n) << endl;
    cout << "Average Waiting Time = " << (total_wt / n) << endl;

    return 0;
}