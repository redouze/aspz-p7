#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_NAME_LEN 256

int has_c_extension(const char *filename) {
    size_t len = strlen(filename);
    return len > 2 && strcmp(filename + len - 2, ".c") == 0;
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
        if (entry->d_type != DT_REG)
            continue;

        if (!has_c_extension(entry->d_name))
            continue;

        printf("File: %s\n", entry->d_name);
        printf("Grant others read permission? (y/n): ");
        
        char answer[8];
        if (!fgets(answer, sizeof(answer), stdin)) {
            perror("fgets");
            break;
        }

        if (answer[0] == 'y' || answer[0] == 'Y') {
            struct stat st;
            if (stat(entry->d_name, &st) != 0) {
                perror("stat");
                continue;
            }

            mode_t new_mode = st.st_mode | S_IROTH;
            if (chmod(entry->d_name, new_mode) != 0) {
                perror("chmod");
            } else {
                printf("Permission granted to others for %s\n", entry->d_name);
            }
        } else {
            printf("Skipped %s\n", entry->d_name);
        }

        printf("\n");
    }

    closedir(dir);
    return 0;
}
