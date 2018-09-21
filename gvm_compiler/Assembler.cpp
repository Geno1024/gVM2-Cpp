#pragma clang diagnostic ignored "-Wconversion"
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
    else return static_cast<char>(name[1] - 0x11);
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

const char *Assembler::assembleSingleLine(const char *line, int line_no)
{
    // pre process

    char *remove_blank = util::trim(const_cast<char *>(line));
    char *remove_comment = strndup(remove_blank, strpbrk(remove_blank, "//") - remove_blank);
    char *upper = remove_comment;
    while (*upper) { *upper = static_cast<char>(toupper(*upper)); upper++; }
    char *instruction = util::trim(remove_comment);

    // get op
    char *wind = instruction;
    char *op = strndup(wind, strchr(wind, ' ') - wind);
    wind = strpbrk(wind, op) + strlen(op);

    char *opr[4] = { nullptr };
    int oprc = 0;

    while (strchr(wind, ','))
    {
        opr[oprc] = util::trim(strndup(wind, strchr(wind, ',') - wind));
        wind = strchr(strpbrk(wind, opr[oprc]) + strlen(opr[oprc]), ',') + 1;
        oprc++;
    }
    opr[oprc++] = util::trim(wind);

    printf("%s|%s|%s|%s|%s\n", op, opr[0], opr[1], opr[2], opr[3]);

    #define __1byteOP char output[4 + 2 + 1]
    #define __4byteOP char output[4 + 8 + 1]
    #define __8byteOP char output[4 + 16 + 1]

    // process
    switch (util::hash(op))
    {
        case util::hash("NOP"):
            util::force_exit_if(oprc != 0, -1, "operand error at line %d", line_no);
            return "0000";
        case util::hash("STOP"):
            util::force_exit_if(oprc != 0, -1, "operand error at line %d", line_no);
            return "0001";
        case util::hash("INC"):
        {
            util::force_exit_if(oprc != 1, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "010%c", registerIndex(opr[0]));
            return strdup(output);
        }
        case util::hash("ADD"):
        case util::hash("ADD8"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __8byteOP;
            sprintf(output, "014%c%016lX", registerIndex(opr[0]), toGLong(opr[1]));
            return strdup(output);
        }
        case util::hash("ADD4"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __4byteOP;
            sprintf(output, "015%c%08lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFFFFFFFF);
            return strdup(output);
        }
        case util::hash("ADD1"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "015%c%02lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFF);
            return strdup(output);
        }
        case util::hash("DEC"):
        {
            util::force_exit_if(oprc != 1, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "018%c", registerIndex(opr[0]));
            return strdup(output);
        }
        case util::hash("SUB"):
        case util::hash("SUB8"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __8byteOP;
            sprintf(output, "01C%c%016lX", registerIndex(opr[0]), toGLong(opr[1]));
            return strdup(output);
        }
        case util::hash("SUB4"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __4byteOP;
            sprintf(output, "01D%c%08lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFFFFFFFF);
            return strdup(output);
        }
        case util::hash("SUB1"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "01F%c%02lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFF);
            return strdup(output);
        }
        case util::hash("ASN"):
        case util::hash("ASN8"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __8byteOP;
            sprintf(output, "020%c%016lX", registerIndex(opr[0]), toGLong(opr[1]));
            return strdup(output);
        }
        case util::hash("ASN4"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __4byteOP;
            sprintf(output, "021%c%08lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFFFFFFFF);
            return strdup(output);
        }
        case util::hash("ASN1"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "023%c%02lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFF);
            return strdup(output);
        }
        case util::hash("ASNL4"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __4byteOP;
            sprintf(output, "021%c%08lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFFFFFFFF);
            return strdup(output);
        }
        case util::hash("ASNL1"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __1byteOP;
            sprintf(output, "027%c%02lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFF);
            return strdup(output);
        }
        case util::hash("MUL"):
        case util::hash("MUL8"):
        {
            util::force_exit_if(oprc != 2, -1, "operand error at line %d", line_no);
            __8byteOP;
            util::force_exit_if((opr[0][1] - 1) & 4, -1, "operand error at line %d", line_no);
            sprintf(output, "030%c%08lX", registerIndex(opr[0]), toGLong(opr[1]) & 0xFFFFFFFF);
            return strdup(output);
        }
        default:
            util::force_exit(-2, "operator error at line %d", line_no);
    }
}

int main(int argc, char *argv[])
{
    printf("%ld\n", Assembler().toGLong("1abc@15"));
    printf("%s", Assembler().assembleSingleLine("  mul8 xe, 1abc@16// "));
}
