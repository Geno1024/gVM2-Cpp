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

unsigned long Assembler::toGlong(const char *string)
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
    char *ltrim = const_cast<char *>(line);
    while (isspace(*ltrim)) ltrim++;
    // trim right comments
    char rtrim[strpbrk(ltrim, "//") - ltrim];
    strncpy(rtrim, ltrim, strpbrk(ltrim, "//") - ltrim);
    // trim right spaces
    while (isspace(rtrim[strlen(rtrim) - 1])) rtrim[strlen(rtrim) - 1] = 0;
    // checkpoint
    for (int i = 0; i < strlen(rtrim); ++i) rtrim[i] = static_cast<char>(toupper(rtrim[i]));

    // process
    // get operand
    char op[10];
    sscanf(rtrim, "%s", op);
    switch (util::hash(op))
    {
        case (((('N' << 8) + 'O') << 8) + 'P') << 8: return "0000";
    }
    if (strcmp("NOP", op)) return "0000";
    else if (strcmp("STOP", op)) return "0001";
    else if (strcmp("INC", op))
}

int main(int argc, char *argv[])
{
    printf("%ld\n", Assembler().toGlong("1abc@15"));
    Assembler().assembleSingleLine("   a %x   // ");
}
