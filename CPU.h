//
// Created by geno1024 on 2018-09-07.
//

#ifndef GVM2_CPU_H
#define GVM2_CPU_H


#include "Motherboard.h"

class CPU
{
public:
    explicit CPU(bool debug = false);
    const unsigned int major = 0;
    const unsigned int minor = 1;

    Motherboard *motherboard = nullptr;

    const unsigned long OF = 1L << 3;
    const unsigned long CF = 1L << 2;
    const unsigned long ZF = 1L << 1;
    const unsigned long PF = 1L << 0;

    void run(unsigned long ip);

    void dump();

private:
    bool debug;
    unsigned long XA;
    unsigned long XB;
    unsigned long XC;
    unsigned long XD;
    unsigned long XE;
    unsigned long XF;
    unsigned long XG;
    unsigned long XH;

    unsigned long IP;
    
    unsigned long FLAGS;

};


#endif //GVM2_CPU_H
