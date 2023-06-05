#ifndef _LABEL_H
#define _LABEL_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct CaveBorder
{
  BorderStyle style;
  const char* color;
  uint8_t width;
  uint8_t height;
} LabelBorder;

typedef struct CaveLabel
{
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  int64_t radius;
  uint8_t padding;
  const char* backgroundColor;

  const char* text;
  const char* textColor;
  LabelBorder border;
} Label;

void labelInit(Label* label);
#endif
