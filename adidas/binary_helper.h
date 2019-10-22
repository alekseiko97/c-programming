#ifndef _BINARYHELPER_H
#define _BINARYHELPER_H

void splitIntoNibbles(uint8_t byte, uint8_t nibbles[]);
void addParityBits(uint8_t *nibble);
void flipBit(uint8_t *byte);
void decodeNibble(uint8_t *nibble);
uint8_t mergeNibblesIntoByte(uint8_t MSB, uint8_t LSB);

void writeToFile(uint8_t byte, const char* output_filename);

#endif
