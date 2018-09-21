#include <iostream>
#include <cstring>
#include "gvm_machine/Memory.h"
#include "gvm_machine/CPU.h"
#include "util.h"
#include "gvm_machine/Motherboard.h"

int main()
{
    static auto memory = Memory(2048);
    memory.write8(0, 0x4041424344454647);
    memory.write8(8, 0x48494A4B4C4D4E4F);
//    memory.dump(1, 32);
    static auto cpu = CPU();
//    cpu.dump();

    static auto motherboard = Motherboard();
    motherboard.cpu = &cpu;
    motherboard.memory = &memory;

    printf("%d\n", util::parity(2));
    return 0;
}