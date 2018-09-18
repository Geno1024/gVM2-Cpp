//
// Created by geno1024 on 2018-09-06.
//

#ifndef GVM2_MEMORY_H
#define GVM2_MEMORY_H


#include "Motherboard.h"

class Memory
{
public:
    explicit Memory(long size);

    Motherboard *motherboard = nullptr;

    char read1(long pos);
    void write1(long pos, char data);
    int read4(long pos);
    void write4(long pos, int data);
    long read8(long pos);
    void write8(long pos, long data);

    void dump(long start, long end);

private:
    long size;
    char *memory;
};


#endif //GVM2_MEMORY_H
