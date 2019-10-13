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

void splitIntoNibbles(uint8_t byteArray[], uint8_t out[], int size) {

    int i;
    for (i = 0; i < size; i++) {
        uint8_t highNibble = byteArray[i] & 0xF0; // clean second part
        uint8_t lowNibble = (byteArray[i] & 0x0F) << 4; // clean first part and shift to to the left 

        // twice bigger than the original array because we create 2 new bytes out of one
        int index = i * 2; 
        out[index] = highNibble;
        out[index + 1] = lowNibble;
    }
}

/*
    In this function we calculate parity bits and add them to the given nibble
*/

uint8_t addParityBits(uint8_t nibble) {
    
    int data[4]; // 4 data bits
    int parity[3]; // 3 parity bits

    int i;
    for (i = 0; i < 4; i++) {
        // get the individual bits at first 4 positions
        data[i] = nibble & (1 << (i + 4)) ? 1 : 0; // (1101) 0000
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
   nibble >>= 1; 

    // add parity bits
    for (i = 0; i < 3; i++) {
        nibble ^= (parity[i] << i); 
    }

    printf("New byte: %ul\n", nibble);

    return nibble; // new byte
}

/*
    Used to flip one random bit in the provided byte
*/
uint8_t flipBit(uint8_t byte) {

    int random = rand() % 6; 
    printf("Shifted by: %d\n", random);

    uint8_t mask = 1 << random;
    byte ^= mask;
    
    return byte;
}

uint8_t decodeNibble(uint8_t nibble) {
    uint8_t parity[3];
    uint8_t data[4];

    uint8_t p0, p1, p2; // circles
    uint8_t decoded = 0; // holder for the decoded byte

    // byte structure: 0 (d3 d2 d1 d0) (p2 p1 p0)

    // extract data bits
    int i;
    for (i = 0; i < 4; i++) {
        data[i] = nibble & ( 1 << (i + 3) ) ? 1 : 0;
    }

    // extract parity bits
    for (i = 0; i < 3; i++) {
        parity[i] = nibble & ( 1 << i ) ? 1 : 0;
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

    if (p0_even && p1_even && p2_even) {
        printf("\nOK. No corruption was detected in the given byte\n");
        printf("----------\n");
        return nibble;
    } else if (!p0_even && !p1_even && p2_even) {
        data[0] ^= 1;
    } else if (!p0_even && !p1_even && !p2_even){
        data[1] ^= 1;
    } else if (!p0_even && p1_even && !p2_even) {
        data[2] ^= 1;
    } else if (p0_even && !p1_even && !p2_even) {
        data[3] ^= 1;
    } else if (!p0_even && p1_even && p2_even) {
        parity[0] ^= 1;
    } else if (p0_even && !p1_even && p2_even) {
        parity[1] ^= 1;
    } else if (p0_even && p1_even && !p2_even) {
        parity[2] ^= 1;
    }

    printf("\nFixed:\n");
    printf("data[0]: %d, data[1]: %d, data[2]: %d, parity[0]: %d\n", data[0], data[1], data[2], parity[0]);
    printf("data[0]: %d, data[1]: %d, data[3]: %d, parity[1]: %d\n", data[0], data[1], data[3], parity[1]);
    printf("data[1]: %d, data[2]: %d, data[3]: %d, parity[2]: %d\n", data[1], data[2], data[3], parity[2]);
    printf("--------\n");

    // add parity bits
    for (i = 0; i < 3; i++) {
        decoded ^= ( parity[i] << i ); 
    }

    // add data bits 
    for (i = 0; i < 4; i++) {
        decoded ^= ( data[i] << ( i + 3 ) );
    }

    return decoded;
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