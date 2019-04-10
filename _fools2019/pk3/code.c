#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// All memory here is in SRA3

int main() {
    uint8_t buffer[512]; // A567
    uint16_t index;

    uint32_t a0a0 = 0xffffffff;
    // function here (A0A4-A0B7)
    uint32_t a0b8 = 0x00000000;
    uint32_t a0bc = 0x00000000;
    uint32_t a0c0 = 0x00000000;
    // function here (A0C4-A0F2)
    uint32_t a0f3 = 0x5d0b1c11;
    uint32_t a0f7 = 0x35e79125;
    uint32_t a0fb = 0x56596b10;
    uint32_t a0ff = 0x7ffffb0a;
    uint32_t a103 = 0x1b080733;

    uint32_t a107;
    uint16_t a10b; // WorkingWord
    uint8_t a10d;
    uint8_t a10e;


    FILE * f = fopen("buffer.bin", "rb");
    if(!f) {
        perror("Error opening buffer.bin");
        exit(1);
    }
    fread(buffer, 1, 512, f);
    fclose(f);


    do {
        a107 = a103;
        a10b = (a0f3 >>  8) & 0xff;
        a10d = (a0f3 >> 16) & 0xff;
        a10e = (a0f3 >> 24) & 0xff;

        index = 0;
        do {
            a10b = (a10b / 2) * a10d + a10e;
            buffer[index] ^= a10b & 0xff;
            index++;
            index %= 0x200;
            a107 += a0a0;
        } while(a107 != 0);

        // de = A0F7
        // hl = A0F3
        a0b8 = a0f7; // Copy4Bytes
        a0bc = a0c0; // Copy4Bytes
        // de = hl from now on
        do {
            a0bc += a0f3;
            a0b8 += a0a0;
        } while(a0b8 != 0);
        a0f3 = a0bc;

        a0f3 += a0fb;
        a0ff += a0a0;
    } while(a0ff != 0);


    f = fopen("out.bin", "wb");
    fwrite(buffer, 1, 512, f);
    fclose(f);


    for(index = 0; index < 512; index++) {
        printf("%02x ", buffer[index]);
    }
    putchar('\n');


    return 0;
}
