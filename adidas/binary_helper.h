#ifndef _BINARYHELPER_H
#define _BINARYHELPER_H

void splitIntoNibbles(uint8_t byteArray[], uint8_t out[], int size);
uint8_t addParityBits(uint8_t nibble);
uint8_t flipBit(uint8_t byte);
uint8_t decodeNibble(uint8_t nibble);
uint8_t mergeNibblesIntoByte(uint8_t MSB, uint8_t LSB);

#endif
