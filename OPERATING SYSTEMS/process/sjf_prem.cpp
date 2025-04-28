#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid, bt, at, rt, wt, tat, ct, rt_time;
};

// Function to calculate waiting time, turnaround time, completion time, and response time
void calculateTimes(vector<Process>& processes) {
    int currentTime = 0, completed = 0;
    int n = processes.size();

    while (completed < n) {
        int idx = -1;
        int minRt = INT_MAX;

        // Find process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && processes[i].rt > 0 && processes[i].rt < minRt) {
                minRt = processes[i].rt;
                idx = i;
            }
        }

        // If no process is ready, increment time
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // If it's the first time the process is executed, set response time
        if (processes[idx].rt == processes[idx].bt) {
            processes[idx].rt_time = currentTime - processes[idx].at;
        }

        // Execute the process for one unit of time
        processes[idx].rt--;

        // If the process finishes, calculate its waiting and turnaround time
        if (processes[idx].rt == 0) {
            processes[idx].ct = currentTime + 1;  // Completion time
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
            completed++;
        }

        currentTime++;
    }
}

// Function to display process results
void displayResults(const vector<Process>& processes) {
    int totalWt = 0, totalTat = 0, totalRt = 0;
    cout << "PID\tAT\tBT\tWT\tTAT\tCT\tRT\n";
    for (const auto& proc : processes) {
        totalWt += proc.wt;
        totalTat += proc.tat;
        totalRt += proc.rt_time;
        cout << proc.pid << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.wt 
             << "\t" << proc.tat << "\t" << proc.ct << "\t" << proc.rt_time << endl;
    }
    cout << "Avg WT: " << (float)totalWt / processes.size() << "\n";
    cout << "Avg TAT: " << (float)totalTat / processes.size() << "\n";
    cout << "Avg RT: " << (float)totalRt / processes.size() << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].rt = processes[i].bt;  // Remaining time equals burst time initially
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    calculateTimes(processes);
    displayResults(processes);
    
    return 0;
}

