//
// Created by geno1024 on 2018-09-18.
//

#include "util.h"

char util::alloc[64] = {48};

char *util::printf_binary(long l)
{
    for (int i = 0; i < 64; i++)
        alloc[63 - i] = static_cast<char>((l >> i & 1) + 0x30);
    return alloc;
}
