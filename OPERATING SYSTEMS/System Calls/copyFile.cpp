// File: copy_file.cpp
#include <iostream>
#include <fcntl.h>    
#include <unistd.h>   
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {
    int src = open("source.txt", O_RDONLY);
    if (src < 0) {
        perror("open source");
        return 1;
    }

    int dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("open destination");
        close(src);
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytesRead);
    }

    close(src);
    close(dest);
    cout << "File copied successfully." << endl;
    return 0;
}
