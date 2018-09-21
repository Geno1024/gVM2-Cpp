//
// Created by geno1024 on 2018-09-18.
//

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "util.h"

char util::alloc[64] = {48};

char *util::binary(unsigned long l)
{
    for (int i = 0; i < 64; i++)
        alloc[63 - i] = static_cast<char>((l >> i & 1) + 0x30);
    return alloc;
}

char util::force_exit(int status, const char *message)
{
    fprintf(stderr, "%s", message);
    exit(status);
}

bool util::parity(unsigned long l)
{
    auto y = l ^ l >> 1;
    y = y ^ y >> 2;
    y = y ^ y >> 4;
    y = y ^ y >> 8;
    y = y ^ y >> 16;
    return static_cast<bool>((y ^ y >> 32) & 1);
}

char *util::trim(char *string)
{
    // trim left spaces
    while (isspace(*string)) string++;

    // trim right spaces
    size_t right = strlen(string);
    while (isspace(string[right - 1])) right--;
    return strndup(string, right);
}
