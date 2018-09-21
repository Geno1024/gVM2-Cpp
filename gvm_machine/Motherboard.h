//
// Created by geno1024 on 2018-09-18.
//

#ifndef GVM2_MOTHERBOARD_H
#define GVM2_MOTHERBOARD_H

class CPU;
class Memory;

class Motherboard
{
public:
    explicit Motherboard();

    CPU *cpu;
    Memory *memory;

    void setCPU(CPU *_cpu);
    void setMemory(Memory *_memory);
};


#endif //GVM2_MOTHERBOARD_H
