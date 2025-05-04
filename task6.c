#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_DIRS 1024

int is_directory(const char *name) {
    struct stat st;
    if (stat(name, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 1;
    }
    return 0;
}

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char *dirs[MAX_DIRS];
    int count = 0;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR || is_directory(entry->d_name)) {
            if (count < MAX_DIRS) {
                dirs[count] = strdup(entry->d_name);
                count++;
            }
        }
    }
    closedir(dir);

    qsort(dirs, count, sizeof(char *), cmp);

    printf("Subdirectories (sorted):\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
