#ifndef CAVE_UTIL_CONVERTOR_H
#define CAVE_UTIL_CONVERTOR_H

#include <SDL2/SDL.h>

const char* intToString(int number);
char* concatStrings(const char* str1, const char* str2);
char** generateStringList(int size, char* strings[]);

void hexToRGBA(const char* hexColor, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a);

#endif
