//
// Created by geno1024 on 2018-09-07.
//

#include <cstdio>
#include "CPU.h"
#include "util.h"

CPU::CPU(bool debug)
{
    this->debug = debug;
    XA = 0; XB = 0; XC = 0; XD = 0;
    XE = 0; XF = 0; XG = 0; XH = 0;

    IP = 0;
    FLAGS = 0;
}

void CPU::dump()
{
    printf("XA=%016lx XB=%016lx XC=%016lx XD=%016lx\n", XA, XB, XC, XD);
    printf("XE=%016lx XF=%016lx XG=%016lx XH=%016lx\n", XE, XF, XG, XH);
    printf("IP=%016lx\n", IP);
    printf("FLAGS=%s\n", util::printf_binary(FLAGS));
}

void CPU::run(unsigned long ip)
{
    IP = ip;
    while (true)
    {
        motherboard->memory->dump();
    }
}

