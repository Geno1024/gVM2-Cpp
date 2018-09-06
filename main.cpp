#include <iostream>
#include "Memory.h"

int main()
{
    auto memory = Memory(2048);
    memory.write8(0, 0x4041424344454647);
    memory.write8(8, 0x48494A4B4C4D4E4F);
    memory.write8(16, 0x5051525354555657);
    memory.write8(24, 0x58595A5B5C5D5E5F);
    memory.dump(1, 32);
    return 0;
}