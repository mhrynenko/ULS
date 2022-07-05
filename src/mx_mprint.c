#include "../inc/uls.h"

void mx_mprint(char **elements, struct winsize *max, char *dir_path, t_flags *flags) {
    int cur_len = 0;
    struct stat buf;
    for (int i = 0; elements[i] != NULL; ++i) {
        if (cur_len + mx_strlen(elements[i]) >= max->ws_col - 1) {
            mx_printchar('\n');
            cur_len = 0;
        }
        char *path = mx_strjoin(dir_path, elements[i]);
        lstat(path, &buf);
        free(path);
        mx_print_name(elements[i], &buf, flags);
        cur_len += (mx_strlen(elements[i]) + 2);
        if (elements[i + 1] != NULL)
            mx_printstr(", ");
        else
            mx_printchar('\n');
    }
    free(dir_path);
}
