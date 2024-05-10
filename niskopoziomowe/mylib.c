#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "mylib.h"

int print_file_content(const char *filename) {
    char buffer[1024];
    int fd, bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (lseek(fd, 0, SEEK_END) == 0) {
        fprintf(stderr, "Plik '%s' jest pusty.\n", filename);
        close(fd);
        return -1;
    }

    lseek(fd, 0, SEEK_SET);

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            close(fd);
            return -1;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

