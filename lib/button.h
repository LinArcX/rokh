#ifndef _BUTTON_H
#define _BUTTON_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct CaveButtonHover
{
  bool isHovered;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
} ButtonHover;

typedef struct CaveButtonActive
{
  bool isActive;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
} ButtonActive;

typedef struct CaveButtonBorder
{
  BorderStyle style;
  const char* color;
  uint8_t width;
  uint8_t height;
} ButtonBorder;

typedef struct SDLButton
{
  int16_t x;
  int16_t y;
  uint16_t height;
  uint8_t padding;
  int64_t radius;
  uint16_t width;
  const char* backgroundColor;

  const char* text;
  const char* textColor;

  ButtonHover hover;
  ButtonActive active;
  ButtonBorder border;
} Button;

void buttonInit(Button* button);
#endif
