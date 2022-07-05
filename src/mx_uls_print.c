#include "../inc/uls.h"

int max_len_files(char **files) {
    int max = 0;
    int temp = 0;

    for (int i = 0; files[i]; i++) {
        temp = mx_strlen(files[i]);
        if (temp > max)
            max = temp;
    }
    if (max % 8 == 0)
        max += 8;
    else
        max = 8 - (max % 8) + max;
    return max;
}

void mx_print_tab(int len, int maxlen) {
    int count = 0;
    int p;

    p = maxlen - len;
    if (p % 8 != 0)
        count = (p / 8) + 1;
    else
        count = p / 8;
    for (int i = 0; i < count; i++)
        mx_printchar('\t');
}

static void printcols(char **files, int rows, int num, int maxlen, t_flags *flags, char *dir_path) {
	struct stat buf;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
			char *path = mx_strjoin(dir_path, files[i + j]);
			lstat(path, &buf);
			mx_print_name(files[i + j], &buf, flags);
            if (files[i + j + 1] && (i + j + rows < num))
                mx_print_tab(mx_strlen(files[i + j]), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

static void print_files(char **files, int maxlen, int wincol, t_flags *flags, char *dir_path) {
    int rows;
	struct stat buf;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    for(;files[num]; num++) {
    }
    int max_file_inode_len = 1;
	for (int i = 0; i < num; ++i) {
        if (flags->using_i) {
            char *new_file_inode_str = mx_itoa(buf.st_ino);
            if (max_file_inode_len < mx_strlen(new_file_inode_str))
                max_file_inode_len = mx_strlen(new_file_inode_str);
            free(new_file_inode_str);
        }
    }
    if (maxlen * cols > wincol && cols != 1)
        cols--;
    if (num * maxlen > wincol) {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows += 1;
        printcols(files, rows, num, maxlen, flags, dir_path);
    } else
        for (int i = 0; files[i]; i++) {
			char *path = mx_strjoin(dir_path, files[i]);
			lstat(path, &buf);
			if (flags->using_i) {
            	char *file_inode_str = mx_itoa(buf.st_ino);
            	int file_inode_len = mx_strlen(file_inode_str);
            	free(file_inode_str);
            	for (int k = 0; k < max_file_inode_len - file_inode_len; k++)
                	mx_printchar(' ');
            	mx_printint(buf.st_ino);
            	mx_printchar(' ');
        	}
			mx_print_name(files[i], &buf, flags);
            if (files[i + 1]) 
                mx_print_tab(mx_strlen(files[i]), maxlen);
        }
        mx_printchar('\n');
}

void mx_uls_print(char **files, struct winsize *win2, char *dir_path, t_flags *flags) {
    int maxlen;
    struct winsize win = *win2;
    int istty = isatty(1);
    if (!files)
        return;
    maxlen = max_len_files(files);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, win);
    if (!istty || flags->using_1) {
		mx_print_strarr(files, "\n");
		return;
    }
    if (isatty(1)) {
        print_files(files, maxlen, win.ws_col, flags, dir_path);
    }
}


