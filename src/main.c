#include "../inc/uls.h"

static void mx_get_flags(int argc, char **argv, t_flags *flags) {
    int j = 0;
    for (int i = 1; i < argc; i++) {
        j = 1;
        if (argv[i][0] == '-') {
            while (argv[i][j] != '\0') {
                mx_check_flags(argv[i][j], flags);
                j++;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
    mx_set_flags(flags);
    
    mx_get_flags(argc, argv, flags);
    char **elements = mx_get_data(argc, argv);

    int err_retrn = 0;

    if (elements != NULL) {
        if (!flags->using_f) {
            mx_sort_string_array(elements, flags);
        
            if (flags->using_t)
                mx_tsort(elements, mx_strjoin(".", "/"), flags);
        }
    }

    mx_uls(elements, flags, &err_retrn);
    
    return err_retrn;
}

