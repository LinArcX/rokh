#include "callback.h"

#include <stdlib.h>
#include <stdio.h>

int callFunctions(Node* head)
{
  Node* current = head;
  while (current != NULL)
  {
    if(EXIT_FAILURE == current->function())
    {
      return EXIT_FAILURE;
    }
    current = current->next;
  }
  return EXIT_SUCCESS;
}

void freeCallBackFunctionList(Node* head)
{
  Node* current = head;
  while (current != NULL)
  {
    Node* temp = current;
    current = current->next;
    free(temp);
  }
}

void registerCallBackFunction(Node** head, int (*function)(void))
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->function = function;
  newNode->next = NULL;

  if (*head == NULL)
  {
    *head = newNode;
  }
  else
  {
    Node* current = *head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newNode;
  }
}
