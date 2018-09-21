//
// Created by geno1024 on 2018-09-07.
//

#ifndef GVM2_CPU_H
#define GVM2_CPU_H


#include "Motherboard.h"

class CPU
{
public:
    // CPU "Constructor".
    explicit CPU(bool debug = false);

    // Major version number.
    const unsigned int major = 0;

    // Minor version number.
    const unsigned int minor = 1;

    // Pointer for the assembled motherboard.
    Motherboard *motherboard = nullptr;

    // Overflow Flag
    const unsigned long OF = 1L << 3;
    // Carry Flag
    const unsigned long CF = 1L << 2;
    // Zero Flag
    const unsigned long ZF = 1L << 1;
    // Parity Flag
    const unsigned long PF = 1L << 0;

    /**
     * Run CPU or VM from the current IP.
     */
    void run();

    /**
     * Run CPU or VM from the given IP.
     * @param ip
     */
    void run(unsigned long ip);

    // Dump current CPU status.
    void dump();

private:
    bool debug;

    // Eight common registers.
    unsigned long XA;
    unsigned long XB;
    unsigned long XC;
    unsigned long XD;
    unsigned long XE;
    unsigned long XF;
    unsigned long XG;
    unsigned long XH;

    // Instruction Pointer register.
    unsigned long IP;

    // Flags register.
    unsigned long FLAGS;

};


#endif //GVM2_CPU_H
