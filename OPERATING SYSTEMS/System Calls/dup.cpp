// File: dup_example.cpp
#include <iostream>
#include <fcntl.h>    
#include <unistd.h>   
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {
    int fd = open("dup_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int fd_dup = dup(fd);

    write(fd, "Writing using original FD\n", 26);
    write(fd_dup, "Writing using duplicated FD\n", 28);

    close(fd);
    close(fd_dup);
    cout << "Data written successfully using dup." << endl;
    return 0;
}
