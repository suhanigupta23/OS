#include <iostream>
using namespace std;

int readers = 0;   // count of active readers
bool writer = false; // whether a writer is writing

void startRead() {
    if (writer) {
        cout << "Writer is writing. Reader must wait.\n";
    } else {
        readers++;
        cout << "Reader started reading. Current readers: " << readers << endl;
    }
}

void endRead() {
    if (readers > 0) {
        readers--;
        cout << "Reader finished reading. Remaining readers: " << readers << endl;
    } else {
        cout << "No readers are reading currently.\n";
    }
}

void startWrite() {
    if (writer || readers > 0) {
        cout << "Cannot write now. Readers or another writer active.\n";
    } else {
        writer = true;
        cout << "Writer started writing.\n";
    }
}

void endWrite() {
    if (writer) {
        writer = false;
        cout << "Writer finished writing.\n";
    } else {
        cout << "No writer is writing currently.\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Start Reading\n2. End Reading\n3. Start Writing\n4. End Writing\n5. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                startRead();
                break;
            case 2:
                endRead();
                break;
            case 3:
                startWrite();
                break;
            case 4:
                endWrite();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
