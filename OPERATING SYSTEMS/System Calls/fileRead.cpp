// File: read_display.cpp
#include <iostream>
#include <fcntl.h>    // open()
#include <unistd.h>   // read(), write(), close()
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {
    int fd = open("testfile.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);  // 1 is the file descriptor for stdout
    }

    close(fd);
    return 0;
}
