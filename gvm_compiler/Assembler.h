//
// Created by geno1024 on 2018-09-18.
//

#ifndef GVM2_ASSEMBLER_H
#define GVM2_ASSEMBLER_H


class Assembler
{
public:
    char registerIndex(char *name);
    unsigned long toGlong(const char *string);
    const char *assembleSingleLine(const char *line);

    unsigned long errno = 0;
};


#endif //GVM2_ASSEMBLER_H