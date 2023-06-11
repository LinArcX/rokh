#include "convertor.h"

#include <stdio.h>
#include <stdlib.h>

const char* intToString(int number)
{
  char* str = NULL;
  int length = snprintf(NULL, 0, "%d", number);
  if (length >= 0)
  {
    str = malloc(length + 1);
    if (str != NULL)
    {
      snprintf(str, length + 1, "%d", number);
    }
  }
  return str;
}

char* concatStrings(const char* str1, const char* str2)
{
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);
  char* result = malloc(len1 + len2 + 1); // +1 for null terminator

  if (result != NULL)
  {
    strcpy(result, str1);
    strcat(result, str2);
  }
  return result;
}

char** generateStringList(int size, char* strings[])
{
  char** stringList = malloc((size+1) * sizeof(char*));
  if (stringList == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for string list\n");
    return NULL;
  }

  for (int i = 0; i < size; i++)
  {
    stringList[i] = strdup(strings[i]);
    if (stringList[i] == NULL)
    {
      fprintf(stderr, "Failed to allocate memory for string %d\n", i+1);
      // Free previously allocated strings
      for (int j = 0; j < i; j++) {
          free(stringList[j]);
      }
      free(stringList);
      return NULL;
    }
  }

  return stringList;
}

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
