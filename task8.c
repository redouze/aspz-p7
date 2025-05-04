#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int is_regular_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return 0;
    }
    return S_ISREG(path_stat.st_mode);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (!is_regular_file(entry->d_name))
            continue;

        printf("Delete file \"%s\"? (y/n): ", entry->d_name);
        char response[8];
        if (!fgets(response, sizeof(response), stdin)) {
            perror("fgets");
            continue;
        }

        if (response[0] == 'y' || response[0] == 'Y') {
            if (unlink(entry->d_name) == 0) {
                printf("Deleted \"%s\".\n", entry->d_name);
            } else {
                perror("unlink");
            }
        } else {
            printf("Skipped \"%s\".\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
