#ifndef CAVE_UTIL_H
#define CAVE_UTIL_H

#include <SDL2/SDL.h>

typedef struct Node
{
  int (*function)(void);
  struct Node* next;
} Node;

void registerCallBackFunction(Node** head, int (*function)(void));
int callFunctions(Node* head);
void freeCallBackFunctionList(Node* head);
void hexToRGBA(const char* hexColor, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a);

#endif
