#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    int fds[2];
    pid_t pid;
    if (pipe(fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);

        int outputFile = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outputFile == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(outputFile, STDOUT_FILENO);

        execlp("sort", "sort", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        FILE* stream;
        close(fds[0]);
        stream = fdopen(fds[1], "w");
        if (stream == NULL) {
            perror("fdopen");
            exit(EXIT_FAILURE);
        }
        fprintf(stream, "This is a test.\n");
        fprintf(stream, "Hello, world.\n");
        fprintf(stream, "My dog has fleas.\n");
        fprintf(stream, "This program is great.\n");
        fprintf(stream, "One fish, two fish.\n");
        fflush(stream);
        fclose(stream); 

        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
