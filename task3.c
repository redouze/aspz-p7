#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    const char *search_word = argv[1];
    const char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, search_word)) {
            printf("%s", line);
        }
    }

    fclose(fp);
    printf("\n");
    return 0;
}