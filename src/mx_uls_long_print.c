#include "../inc/uls.h"

static char *mx_get_mtime(char *ntime) {
    char *res = mx_strnew(12);
    res = mx_strncpy(res, ntime + 4, 12);
    time_t seconds = time(NULL);
    char *cur_time = ctime(&seconds);
    if (mx_atoi(ntime + 20) < mx_atoi(cur_time + 20)) {
        mx_strncpy(res + 7, ntime + 19, 5);
    }
    return res;
}

static int mx_find_max_size(char **files, int *links_max_amount_len, char *dir_path) {
    struct stat buf;
    int max_size = 0;
    int max_links_len = 0;
    for (int i = 0; files[i] != NULL; i++) {
        char *path = mx_strjoin(dir_path, files[i]);
        lstat(path, &buf);
        free(path);
        if (buf.st_size > max_size) 
            max_size = buf.st_size;
        if (buf.st_nlink > max_links_len)
            max_links_len = buf.st_nlink;
    }
    *links_max_amount_len = mx_strlen(mx_itoa(max_links_len));
    return mx_strlen(mx_itoa(max_size));
}

void mx_uls_long_print(char **files, char *dir_path, t_flags *flags, bool is_dir) {
    int len = 0;
    for (; files[len] != NULL; ++len);

    struct stat buf;
    char *ntime = mx_strnew(100);
    int links_amount_max_len = 0;
    int max_size_len = mx_find_max_size(files, &links_amount_max_len, dir_path);
    int max_block_size_len = 1;
    int max_file_inode_len = 1;
    int total = 0;
    for (int i = 0; i < len; ++i) {
        char *path = mx_strjoin(dir_path, files[i]);
        stat(path, &buf);
        total += buf.st_blocks;
        if (flags->using_s) {
            char *new_block_size = mx_itoa(buf.st_blocks);
            if (max_block_size_len < mx_strlen(new_block_size))
                max_block_size_len = mx_strlen(new_block_size);
            free(new_block_size);
        }
        if (flags->using_i) {
            char *new_file_inode_str = mx_itoa(buf.st_ino);
            if (max_file_inode_len < mx_strlen(new_file_inode_str))
                max_file_inode_len = mx_strlen(new_file_inode_str);
            free(new_file_inode_str);
        }
    }
    
    if (is_dir) {
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
    }

    for (int i = 0; i < len; ++i) {
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

        if (flags->using_s) {
            char *block_size = mx_itoa(buf.st_blocks);
            int block_size_int = mx_strlen(block_size);
            free(block_size);
            for (int k = 0; k < max_block_size_len - block_size_int; k++)
                mx_printchar(' ');
            mx_printint(buf.st_blocks);
            mx_printchar(' ');
        }

        if (S_ISDIR(buf.st_mode))
            mx_printchar('d');
        if (S_ISREG(buf.st_mode))
            mx_printchar('-');
        if (S_ISFIFO(buf.st_mode))
            mx_printchar('p');
        if (S_ISLNK(buf.st_mode))
            mx_printchar('l');
        if (S_ISBLK(buf.st_mode))
            mx_printchar('b');
        if (S_ISCHR(buf.st_mode))
            mx_printchar('c');
        if ((buf.st_mode & S_IFMT) == S_IFSOCK)
            mx_printchar('s');

        char *permissions = mx_get_mods(&buf, path);
        mx_printstr(permissions);
        free(permissions);
        mx_printchar(' ');

        for (int k = mx_strlen(mx_itoa(buf.st_nlink)); k < links_amount_max_len; ++k)
            mx_printchar(' ');
        mx_printint(buf.st_nlink);
        mx_printchar(' ');

        struct passwd *ubuf = getpwuid(buf.st_uid);
        if (ubuf == NULL) {
            char *mx_err = "uls";
            perror(mx_err);
            free(dir_path);
            exit(EXIT_FAILURE);
        }
        mx_printstr(ubuf->pw_name);
        mx_printstr("  ");

        if (!flags->using_o) {
            struct group *gbuf = getgrgid(buf.st_gid);
            if (gbuf == NULL) {
                mx_printint(buf.st_gid);
            }
            else {
                mx_printstr(gbuf->gr_name);
            }
            
            mx_printstr("  ");
        }
        
        
        for (int k = mx_strlen(mx_itoa(buf.st_size)); k < max_size_len; ++k)
            mx_printchar(' ');
        mx_printint(buf.st_size);
        mx_printchar(' ');

        mx_strcpy(ntime, ctime(&buf.st_mtime));
        if (!flags->using_T) {
            char *mtime = mx_get_mtime(ntime);
            mx_printstr(mtime);
            free(mtime);
        }
        else {
            char *ntime_full = mx_strnew(20);
            ntime_full = mx_strncpy(ntime_full, ntime + 4, 20);
            mx_printstr(ntime_full);
            free(ntime_full);
        }
        mx_printchar(' ');

        mx_print_name(files[i], &buf, flags);
        
        if (S_ISLNK(buf.st_mode)) {
            char link_buf[1024];
            ssize_t len;
            if ((len = readlink(path, link_buf, sizeof(link_buf)-1)) != -1) {
                link_buf[len] = '\0';
                mx_printstr(" -> ");
                mx_printstr(link_buf);
            }
        }
        mx_printchar('\n');
        free(path);
    }
    free(dir_path);
    free(ntime);
}
