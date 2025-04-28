#include <bits/stdc++.h>
#include <thread>
#include <semaphore.h>
using namespace std;

// Semaphore declarations
sem_t agentSem;
sem_t tobacco;
sem_t paper;
sem_t match;

sem_t tobaccoSem;
sem_t paperSem;
sem_t matchSem;
sem_t semMutex; // Renamed from 'mutex' to 'semMutex'

// Ingredient flags
bool isTobacco = false;
bool isPaper = false;
bool isMatch = false;

// Agent function to place ingredients on the table
void agent()
{
    while (true)
    {
        sem_wait(&agentSem);  // Wait for smoker to be ready
        int item = rand() % 3;
        if (item == 0)
        {
            cout << "Agent puts TOBACCO and PAPER.\n";
            sem_post(&tobacco); // Give tobacco
            sem_post(&paper);   // Give paper
        }
        else if (item == 1)
        {
            cout << "Agent puts PAPER and MATCH.\n";
            sem_post(&paper);   // Give paper
            sem_post(&match);   // Give match
        }
        else
        {
            cout << "Agent puts MATCH and TOBACCO.\n";
            sem_post(&match);   // Give match
            sem_post(&tobacco); // Give tobacco
        }
        this_thread::sleep_for(chrono::seconds(2));
    }
}

// Smoker function to take ingredients and smoke
void smoker(string itemName, sem_t *myItem, sem_t *otherItem1, sem_t *otherItem2)
{
    while (true)
    {
        sem_wait(myItem);  // Wait for the ingredient
        cout << ">> Smoker with " << itemName << " is SMOKING.\n";
        this_thread::sleep_for(chrono::seconds(3)); // Smoking time
        sem_post(&agentSem);  // Let the agent know the smoker is done
    }
}

// Functions for each ingredient type (Tobacco, Paper, Match)
void tobaccoFunc()
{
    sem_wait(&semMutex); // Use semMutex to lock the resource
    if (isPaper)
    {
        isPaper = false;
        sem_post(&matchSem);  // Notify match smoker
    }
    else if (isMatch)
    {
        isMatch = false;
        sem_post(&paperSem);  // Notify paper smoker
    }
    else
    {
        isTobacco = true;
    }
    sem_post(&semMutex); // Unlock semMutex
}

void paperFunc()
{
    sem_wait(&semMutex); // Use semMutex to lock the resource
    if (isTobacco)
    {
        isTobacco = false;
        sem_post(&matchSem);  // Notify match smoker
    }
    else if (isMatch)
    {
        isMatch = false;
        sem_post(&tobaccoSem);  // Notify tobacco smoker
    }
    else
    {
        isPaper = true;
    }
    sem_post(&semMutex); // Unlock semMutex
}

void matchFunc()
{
    sem_wait(&semMutex); // Use semMutex to lock the resource
    if (isTobacco)
    {
        isTobacco = false;
        sem_post(&paperSem);  // Notify paper smoker
    }
    else if (isPaper)
    {
        isPaper = false;
        sem_post(&tobaccoSem);  // Notify tobacco smoker
    }
    else
    {
        isMatch = true;
    }
    sem_post(&semMutex); // Unlock semMutex
}

int main()
{
    // Semaphore initialization
    sem_init(&agentSem, 0, 1);
    sem_init(&tobacco, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&match, 0, 0);
    sem_init(&tobaccoSem, 0, 0);
    sem_init(&paperSem, 0, 0);
    sem_init(&matchSem, 0, 0);
    sem_init(&semMutex, 0, 1);

    int num_smokers;
    cout << "Enter number of smokers: ";
    cin >> num_smokers;

    // Creating smokers' threads
    vector<thread> smokers;
    for (int i = 0; i < num_smokers; i++)
    {
        smokers.push_back(thread(smoker, "TOBACCO", &tobaccoSem, &paperSem, &matchSem));
        smokers.push_back(thread(smoker, "PAPER", &paperSem, &tobaccoSem, &matchSem));
        smokers.push_back(thread(smoker, "MATCH", &matchSem, &tobaccoSem, &paperSem));
    }

    // Creating other necessary threads
    thread agentThread(agent);
    thread tobaccoThread(tobaccoFunc);
    thread paperThread(paperFunc);
    thread matchThread(matchFunc);

    // Joining all threads
    for (auto &t : smokers)
        t.join();
    agentThread.join();
    tobaccoThread.join();
    paperThread.join();
    matchThread.join();

    return 0;
}
