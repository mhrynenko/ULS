#ifndef ULS_H
#define ULS_H

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include "../libmx/inc/libmx.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KBRN  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"

typedef struct s_flags
{
    int using_1;
    int using_A;
    int using_a;
    int using_C;
    int using_F;
    int using_f;
    int using_G;
    int using_i;
    int using_l;
    int using_m;
    int using_o;
    int using_p;
    int using_r;
    int using_s;
    int using_T;
    int using_t;
    int using_x;
}              t_flags;

void mx_set_flags(t_flags *flags);
char **mx_get_data(int argc, char **argv);
void mx_elems_by_type(char **elements, int n, char ***directories, char ***files, int *err_retrn);
void mx_check_flags(char c, t_flags *flags);
char *mx_get_mods(struct stat *buf, char *path);
void mx_uls(char **elements, t_flags *flags, int *err_retrn);
void mx_dirs_output(char **elements, int n, struct winsize max, t_flags *flags);
void mx_uls_print(char **files, struct winsize *max, char *dir_path, t_flags *flags);
void mx_uls_long_print(char **files, char *dir_path, t_flags *flags, bool is_dir);
void mx_reversarr(char **arr);
void mx_sort_string_array(char **arr, t_flags *flags);
void mx_tsort(char **arr, char *dir_path, t_flags *flags);
void mx_print_name(char *name, struct stat *buf, t_flags *flags);
void mx_mprint(char **elements, struct winsize *max, char *dir_path, t_flags *flags);


#endif
