#include <stdint.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static char* get_file_type(const struct stat* file_stat) {
    if (S_ISREG(file_stat->st_mode)) {
        return "Regular File";
    } else if (S_ISDIR(file_stat->st_mode)) {
        return "Directory";
    } else if (S_ISLNK(file_stat->st_mode)) {
        return "Symbolic Link";
    } else {
        return "Other";
    }
}

static char* convert_time_to_string(time_t time_value) {
    struct tm* tm_info = localtime(&time_value);
    static char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return buffer;
}

static char* get_full_path(const char* file_path) {
    static char* full_path = realpath(file_path, NULL;
    if (len != -1) {
        path[len] = '\0';
        snprintf(full_path, sizeof(full_path), "%s", path);
    } else {
        perror("readlink");
    }
    return full_path;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    if (argc > 2) {
        printf("Too many arguments provided.\n");
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        struct stat file_stat;
        if (stat(argv[1], &file_stat) != 0) {
            perror("Error retrieving file statistics");
            return 1;
        }

        printf("File: %s\n", argv[1]);
        printf("File type: %s \n", get_file_type(&file_stat));
        printf("Size: %lld bytes\n", (long long)file_stat.st_size);
        printf("Last modified: %s\n", convert_time_to_string(file_stat.st_mtime));
    }

    return 0;
}