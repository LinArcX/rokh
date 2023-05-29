#ifndef _TEXT_INPUT_H
#define _TEXT_INPUT_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct SDLTextInput
{
  int16_t x;
  int16_t y;
  int64_t radius;
  uint16_t width;
  uint16_t height;
  uint8_t padding;
  const char* backgroundColor;

  char* text;
  char newChar;
  const char* textColor;

  bool isHovered;
  const char* hoverText;
  const char* hoverTextColor;
  const char* hoverBackgroundColor;

  const char* borderColor;
  BorderStyle borderStyle;
  uint8_t borderDefaultWidth;
  uint8_t borderDefaultHeight;

}TextInput;

int textInputCreate(SDL_Renderer* renderer, TTF_Font* font, TextInput textInput);

#endif
