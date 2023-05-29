#include "util.h"

#include <stdio.h>

void hexToRGBA(const char* hexColor, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a)
{
  // Skip the '#' character if present
  if (hexColor[0] == '#')
  {
    hexColor++;
  }

  // Convert the hexadecimal color value to unsigned integer
  unsigned int hexValue;
  sscanf(hexColor, "%x", &hexValue);

  // Extract the color components using bitwise operations
  *r = (hexValue >> 16) & 0xFF;       // Red component
  *g = (hexValue >> 8) & 0xFF;        // Green component
  *b = hexValue & 0xFF;                // Blue component
  *a = (hexValue >> 24) & 0xFF;      // Alpha component (if present)

  // If alpha component is not specified, set it to 255 (fully opaque)
  if (*a == 0)
  {
    *a = 255;
  }
}

void registerCallBackFunction(Node** head, void (*function)())
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

void callFunctions(Node* head)
{
  Node* current = head;
  while (current != NULL)
  {
    current->function();
    current = current->next;
  }
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
