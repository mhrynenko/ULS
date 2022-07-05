#include "../inc/uls.h"

static void mx_set_color(struct stat *buf) {
    if (S_ISDIR(buf->st_mode))
        mx_printstr(KBLU);
    else if (S_ISFIFO(buf->st_mode))
        mx_printstr(KBRN);
    else if (S_ISLNK(buf->st_mode))
        mx_printstr(KMAG);
    else if (S_ISBLK(buf->st_mode))
        mx_printstr(KBLU);
    else if (S_ISCHR(buf->st_mode))
        mx_printstr(KBLU);
    else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
        mx_printstr(KGRN);
    else if (buf->st_mode & S_IEXEC)
        mx_printstr(KRED);
    else if (S_ISREG(buf->st_mode))
        mx_printstr(KNRM);
}

void mx_print_name(char *name, struct stat *buf, t_flags *flags) {
    int istty = isatty(1);
    if (flags->using_G && istty)
        mx_set_color(buf);
    mx_printstr(name);
    if (istty)
        mx_printstr(KNRM);
    if (S_ISDIR(buf->st_mode) && (flags->using_p || flags->using_F))
        mx_printchar('/');
    else if (S_ISFIFO(buf->st_mode) && flags->using_F)
        mx_printchar('|');
    else if (S_ISLNK(buf->st_mode) && flags->using_F)
        mx_printchar('@');
    else if ((buf->st_mode & S_IEXEC) && flags->using_F)
        mx_printchar('*');
    else if (((buf->st_mode & S_IFMT) == S_IFSOCK) && flags->using_F)
        mx_printchar('=');
}
