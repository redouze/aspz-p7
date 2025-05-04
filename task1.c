#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[1024];

    fp = popen("rwho | more", "r");

    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    int status = pclose(fp);

    printf("Finished the commad `rwho | more` with status: %d\n", status);

    return 0;
}
