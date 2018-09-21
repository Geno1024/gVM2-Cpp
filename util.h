//
// Created by geno1024 on 2018-09-18.
//

#ifndef GVM2_UTIL_H
#define GVM2_UTIL_H


#include <cstring>

class util
{
public:
    // Converts from unsigned long to binary string.
    static char *binary(unsigned long l);

    // Unconditionally force VM to exit. Emergency situation?
    static void force_exit(int status, const char *message, ...) __attribute__ ((__noreturn__));

    // Conditionally force VM to exit.
    static void force_exit_if(bool condition, int status, const char *message, ...);

    // Check bitwise parity of input.
    static bool parity(unsigned long l);

    // Simple string hash for switch.
    constexpr static long hash(const char *string)
    {
        long result = 0;
        while (*string) result = (result << 8) + *string++;
        return result;
    };

    // Trim string.
    static char *trim(char *string);

private:
    static char alloc[64];
};

#endif //GVM2_UTIL_H
