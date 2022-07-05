#include "../inc/uls.h"

char *mx_get_mods(struct stat *buf, char *path) {
    char *result = mx_strnew(10);
    if (buf->st_mode & S_IRUSR)
        mx_strcat(result, "r");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IWUSR)
        mx_strcat(result, "w");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IXUSR)
        mx_strcat(result, "x");
    else
        mx_strcat(result, "-");

    if (buf->st_mode & S_IRGRP)
        mx_strcat(result, "r");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IWGRP)
        mx_strcat(result, "w");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IXGRP)
        mx_strcat(result, "x");
    else
        mx_strcat(result, "-");

    if (buf->st_mode & S_IROTH)
        mx_strcat(result, "r");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IWOTH)
        mx_strcat(result, "w");
    else
        mx_strcat(result, "-");
    if (buf->st_mode & S_IXOTH)
        mx_strcat(result, "x");
    else
        mx_strcat(result, "-");

    acl_t tmp;

    if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
        mx_strcat(result, "@");
    else if ((tmp = acl_get_file(path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        mx_strcat(result, "+");
    }
    else {
        mx_strcat(result, " ");
    }
    return result;
}
