#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int priority; // Process Priority
};

// Comparator function to sort processes based on priority (descending) and arrival time
bool compare(Process p1, Process p2) {
    if (p1.priority == p2.priority)
        return p1.at < p2.at; // If priorities are the same, sort by arrival time
    return p1.priority > p2.priority; // Sort by priority (descending order)
}

void prioritySchedulingNonPreemptive(vector<Process>& processes, int n) {
    // Sort processes by priority (descending order)
    sort(processes.begin(), processes.end(), compare);

    int currentTime = 0;
    vector<bool> isCompleted(n, false);
    int completed = 0;

    // Calculate completion time for each process
    while (completed < n) {
        int idx = -1;

        // Find the process with the highest priority (since it's sorted by priority)
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].at <= currentTime) {
                idx = i;
                break;  // As soon as we find the process with the highest priority, break out
            }
        }

        if (idx == -1) {
            // No process is ready to execute, move forward in time
            currentTime++;
        } else {
            // Execute the selected process
            processes[idx].ct = currentTime + processes[idx].bt;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
            isCompleted[idx] = true;
            completed++;
            currentTime = processes[idx].ct;  // Update current time
        }
    }

    // Output the result
    cout << "\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (auto& p : processes) {
        cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.priority << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    // Calculate and display the average turnaround time and waiting time
    double avgTAT = 0, avgWT = 0;
    for (auto& p : processes) {
        avgTAT += p.tat;
        avgWT += p.wt;
    }

    cout << "\nAverage Turnaround Time: " << (avgTAT / n) << "\n";
    cout << "Average Waiting Time: " << (avgWT / n) << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time and Priority for Process " << (i + 1) << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].pid = i + 1;  // Assign Process ID
    }

    prioritySchedulingNonPreemptive(processes, n);

    return 0;
}