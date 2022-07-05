#include "../inc/uls.h"

void mx_uls(char **elements, t_flags *flags, int *err_retrn) {
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);
    char **directories = NULL;
    char **files = NULL;
    
    int n = 0;
    if (elements != NULL)
        for (; elements[n] != NULL; n++);
    else {
        elements = (char **)malloc(1);
        n = 1;
        elements[0] = mx_strdup(".");
        elements[1] = NULL;
    }
    mx_elems_by_type(elements, n, &directories, &files, err_retrn);

    if (files != NULL) {
        if (flags->using_m) {
            mx_mprint(files, &max, NULL, flags);
        }
        else if (flags->using_C || flags->using_x || flags->using_i) {
            mx_uls_print(files, &max, NULL, flags);
        }
        else if (flags->using_l) {
            mx_uls_long_print(files, NULL, flags, false);
        }
        if (directories != NULL)
            mx_printchar('\n');
        mx_del_strarr(&files);
    }
    if (directories != NULL) {
        mx_dirs_output(directories, n, max, flags);
        mx_del_strarr(&directories);
    }
    free(flags);
}

