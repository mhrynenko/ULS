#include "../inc/uls.h"

void mx_tsort(char **arr, char *dir_path, t_flags *flags) {
    int len = 0;
    for (; arr[len] != NULL; len++);
    char *temp = NULL;

    for (int i = 0; i < len - 1; i++) {
        struct stat buf1;
        char *path1 = mx_strdup(dir_path);
        path1 = mx_strjoin(path1, arr[i]);
        lstat(path1, &buf1);
        free(path1);

        for (int j = i + 1; j < len; j++) {
            struct stat buf2;
            char *path2 = mx_strnew(mx_strlen(dir_path) + mx_strlen(arr[j]));
            path2 = mx_strcpy(path2, dir_path);
            path2 = mx_strcat(path2, arr[j]);
            lstat(path2, &buf2);
            free(path2);
            if (buf1.st_mtimespec.tv_sec < buf2.st_mtimespec.tv_sec) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            else if (mx_strcmp(arr[i], arr[j]) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    if (flags->using_r)
        mx_reversarr(arr);

    free(dir_path);
}
