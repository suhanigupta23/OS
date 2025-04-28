#include <bits/stdc++.h>
#include <thread> // For sleep
using namespace std;

#define ll long long

ll readcount = 0;
ll S = 1;    // Semaphore for critical section
ll wrt = 1;  // Semaphore for writer access
ll max_wait_time = 5; // Max wait for writer

bool wait(ll &S)
{
    if (S <= 0)
    {
        return false;
    }
    S--;
    return true;
}

void signal(ll &S)
{
    S++;
}

void reader_enter(ll id)
{
    if (!wait(S))
    {
        cout << "!! Reader " << id << " failed to enter critical section.\n";
        return;
    }

    readcount++;
    if (readcount == 1)
    {
        if (!wait(wrt))
        {
            readcount--;
            signal(S);
            cout << "!! Reader " << id << " failed because Writer was writing.\n";
            return;
        }
    }

    cout << ">> Reader " << id << " enters. Total Readers now = " << readcount << "\n";

    signal(S); // allow others

    // Reader is reading, but we don't simulate auto exit now.
    cout << ">> Reader " << id << " is READING data...\n";
}

void reader_exit(ll id)
{
    if (!wait(S))
    {
        cout << "!! Reader " << id << " failed to exit critical section.\n";
        return;
    }

    readcount--;
    cout << ">> Reader " << id << " exits. Remaining Readers = " << readcount << "\n";

    if (readcount == 0)
    {
        signal(wrt); // Last reader unlocks writer
    }

    signal(S);
}

void writer()
{
    int wait_time = 0;
    while (true)
    {
        if (readcount == 0 && wait(wrt))
        {
            cout << ">> Writer is WRITING data...\n";
            this_thread::sleep_for(chrono::seconds(2)); // simulate writing
            cout << ">> Writer finished writing.\n";
            signal(wrt);
            return;
        }

        wait_time++;

        if (wait_time >= max_wait_time)
        {
            cout << "!! Writer waited too long. Exiting to avoid deadlock.\n";
            return;
        }

        cout << "-- Writer waiting... Readers currently reading: " << readcount << "\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main()
{
    cout << "---- Reader-Writer Problem Simulation (Final Correct Version) ----\n";

    ll choice;
    ll reader_id = 1;
    map<ll, bool> active_readers; // Track active readers

    while (true)
    {
        cout << "\nMENU:\n";
        cout << "1. Reader wants to Enter (Read)\n";
        cout << "2. Reader wants to Exit (Done Reading)\n";
        cout << "3. Writer wants to Write\n";
        cout << "4. Exit Simulation\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            ll r;
            cout << "Enter number of readers entering together: ";
            cin >> r;
            for (ll i = 0; i < r; i++)
            {
                reader_enter(reader_id);
                active_readers[reader_id] = true;
                reader_id++;
            }
            break;
        }
        case 2:
        {
            if (active_readers.empty())
            {
                cout << "No active readers to exit.\n";
            }
            else
            {
                ll rid;
                cout << "Enter Reader ID to exit: ";
                cin >> rid;
                if (active_readers[rid])
                {
                    reader_exit(rid);
                    active_readers.erase(rid);
                }
                else
                {
                    cout << "Invalid Reader ID or already exited.\n";
                }
            }
            break;
        }
        case 3:
            writer();
            break;
        case 4:
            cout << "Exited.\n";
            exit(0);
        default:
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
