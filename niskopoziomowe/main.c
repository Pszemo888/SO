#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        write(STDERR_FILENO, "Użycie: ", 8);
        write(STDERR_FILENO, argv[0], strlen(argv[0]));
        write(STDERR_FILENO, " plik1 plik2 ...\n", 18);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        char message[50];
        int len = snprintf(message, 50, "Zawartość pliku %s:\n", argv[i]);
        write(STDOUT_FILENO, message, len);
        if (print_file_content(argv[i]) == -1) {
            write(STDERR_FILENO, "Błąd odczytu pliku: ", 21);
            perror(argv[i]);
        }
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}

