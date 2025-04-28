#include <iostream>
#include <vector>
#include <iomanip>  // for setw()

using namespace std;

struct Customer {
    int arrival_time;
    int service_time;
};

int main() {
    int n;
    cout << "Enter number of customers: ";
    cin >> n;

    vector<Customer> customers(n);

    cout << "Enter arrival time and service time for each customer:\n";
    for (int i = 0; i < n; ++i) {
        cin >> customers[i].arrival_time >> customers[i].service_time;
    }

    int current_time = 0;
    int total_waiting_time = 0;

    // Print table header
    cout << "\n";
    cout << setw(10) << "Customer" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Service Time" 
         << setw(15) << "Start Time" 
         << setw(15) << "Finish Time" 
         << setw(15) << "Waiting Time" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < n; ++i) {
        if (current_time < customers[i].arrival_time) {
            current_time = customers[i].arrival_time;
        }
        int start_time = current_time;
        int finish_time = start_time + customers[i].service_time;
        int waiting_time = start_time - customers[i].arrival_time;

        total_waiting_time += waiting_time;

        // Print each customer's info
        cout << setw(10) << i + 1 
             << setw(15) << customers[i].arrival_time 
             << setw(15) << customers[i].service_time 
             << setw(15) << start_time 
             << setw(15) << finish_time 
             << setw(15) << waiting_time << endl;

        current_time = finish_time;
    }

    double average_waiting_time = (double)total_waiting_time / n;

    cout << "\nTotal waiting time = " << total_waiting_time << endl;
    cout << "Average waiting time = " << average_waiting_time << endl;

    return 0;
}
