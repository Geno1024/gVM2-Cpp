//
// Created by geno1024 on 2018-09-18.
//

#include "Motherboard.h"
#include "CPU.h"
#include "Memory.h"

Motherboard::Motherboard()
{
    cpu = nullptr;
    memory = nullptr;
}

void Motherboard::setCPU(CPU *_cpu)
{
    cpu = _cpu;
    cpu->motherboard = this;
}

void Motherboard::setMemory(Memory *_memory)
{
    memory = _memory;
    memory->motherboard = this;
}
