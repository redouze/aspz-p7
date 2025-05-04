#include <stdio.h>
#include <stdlib.h>

#define LINES 20
#define LINE_LENGTH 1024

void show_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return;
    }

    char line[LINE_LENGTH];
    int line_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        fputs(line, stdout);
        line_count++;

        if (line_count == LINES) {
            printf("\npresse enter to continue");
            getchar();
            line_count = 0;
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file1> [file2 file3 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("===== %s =====\n", argv[i]);
        show_file(argv[i]);
    }

    printf("\n");
    return 0;
}
