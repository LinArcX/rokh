#ifndef _LABEL_H
#define _LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct SDLLabel
{
  int16_t x;
  int16_t y;
  int64_t radius;
  uint16_t width;
  uint16_t height;
  uint8_t padding;
  const char* text;
  const char* textColor;
  const char* backgroundColor;
} Label;

int createLable(SDL_Renderer* renderer, TTF_Font* font, Label label);

#endif
