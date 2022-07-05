#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	int sum = mx_strlen(replace) - mx_strlen(sub);
	int len = mx_strlen(str) + mx_count_substr(str, sub) * sum;
	char *memory = mx_strnew(len);
    bool check_worked = false;

	if (!str || !sub || !replace || mx_strlen(str) <= mx_strlen(sub)) {
		return NULL;
    }

	for (int i = 0; i < len; i++, str++) {
        check_worked = false;
        if (mx_strncmp((char *)str, (char *)sub, mx_strlen(sub)) == 0) {
            str += mx_strlen(sub);

            for (int j = 0; j < mx_strlen(replace); i++, j++) {
                memory[i] = replace[j];
            }
            check_worked = true;
        }
        memory[i] = *str;
        if (check_worked) {
            str--;
            i--;
        }
    }

    return memory;
}

