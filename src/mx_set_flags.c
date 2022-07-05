#include "../inc/uls.h"

void mx_set_flags(t_flags *flags) {
    flags->using_1 = 0;
    flags->using_A = 0;
    flags->using_a = 0;
    flags->using_C = 1;
    flags->using_F = 0;
    flags->using_f = 0;
    flags->using_G = 0;
    flags->using_i = 0;
    flags->using_l = 0;
    flags->using_m = 0;
    flags->using_o = 0;
    flags->using_p = 0;
    flags->using_r = 0;
    flags->using_s = 0;
    flags->using_T = 0;
    flags->using_t = 0;
}

