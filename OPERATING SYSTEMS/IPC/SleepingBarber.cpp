#include <bits/stdc++.h>
#include <semaphore.h>
#include <thread>
using namespace std;

sem_t sem_mutex; // Renamed mutex to sem_mutex to avoid ambiguity
sem_t barberReady; // Semaphore to check if barber is ready
sem_t customerReady; // Semaphore to check if customer is ready
int waitingCustomers = 0;

void barberFunc()
{
    while (true)
    {
        sem_wait(&customerReady); // Wait for a customer to arrive

        sem_wait(&sem_mutex); // Lock critical section
        waitingCustomers--;
        cout << "Barber is CUTTING hair.\n";
        sem_post(&sem_mutex); // Unlock critical section

        this_thread::sleep_for(chrono::seconds(2)); // Simulate hair cutting
        sem_post(&barberReady); // Signal customer that the barber is ready
    }
}

void customerFunc(int id)
{
    sem_wait(&sem_mutex); // Lock critical section
    if (waitingCustomers < 3) // Check if there is space in the waiting room
    {
        waitingCustomers++;
        cout << "Customer " << id << " is WAITING for a haircut.\n";
        sem_post(&sem_mutex); // Unlock critical section

        sem_post(&customerReady); // Signal the barber that a customer has arrived
        sem_wait(&barberReady); // Wait until the barber is ready
        cout << "Customer " << id << " is GETTING haircut.\n";
    }
    else
    {
        sem_post(&sem_mutex); // Unlock critical section
        cout << "Customer " << id << " is LEAVING since the waiting room is full.\n";
    }
}

int main()
{
    int numCustomers;

    // Take user input for the number of customers
    cout << "Enter the number of customers: ";
    cin >> numCustomers;

    // Initialize semaphores
    sem_init(&sem_mutex, 0, 1); // Semaphore for critical section
    sem_init(&barberReady, 0, 0); // Barber is initially not ready
    sem_init(&customerReady, 0, 0); // No customers initially

    // Start barber thread
    thread barber(barberFunc);

    // Start customer threads based on user input
    vector<thread> customers;
    for (int i = 0; i < numCustomers; i++)
    {
        customers.push_back(thread(customerFunc, i));
        this_thread::sleep_for(chrono::seconds(1)); // New customer arrives every second
    }

    // Join threads
    barber.join();
    for (auto &c : customers)
        c.join();

    // Destroy semaphores
    sem_destroy(&sem_mutex);
    sem_destroy(&barberReady);
    sem_destroy(&customerReady);

    return 0;
}
