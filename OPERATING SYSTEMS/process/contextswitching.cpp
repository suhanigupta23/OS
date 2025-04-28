#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
    int responseTime;   // Response Time
};

int main() {
    int n, contextSwitch;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter context switch time: ";
    cin >> contextSwitch;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Process " << i + 1 << endl;
        cout << "Process ID: ";
        cin >> processes[i].pid;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }

    // Sort processes by arrival time (FCFS Scheduling)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                swap(processes[i], processes[j]);
            }
        }
    }

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    // Calculating times
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Response Time = current time - arrival time (when first picked)
        processes[i].responseTime = currentTime - processes[i].arrivalTime;

        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;

        if (i != n - 1) { // Add context switch time after every process except the last one
            currentTime += contextSwitch;
        }

        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
        totalRT += processes[i].responseTime;
    }

    // Output Header
    cout << "\n\n";
    cout << left << setw(12) << "ProcessID" 
         << setw(15) << "ArrivalTime" 
         << setw(12) << "BurstTime" 
         << setw(18) << "CompletionTime" 
         << setw(18) << "TurnaroundTime" 
         << setw(15) << "WaitingTime"
         << setw(15) << "ResponseTime" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    // Output process details
    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << processes[i].pid 
             << setw(15) << processes[i].arrivalTime 
             << setw(12) << processes[i].burstTime 
             << setw(18) << processes[i].completionTime 
             << setw(18) << processes[i].turnaroundTime 
             << setw(15) << processes[i].waitingTime
             << setw(15) << processes[i].responseTime << endl;
    }

    // Output averages
    cout << "\nAverage Waiting Time: " << (totalWT / n) << " units" << endl;
    cout << "Average Turnaround Time: " << (totalTAT / n) << " units" << endl;
    cout << "Average Response Time: " << (totalRT / n) << " units" << endl;

    return 0;
}