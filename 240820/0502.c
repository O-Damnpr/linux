#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void count(const char *path, int *f, int *d) {
    struct dirent *e;
    DIR *dp = opendir(path);
    if (!dp) return;
    while ((e = readdir(dp))) {
        if (strcmp(e->d_name, ".") && strcmp(e->d_name, "..")) {
            e->d_type == DT_DIR ? (*d)++ : (*f)++;
            if (e->d_type == DT_DIR) {
                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, e->d_name);
                count(new_path, f, d);
            }
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    int f = 0, d = 0;
    if (argc == 2) count(argv[1], &f, &d);
    printf("%d %d\n", f, d);
    return 0;
}
