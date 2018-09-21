//
// Created by geno1024 on 2018-09-21.
//

#include "HexIO.h"

void HexIO::hex2bin(const char *input, const char *output)
{
    FILE *fp_in = fopen(input, "r");
    FILE *fp_out = fopen(output, "wb");
    unsigned char buffer[1024] = {0}, zip[512] = {0};
    size_t size, i;
    while ((size = fread(buffer, sizeof(unsigned char), sizeof(buffer), fp_in)))
    {
        for (i = 0; i < size / 2; i++)
        {
            unsigned char left = buffer[2 * i];
            unsigned char right = buffer[2 * i + 1];
            zip[i] = static_cast<unsigned char>(((left & 0x40) >> 2) * 9 + ((left & 0x0F) << 4) + ((right & 0x40) >> 6) * 9 + (right & 0x0F));
        }
        fwrite(zip, sizeof(char), i, fp_out);
    }
    fclose(fp_in);
    fclose(fp_out);
}

void HexIO::bin2hex(const char *input, const char *output)
{
    FILE *fp_in = fopen(input, "r");
    FILE *fp_out = fopen(output, "wb");
    unsigned char zip[512] = {0}, buffer[1024] = {0};
    size_t size, i;
    while ((size = fread(zip, sizeof(unsigned char), sizeof(zip), fp_in)))
    {
        for (i = 0; i < size; i++)
        {
            auto left = (zip[i] & 0xF0) >> 4;
            auto right = zip[i] & 0x0F;
            buffer[2 * i] = static_cast<unsigned char>(48 + ((left & 8 && left & 4) || left & 2) * 7 + (left & 15));
            buffer[2 * i + 1] = static_cast<unsigned char>(48 + ((right & 8 && right & 4) || right & 2) * 7 + (right & 15));
        }
        fwrite(buffer, sizeof(char), i * 2, fp_out);
        fclose(fp_in);
        fclose(fp_out);
    }
}

int main(int argc, char *argv[])
{
    HexIO::hex2bin(argv[1], argv[2]);
    return 0;
}
