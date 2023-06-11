#ifndef CAVE_UTIL_CALLBACK_H
#define CAVE_UTIL_CALLBACK_H

typedef struct Node
{
  int (*function)(void);
  struct Node* next;
} Node;

int callFunctions(Node* head);
void freeCallBackFunctionList(Node* head);
void registerCallBackFunction(Node** head, int (*function)(void));

#endif
