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

    // read 1 byte
    unsigned char read1(long pos);
    // write 1 byte
    void write1(long pos, unsigned char data);
    // read 4 bytes
    unsigned int read4(long pos);
    // write 4 bytes
    void write4(long pos, unsigned int data);
    // read 8 bytes
    unsigned long read8(long pos);
    // write 8 bytes
    void write8(long pos, unsigned long data);

    // dump a range of memory
    void dump(unsigned long start, unsigned long end);

private:
    // size of the memory stick
    long size;

    // the memory stick
    unsigned char *memory;
};


#endif //GVM2_MEMORY_H
