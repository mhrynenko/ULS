#include "../inc/uls.h"

static char **mx_exclude_hidden(char **arr, t_flags *flags) {
    char **res = NULL;
    char *str = NULL;
    int len = 0;
    for (; arr[len] != NULL; len++);

    int i = 0;
    if (flags->using_A) i = 2;
    for (; i < len; i++) {
        if (arr[i][0] == '.' && !flags->using_a && !flags->using_A)
            continue;
        str = mx_strjoin(str, arr[i]);
        str = mx_strjoin(str, " ");
    }

    res = mx_strsplit(str, ' ');
    free(str);
    mx_del_strarr(&arr);
    return res;
}

void mx_dirs_output(char **elements, int n, struct winsize max, t_flags *flags) {
    DIR* dir = NULL;
    struct dirent *sd = NULL;
    char *str;
    for (int i = 0; elements[i] != NULL; i++) {
        if (n > 1) {
            mx_printstr(elements[i]);
            mx_printstr(":\n");
            dir = opendir(elements[i]);
        }
        else
	    	dir = opendir(elements[i]);
	    
	    if (dir == NULL) {
			mx_printerr("uls");
			exit(EXIT_FAILURE);
	    }
	    
	    str = NULL;
	    while ((sd = readdir(dir)) != NULL) {
			str = mx_strjoin(str, sd->d_name);
			str = mx_strjoin(str, " ");
	    }
	    
	    char **files = NULL;
	    files = mx_strsplit(str, ' ');

		if (!flags->using_f)
			mx_sort_string_array(files, flags);
		if ((!flags->using_a && flags->using_A) || (!flags->using_a && !flags->using_A))
	    	files = mx_exclude_hidden(files, flags);
	    free(str);
		
		if (!flags->using_f) {
			if (flags->using_t)
				mx_tsort(files, mx_strjoin(elements[i], "/"), flags);
		}

	    if (files != NULL) {
			if (flags->using_m) {
				mx_mprint(files, &max, mx_strjoin(elements[i], "/"), flags);
			}
			else if(flags->using_C || flags->using_x || flags->using_i) {
	        	mx_uls_print(files, &max, mx_strjoin(elements[i], "/"), flags);
			}
			else {
				mx_uls_long_print(files, mx_strjoin(elements[i], "/"), flags, true);
			}

	        mx_del_strarr(&files);
	    }
	    closedir(dir);

	    if (n > 1 && elements[i + 1] != NULL)
	        mx_printchar('\n');
    }
}

