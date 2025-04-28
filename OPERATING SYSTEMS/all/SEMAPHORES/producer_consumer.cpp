#include <iostream>
using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]; // use array instead of queue
int front = 0, rear = 0;
int emptySlots = BUFFER_SIZE;
int fullSlots = 0;

void produce(int item) {
    if (emptySlots == 0) {
        cout << "Buffer is full! Cannot produce item: " << item << endl;
        return;
    }
    buffer[rear] = item;
    cout << "Produced item: " << item << " at position " << rear << endl;
    rear = (rear + 1) % BUFFER_SIZE; // Circular Buffer
    emptySlots--;
    fullSlots++;
}

void consume() {
    if (fullSlots == 0) {
        cout << "Buffer is empty! Cannot consume item." << endl;
        return;
    }
    int item = buffer[front];
    cout << "Consumed item: " << item << " from position " << front << endl;
    front = (front + 1) % BUFFER_SIZE; // Circular Buffer
    fullSlots--;
    emptySlots++;
}

int main() {
    int choice, item = 0;
    while (true) {
        cout << "\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                item++;
                produce(item);
                break;
            case 2:
                consume();
                break;
            case 3:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
