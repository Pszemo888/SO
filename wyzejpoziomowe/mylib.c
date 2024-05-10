#include <stdio.h>
#include "mylib.h"

int print_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Błąd otwierania pliku");
        return -1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ferror(file)) {
            perror("Błąd odczytu pliku");
            fclose(file);
            return -1;
        }
        putchar(ch);
    }

    if (fclose(file) != 0) {
        perror("Błąd zamykania pliku");
        return -1;
    }

    return 0;
}

