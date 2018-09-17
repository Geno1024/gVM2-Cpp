//
// Created by geno1024 on 2018-09-07.
//

#ifndef GVM2_CPU_H
#define GVM2_CPU_H


class CPU
{
public:
    explicit CPU(bool debug = false);
    int major = 0;
    int minor = 1;


    void dump();

private:
    bool debug;
    unsigned long XA;
    unsigned long XB;
    unsigned long XC;
    unsigned long XD;
    unsigned long XE;
    unsigned long XF;
    unsigned long XG;
    unsigned long XH;

    unsigned long IP;
    
    unsigned long FLAGS;

};


#endif //GVM2_CPU_H
