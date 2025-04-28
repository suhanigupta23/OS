#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

// Mutex for protecting the spooler queue
mutex mtx;
condition_variable cv;

queue<string> spooler;  // queue for storing print jobs

// Function to add a print job
void addPrintJob(string job) {
    unique_lock<mutex> lock(mtx);  // lock mutex
    spooler.push(job);              // add job to spooler queue
    cout << "Job " << job << " added to spooler.\n";
    cv.notify_all();                // Notify printer daemon
}

// Printer daemon function to print jobs from the spooler
void printerDaemon() {
    while (true) {
        unique_lock<mutex> lock(mtx);

        // If there are no jobs in the spooler, wait for jobs
        while (spooler.empty()) {
            cv.wait(lock);  // Wait until there is a job
        }
        
        // Process the job
        string job = spooler.front();
        spooler.pop();
        
        cout << "Printing job: " << job << endl;
        
        lock.unlock();
        this_thread::sleep_for(chrono::seconds(2));  // Simulate printing time
    }
}

int main() {
    // Start the printer daemon in a separate thread
    thread printer(printerDaemon);

    int numberOfJobs;
    cout << "Enter the number of print jobs: ";
    cin >> numberOfJobs;

    // Take user input for the print jobs
    for (int i = 0; i < numberOfJobs; ++i) {
        string job;
        cout << "Enter name for print job " << i + 1 << ": ";
        cin >> job;
        addPrintJob(job);
        this_thread::sleep_for(chrono::seconds(1));  // Simulate some delay between job submissions
    }

    // Wait for the printer daemon thread to finish (it runs forever in this example)
    printer.join(); 
    
    return 0;
}
