#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int remainingTime;  // Used for Round Robin
    int waitingTime;    // Waiting Time
    int turnaroundTime; // Turnaround Time
    int completionTime; // Completion Time
    int responseTime;   // Response Time
    int queueNumber;    // Which queue the process belongs to
};

// Round Robin Scheduling
void roundRobinScheduling(queue<Process>& highPriorityQueue, vector<Process>& processes, int timeSlice) {
    int time = 0;
    while (!highPriorityQueue.empty()) {
        Process current = highPriorityQueue.front();
        highPriorityQueue.pop();

        // Set response time if it's the first time being executed
        if (current.responseTime == -1) {
            current.responseTime = time - current.arrivalTime;
        }

        // Execute the process for the time slice
        int executionTime = min(current.remainingTime, timeSlice);
        current.remainingTime -= executionTime;
        time += executionTime;

        // If process is not finished, put it back into the queue
        if (current.remainingTime > 0) {
            highPriorityQueue.push(current);
        } else {
            current.completionTime = time; // Correctly set completion time
            processes[current.pid - 1] = current;  // Update the process
        }
    }
}

// FCFS Scheduling
void fcfsScheduling(queue<Process>& lowPriorityQueue, vector<Process>& processes) {
    int time = 0;
    while (!lowPriorityQueue.empty()) {
        Process current = lowPriorityQueue.front();
        lowPriorityQueue.pop();

        // Set response time if it's the first time being executed
        if (current.responseTime == -1) {
            current.responseTime = time - current.arrivalTime;
        }

        // Execute the process
        time += current.burstTime;
        current.completionTime = time; // Correctly set completion time

        processes[current.pid - 1] = current;  // Update the process
    }
}

// Calculate Waiting Time and Turnaround Time for each process
void calculateTimes(vector<Process>& processes) {
    for (int i = 0; i < processes.size(); i++) {
        processes[i].waitingTime = processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to print the results in tabular format
void printTable(const vector<Process>& processes) {
    cout << setw(10) << "PID" << setw(15) << "Arrival Time" << setw(15) << "Burst Time"
         << setw(15) << "Completion Time" << setw(15) << "Waiting Time"
         << setw(15) << "Turnaround Time" << setw(15) << "Response Time" << setw(15) << "Queue No." << endl;

    for (const auto& p : processes) {
        cout << setw(10) << p.pid
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(15) << p.completionTime
             << setw(15) << p.waitingTime
             << setw(15) << p.turnaroundTime
             << setw(15) << p.responseTime
             << setw(15) << p.queueNumber << endl;
    }
}

int main() {
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter details for each process (PID, Arrival Time, Burst Time):" << endl;
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].responseTime = -1;  // Initializing response time as -1
        cout << "Process " << i + 1 << ":" << endl;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }

    // Separate processes into high and low priority queues
    queue<Process> highPriorityQueue;
    queue<Process> lowPriorityQueue;

    for (int i = 0; i < n; i++) {
        if (processes[i].burstTime <= 5) {  // High priority if burst time <= 5
            processes[i].queueNumber = 1;
            highPriorityQueue.push(processes[i]);
        } else {
            processes[i].queueNumber = 2;
            lowPriorityQueue.push(processes[i]);
        }
    }

    // Perform Multilevel Queue Scheduling
    int timeSlice = 1;  // Round Robin time slice (for high-priority queue)
    cout << "\nPerforming High Priority Scheduling (Round Robin)..." << endl;
    roundRobinScheduling(highPriorityQueue, processes, timeSlice);

    cout << "\nPerforming Low Priority Scheduling (FCFS)..." << endl;
    fcfsScheduling(lowPriorityQueue, processes);

    // Calculate waiting time and turnaround time for each process
    calculateTimes(processes);

    // Calculate average waiting time and turnaround time
    double totalWT = 0, totalTAT = 0;
    for (const auto& p : processes) {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }
    double avgWT = totalWT / n;
    double avgTAT = totalTAT / n;

    // Print results in table form
    printTable(processes);

    // Print average times
    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;

    return 0;
}
