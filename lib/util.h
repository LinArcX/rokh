#ifndef _UTIL_H
#define _UTIL_H

#include <SDL2/SDL.h>

typedef struct Node {
    int (*function)(void);
    struct Node* next;
} Node;

typedef enum _BorderStyle
{
  LEFT = 0,
  RIGHT,
  TOP,
  BOTTOM,
  ALL
} BorderStyle;

void registerCallBackFunction(Node** head, int (*function)(void));
int callFunctions(Node* head);
void freeCallBackFunctionList(Node* head);

void hexToRGBA(const char* hexColor, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a);

#endif
