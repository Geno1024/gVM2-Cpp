//
// Created by geno1024 on 2018-09-07.
//

#include <cstdio>
#include "CPU.h"
#include "../util.h"
#include "Memory.h"

void todo() { util::force_exit(-1, "not implemented"); }

CPU::CPU(bool debug)
{
    this->debug = debug;
    // initialize registers
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
    printf("FLAGS=%s\n", util::binary(FLAGS));
}

void CPU::run()
{
    run(IP);
}

void CPU::run(unsigned long ip)
{
    IP = ip;
    auto memory = motherboard->memory;
    while (true)
    {
        // major operand
        unsigned char left = memory->read1(IP);
        // minor operand
        unsigned char right = memory->read1(IP + 1);
        switch (left)
        {
            case 0x00: // execution control
                switch (right)
                {
                    case 0x00: IP += 2; break;
                    case 0x01: return;
                    default: todo();
                }
            case 0x01: // addition and subtraction
                switch (right)
                {
                    case 0x00: XA++; IP += 2; break;
                    case 0x01: XB++; IP += 2; break;
                    case 0x02: XC++; IP += 2; break;
                    case 0x03: XD++; IP += 2; break;
                    case 0x04: XE++; IP += 2; break;
                    case 0x05: XF++; IP += 2; break;
                    case 0x06: XG++; IP += 2; break;
                    case 0x07: XH++; IP += 2; break;

                    case 0x40: XA += memory->read8(IP + 2); IP += 10; break;
                    case 0x41: XB += memory->read8(IP + 2); IP += 10; break;
                    case 0x42: XC += memory->read8(IP + 2); IP += 10; break;
                    case 0x43: XD += memory->read8(IP + 2); IP += 10; break;
                    case 0x44: XE += memory->read8(IP + 2); IP += 10; break;
                    case 0x45: XF += memory->read8(IP + 2); IP += 10; break;
                    case 0x46: XG += memory->read8(IP + 2); IP += 10; break;
                    case 0x47: XH += memory->read8(IP + 2); IP += 10; break;

                    case 0x50: XA += memory->read4(IP + 2); IP += 6; break;
                    case 0x51: XB += memory->read4(IP + 2); IP += 6; break;
                    case 0x52: XC += memory->read4(IP + 2); IP += 6; break;
                    case 0x53: XD += memory->read4(IP + 2); IP += 6; break;
                    case 0x54: XE += memory->read4(IP + 2); IP += 6; break;
                    case 0x55: XF += memory->read4(IP + 2); IP += 6; break;
                    case 0x56: XG += memory->read4(IP + 2); IP += 6; break;
                    case 0x57: XH += memory->read4(IP + 2); IP += 6; break;

                    case 0x70: XA += memory->read1(IP + 2); IP += 3; break;
                    case 0x71: XB += memory->read1(IP + 2); IP += 3; break;
                    case 0x72: XC += memory->read1(IP + 2); IP += 3; break;
                    case 0x73: XD += memory->read1(IP + 2); IP += 3; break;
                    case 0x74: XE += memory->read1(IP + 2); IP += 3; break;
                    case 0x75: XF += memory->read1(IP + 2); IP += 3; break;
                    case 0x76: XG += memory->read1(IP + 2); IP += 3; break;
                    case 0x77: XH += memory->read1(IP + 2); IP += 3; break;

                    case 0x80: XA--; IP += 2; break;
                    case 0x81: XB--; IP += 2; break;
                    case 0x82: XC--; IP += 2; break;
                    case 0x83: XD--; IP += 2; break;
                    case 0x84: XE--; IP += 2; break;
                    case 0x85: XF--; IP += 2; break;
                    case 0x86: XG--; IP += 2; break;
                    case 0x87: XH--; IP += 2; break;

                    case 0xC0: XA -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC1: XB -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC2: XC -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC3: XD -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC4: XE -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC5: XF -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC6: XG -= memory->read8(IP + 2); IP += 10; break;
                    case 0xC7: XH -= memory->read8(IP + 2); IP += 10; break;

                    case 0xD0: XA -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD1: XB -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD2: XC -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD3: XD -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD4: XE -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD5: XF -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD6: XG -= memory->read4(IP + 2); IP += 6; break;
                    case 0xD7: XH -= memory->read4(IP + 2); IP += 6; break;

                    case 0xF0: XA -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF1: XB -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF2: XC -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF3: XD -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF4: XE -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF5: XF -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF6: XG -= memory->read1(IP + 2); IP += 3; break;
                    case 0xF7: XH -= memory->read1(IP + 2); IP += 3; break;

                    default: todo();
                }
                break;
            case 0x02: // direct assignment
                switch (right)
                {
                    case 0x00: XA = memory->read8(IP + 2); IP += 10; break;
                    case 0x01: XB = memory->read8(IP + 2); IP += 10; break;
                    case 0x02: XC = memory->read8(IP + 2); IP += 10; break;
                    case 0x03: XD = memory->read8(IP + 2); IP += 10; break;
                    case 0x04: XE = memory->read8(IP + 2); IP += 10; break;
                    case 0x05: XF = memory->read8(IP + 2); IP += 10; break;
                    case 0x06: XG = memory->read8(IP + 2); IP += 10; break;
                    case 0x07: XH = memory->read8(IP + 2); IP += 10; break;

                    case 0x10: XA = memory->read4(IP + 2); IP += 6; break;
                    case 0x11: XB = memory->read4(IP + 2); IP += 6; break;
                    case 0x12: XC = memory->read4(IP + 2); IP += 6; break;
                    case 0x13: XD = memory->read4(IP + 2); IP += 6; break;
                    case 0x14: XE = memory->read4(IP + 2); IP += 6; break;
                    case 0x15: XF = memory->read4(IP + 2); IP += 6; break;
                    case 0x16: XG = memory->read4(IP + 2); IP += 6; break;
                    case 0x17: XH = memory->read4(IP + 2); IP += 6; break;

                    case 0x30: XA = memory->read1(IP + 2); IP += 3; break;
                    case 0x31: XB = memory->read1(IP + 2); IP += 3; break;
                    case 0x32: XC = memory->read1(IP + 2); IP += 3; break;
                    case 0x33: XD = memory->read1(IP + 2); IP += 3; break;
                    case 0x34: XE = memory->read1(IP + 2); IP += 3; break;
                    case 0x35: XF = memory->read1(IP + 2); IP += 3; break;
                    case 0x36: XG = memory->read1(IP + 2); IP += 3; break;
                    case 0x37: XH = memory->read1(IP + 2); IP += 3; break;

                    case 0x50: XA = (XA & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x51: XB = (XB & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x52: XC = (XC & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x53: XD = (XD & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x54: XE = (XE & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x55: XF = (XF & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x56: XG = (XG & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;
                    case 0x57: XH = (XH & 0x7fffffff00000000L) + memory->read4(IP + 2); IP += 6; break;

                    case 0x70: XA = (XA & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x71: XB = (XB & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x72: XC = (XC & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x73: XD = (XD & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x74: XE = (XE & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x75: XF = (XF & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x76: XG = (XG & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;
                    case 0x77: XH = (XH & 0x7fffffffffff0000L) + memory->read1(IP + 2); IP += 3; break;

                    default: todo();
                }
                break;
            case 0x03: // indirect multiplication and division
            unsigned long op, h1, l1, h2, l2, l, m, h;
                switch (right)
                {
                    case 0x00:
                        op = memory->read8(IP + 2);

                        h1 = XA >> 32, l1 = XA & 0xffffffff;
                        h2 = op >> 32, l2 = op & 0xffffffff;

                        h = h1 * h2, m = l1 * h2 + l2 * h1, l = l1 * l2;

                        XE = h + (m >> 32);
                        XA = l + ((m & 0xffffffffL) << 32);

                        IP += 10;
                        break;
                    case 0x01:
                        op = memory->read8(IP + 2);

                        h1 = XB >> 32, l1 = XB & 0xffffffff;
                        h2 = op >> 32, l2 = op & 0xffffffff;

                        h = h1 * h2, m = l1 * h2 + l2 * h1, l = l1 * l2;

                        XF = h + (m >> 32);
                        XB = l + ((m & 0xffffffffL) << 32);

                        IP += 10;
                        break;
                    case 0x02:
                        op = memory->read8(IP + 2);

                        h1 = XC >> 32, l1 = XC & 0xffffffff;
                        h2 = op >> 32, l2 = op & 0xffffffff;

                        h = h1 * h2, m = l1 * h2 + l2 * h1, l = l1 * l2;

                        XG = h + (m >> 32);
                        XC = l + ((m & 0xffffffffL) << 32);

                        IP += 10;
                        break;
                    case 0x04:
                        op = memory->read8(IP + 2);

                        h1 = XD >> 32, l1 = XD & 0xffffffff;
                        h2 = op >> 32, l2 = op & 0xffffffff;

                        h = h1 * h2, m = l1 * h2 + l2 * h1, l = l1 * l2;

                        XH = h + (m >> 32);
                        XD = l + ((m & 0xffffffffL) << 32);

                        IP += 10;
                        break;
                }
                break;
            default: todo();
        }
    }
}
