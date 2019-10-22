#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>    // time()
#include <stdbool.h> // boolean
#include "binary_helper.h"

/*
    This function is splitting every byte into two nibbles.

    Nibbles are structured in a way that first four bits are occupied by data bits
    and the last three (least significant) are reserved for parity bits (will be added later)
*/

void splitIntoNibbles(uint8_t byte, uint8_t out[]) {
    uint8_t highNibble = byte & 0xF0; // clean second part
    uint8_t lowNibble = (byte & 0x0F) << 4; // clean first part and shift to to the left 

    out[0] = highNibble;
    out[1] = lowNibble;
}

/*
    In this function we calculate parity bits and add them to the given nibble
*/

void addParityBits(uint8_t *nibble) {
    
    uint8_t data[4]; // 4 data bits
    uint8_t parity[3]; // 3 parity bits

    int i;
    for (i = 0; i < 4; i++) {
        // get the individual bits at first 4 positions
        data[i] = *nibble & (1 << (i + 4)) ? 1 : 0; // (1101) 0000
    }

    /*
        p0: d0 + d1 + d2
        p1: d0 + d1 + d3
        p2: d1 + d2 + d3 
    */
   parity[0] = data[0] + data[1] + data[2];
   parity[1] = data[0] + data[1] + data[3];
   parity[2] = data[1] + data[2] + data[3];

    /*
        We check the sum of data bits.
        If it is even, we do nothing.
        If it is odd, we add 1 as a parity bit.
    */

   for (i = 0; i < 3; i++) {
       parity[i] = parity[i] % 2 == 0 ? 0 : 1;
   }

   printf("\nAfter adding parity bits: \n");
   printf("data[0]: %d, data[1]: %d, data[2]: %d, parity[0]: %d\n", data[0], data[1], data[2], parity[0]);
   printf("data[0]: %d, data[1]: %d, data[3]: %d, parity[1]: %d\n", data[0], data[1], data[3], parity[1]);
   printf("data[1]: %d, data[2]: %d, data[3]: %d, parity[2]: %d\n", data[1], data[2], data[3], parity[2]);
   printf("-------------\n");

    // shift all bits to the right by one to have 1 zero byte in front
   *nibble >>= 1; 

    // add parity bits
    for (i = 0; i < 3; i++) {
        *nibble ^= (parity[i] << i); 
    }

    printf("New byte: %ul\n", *nibble);
}

/*
    Used to flip one random bit in the provided byte
*/
void flipBit(uint8_t *byte) {

    int random = rand() % 6; 
    printf("Shifted by: %d\n", random);

    uint8_t mask = 1 << random;
    *byte ^= mask;
}

void decodeNibble(uint8_t *nibble) {
    uint8_t parity[3];
    uint8_t data[4];

    uint8_t p0, p1, p2; // circles

    // byte structure: 0 (d3 d2 d1 d0) (p2 p1 p0)

    // extract data bits
    int i;
    for (i = 0; i < 4; i++) {
        data[i] = *nibble & ( 1 << (i + 3) ) ? 1 : 0;
    }

    // extract parity bits
    for (i = 0; i < 3; i++) {
        parity[i] = *nibble & ( 1 << i ) ? 1 : 0;
    }

    /*
        p0: d0 + d1 + d2
        p1: d0 + d1 + d3
        p2: d1 + d2 + d3 
    */

    p0 = data[0] + data[1] + data[2] + parity[0];
    p1 = data[0] + data[1] + data[3] + parity[1];
    p2 = data[1] + data[2] + data[3] + parity[2];

    bool p0_even = p0 % 2 == 0;
    bool p1_even = p1 % 2 == 0;
    bool p2_even = p2 % 2 == 0;

    // check for data bits
    if (p0_even && p1_even && p2_even) {
        printf("\nOK. No corruption was detected in the given byte\n");
        printf("----------\n");
    } else if (!p0_even && !p1_even && p2_even) {
        *nibble ^= (1 << 3);
    } else if (!p0_even && !p1_even && !p2_even){
        *nibble ^= (1 << 4);
    } else if (!p0_even && p1_even && !p2_even) {
        *nibble ^= (1 << 5);
    } else if (p0_even && !p1_even && !p2_even) {
        *nibble ^= (1 << 6);
        // check for parity bits
    } else if (!p0_even && p1_even && p2_even) {
        *nibble ^= 1;
    } else if (p0_even && !p1_even && p2_even) {
        *nibble ^= (1 << 1);
    } else if (p0_even && p1_even && !p2_even) {
        *nibble ^= (1 << 2);
    }

    printf("\nFixed:\n");
    printf("data[0]: %d, data[1]: %d, data[2]: %d, parity[0]: %d\n", data[0], data[1], data[2], parity[0]);
    printf("data[0]: %d, data[1]: %d, data[3]: %d, parity[1]: %d\n", data[0], data[1], data[3], parity[1]);
    printf("data[1]: %d, data[2]: %d, data[3]: %d, parity[2]: %d\n", data[1], data[2], data[3], parity[2]);
    printf("--------\n");
}

/*
    This function is used to reconstruct the original byte by merging two nibbles.
    The return value is original byte
*/

uint8_t mergeNibblesIntoByte(uint8_t MSB, uint8_t LSB) {

    uint8_t new = 0; 
    // get rid of parity bits
    MSB >>= 3;
    MSB <<= 4;
    LSB >>= 3;

    // merge 2 nibbles
    new = MSB | LSB;

    return new;
}

void writeToFile(uint8_t byte, const char* filename) {
    FILE* fp;
    fp = fopen(filename, "a"); // write in binary

    if (fp == NULL) {
        printf("Error while writing to the file.\n");
        return;
    }

    fwrite(&byte, sizeof(byte), 1, fp);
    
    fclose(fp);
}