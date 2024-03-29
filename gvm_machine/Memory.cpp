//
// Created by geno1024 on 2018-09-06.
//

#include <cstdio>
#include <cmath>
#include "Memory.h"

Memory::Memory(long size)
{
    this->size = size;
    this->memory = new unsigned char[size];
}

unsigned char Memory::read1(long pos)
{
    return memory[pos];
}

void Memory::write1(long pos, unsigned char data)
{
    memory[pos] = data;
}

unsigned int Memory::read4(long pos)
{
    return
    (memory[pos    ] << 24) +
    (memory[pos + 1] << 16) +
    (memory[pos + 2] <<  8) +
     memory[pos + 3];
}

void Memory::write4(long pos, unsigned int data)
{
    memory[pos    ] = static_cast<unsigned char>(data >> 24);
    memory[pos + 1] = static_cast<unsigned char>(data >> 16);
    memory[pos + 2] = static_cast<unsigned char>(data >>  8);
    memory[pos + 3] = static_cast<unsigned char>(data      );
}

unsigned long Memory::read8(long pos)
{
    return
    (static_cast<unsigned long>(memory[pos    ]) << 56) +
    (static_cast<unsigned long>(memory[pos + 1]) << 48) +
    (static_cast<unsigned long>(memory[pos + 2]) << 40) +
    (static_cast<unsigned long>(memory[pos + 3]) << 32) +
    (static_cast<unsigned long>(memory[pos + 4]) << 24) +
    (static_cast<unsigned long>(memory[pos + 5]) << 16) +
    (static_cast<unsigned long>(memory[pos + 6]) <<  8) +
     static_cast<unsigned long>(memory[pos + 7]);
}

void Memory::write8(long pos, unsigned long data)
{
    memory[pos    ] = static_cast<unsigned char>(data >> 56);
    memory[pos + 1] = static_cast<unsigned char>(data >> 48);
    memory[pos + 2] = static_cast<unsigned char>(data >> 40);
    memory[pos + 3] = static_cast<unsigned char>(data >> 32);
    memory[pos + 4] = static_cast<unsigned char>(data >> 24);
    memory[pos + 5] = static_cast<unsigned char>(data >> 16);
    memory[pos + 6] = static_cast<unsigned char>(data >>  8);
    memory[pos + 7] = static_cast<unsigned char>(data      );
}

void Memory::dump(unsigned long start, unsigned long end)
{
    // zeroth line
    printf("----------------:  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

    // first line
    unsigned long startLine = start & 0x7ffffffffffffff0;
    unsigned long endLine = end & 0x7ffffffffffffff0;

    printf("%016lx:", startLine);
    for (unsigned long i = startLine; i < start; i++) printf("   ");

    for (unsigned long i = start; i < fmin(startLine + 16, end + 1); i++) printf(" %02x", read1(i));

    // last line, if exists
    if (startLine - endLine)
    {
        for (unsigned long i = end; i < startLine + 16; i++) printf(" %02x", read1(i));
        for (unsigned long i = startLine + 16; i < endLine; i++)
        {
            if (!(i & 15)) printf("\n%016lx:", i);
            printf(" %02x", read1(i));
        }
        printf("\n%016lx:", endLine);
        for (unsigned long i = endLine; i <= end; i++) printf(" %02x", read1(i));
    }
    printf("\n");
}
