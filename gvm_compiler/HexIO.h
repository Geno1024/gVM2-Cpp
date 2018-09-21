//
// Created by geno1024 on 2018-09-21.
//

#ifndef GVM2_HEXIO_H
#define GVM2_HEXIO_H


#include <cstdio>

class HexIO
{
public:
    static void hex2bin(const char *input, const char *output);
    static void bin2hex(const char *input, const char *output);
};


#endif //GVM2_HEXIO_H
