#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Błąd: Zbyt mało argumentów. Użycie: %s <plik.txt> ... <plik.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        printf("Zawartość pliku: %s\n", argv[i]);
        if (print_file_content(argv[i]) == -1) {
            fprintf(stderr, "Błąd: Nie można odczytać pliku %s\n", argv[i]);
            perror("Błąd szczegóły");
            return EXIT_FAILURE;
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}

