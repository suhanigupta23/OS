#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip> // for setw
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compare(Process a, Process b) {
    if (a.arrival_time == b.arrival_time)
        return a.pid < b.pid;
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        processes[i].pid = i + 1;
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort(processes, processes + n, compare);

    queue<int> ready_queue;
    int time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    bool visited[n] = {false};
    visited[0] = true;
    ready_queue.push(0);

    while (completed < n) {
        if (!ready_queue.empty()) {
            int idx = ready_queue.front();
            ready_queue.pop();

            int exec_time = min(time_quantum, processes[idx].remaining_time);
            time += exec_time;
            processes[idx].remaining_time -= exec_time;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && processes[i].arrival_time <= time) {
                    ready_queue.push(i);
                    visited[i] = true;
                }
            }

            if (processes[idx].remaining_time > 0) {
                ready_queue.push(idx);
            } else {
                completed++;
                processes[idx].completion_time = time;
                processes[idx].turnaround_time = time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                total_turnaround_time += processes[idx].turnaround_time;
                total_waiting_time += processes[idx].waiting_time;
            }
        } else {
            time++;
        }
    }

    // Print Table
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t\t"
             << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t"
             << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t"
             << processes[i].waiting_time << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}
