#include "../inc/uls.h"

void mx_check_flags(char c, t_flags *flags) {
    switch (c) {
        case '1':
            flags->using_1 = 1;
            flags->using_l = 0;
            break;
        case 'A':
            flags->using_A = 1;
            break;
        case 'a':
            flags->using_A = 0;
            flags->using_a = 1;
            break;
        case 'C':
            flags->using_C = 1;
            flags->using_1 = 0;
            flags->using_l = 0;
            break;
        case 'F':
            flags->using_F = 1;
            break;
        case 'f':
            flags->using_f = 1;
            flags->using_a = 1;
            break;
        case 'G':
            flags->using_G = 1;
            break;
        case 'i':
            flags->using_i = 1;
            flags->using_C = 1;
            flags->using_x = 1;
            flags->using_l = 0;
        case 'l':
            flags->using_l = 1;
            flags->using_1 = 0;
            flags->using_C = 0;
            flags->using_x = 0;
            break;
        case 'm':
            flags->using_m = 1;
            break;
        case 'o':
            flags->using_o = 1;
            flags->using_l = 1;
            flags->using_C = 0;
            flags->using_x = 0;
            flags->using_i = 0;
            break;
        case 'p':
            flags->using_p = 1;
            break;
        case 'r':
            flags->using_r = 1;
            break;
        case 's':
            flags->using_s = 1;
            break;
        case 'T':
            flags->using_T = 1;
            break;
        case 't':
            flags->using_t = 1;
            break;
        case 'x':
            flags->using_x = 1;
            flags->using_C = 0;
            flags->using_1 = 0;
            flags->using_l = 0;
            break;
        default:
                mx_printerr("uls: illegal option -- ");
                mx_printerrchar(c);
                mx_printerr("\n");
                mx_printerr("usage: uls [-aACfFGilmosp1rTtx] [file ...]\n");
                exit(EXIT_FAILURE);
    }
}

