//
// Created by geno1024 on 2018-09-18.
//

#ifndef GVM2_UTIL_H
#define GVM2_UTIL_H


class util
{
public:
    // Converts from unsigned long to binary string.
    static char *binary(unsigned long l);

    // Force VM to exit. Emergency situation?
    static char force_exit(int status, const char *message) __attribute__ ((__noreturn__));

    // Check bitwise parity of input.
    static bool parity(unsigned long l);

private:
    static char alloc[64];
};

#endif //GVM2_UTIL_H
