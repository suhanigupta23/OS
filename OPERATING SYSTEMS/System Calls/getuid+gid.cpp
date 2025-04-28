#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    cout << "User ID (Real): " << getuid() << ", Group ID (Real): " << getgid() << endl;
    cout << "User ID (Effective): " << geteuid() << ", Group ID (Effective): " << getegid() << endl;

    return 0;
}
