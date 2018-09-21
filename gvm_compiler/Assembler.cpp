//
// Created by geno1024 on 2018-09-18.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include "Assembler.h"
#include "../util.h"

char Assembler::registerIndex(char *name)
{
    if (
        name[0] != 'X' ||               // pass if name[0] == 'X'
        name[1] == 0 ||                 // pass if name.length > 1
        name[2] != 0 ||                 // pass if name.length <= 2
        ((name[1] - 1) & 0xf8) != 0x40  // pass if name[1] in ['A'..'H']
        )
        util::force_exit(-2, "register name error");
    else return static_cast<char>(name[1] - 0x31);
}

unsigned long Assembler::toGLong(const char *string)
{
    const char *pos = strchr(string, '@');
    if (pos) // contains '@'
    {
        // left of '@' starts from (string), length (pos - string)
        char *left = strndup(string, pos - string);
        // right of '@' starts from (pos + 1), ends at (string + strlen(string))
        char *right = strndup(pos + 1, string + strlen(string) - pos);
        return strtoul(left, nullptr, static_cast<int>(strtol(right, nullptr, 10)));
    }
    else
        // use decimal
        return strtoul(string, nullptr, 10);
}

const char *Assembler::assembleSingleLine(const char *line)
{
    // pre process
    // trim left spaces
    char *trimL = const_cast<char *>(line);
    while (isspace(*trimL)) trimL++;
    // trim right comments
    char trimR[strpbrk(trimL, "//") - trimL + 1];
    trimR[sizeof(trimR) - 1] = 0;
    strncpy(trimR, trimL, strpbrk(trimL, "//") - trimL);

    // trim right spaces
    printf("%zu\n", strlen(trimR));
    while (isspace(trimR[strlen(trimR) - 1])) trimR[strlen(trimR) - 1] = 0;
    // checkpoint
    for (int i = 0; i < strlen(trimR); ++i) trimR[i] = (char) toupper(trimR[i]);

    // process
    // get operator
    char op[10];
    sscanf(trimR, "%s", op);

    // get operand
    char opr[3][10];


    switch (util::hash(op))
    {
        case util::hash("NOP"):
            return "0000";
        case util::hash("STOP"):
            return "0001";
        case util::hash("INC"):
        {
            static char output[] = "0100";
            output[4] = registerIndex(op);
            return output;
        }
        default:
            util::force_exit(-1, "invalid op");
    }
}

int main(int argc, char *argv[])
{
    printf("%ld\n", Assembler().toGLong("1abc@15"));
    printf("%s", Assembler().assembleSingleLine("   inc ax  // "));
}
