#ifndef _TEXT_INPUT_H
#define _TEXT_INPUT_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct SDLTextInputHover
{
  bool isHovered;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
}TextInputHover;

typedef struct SDLTextInputActive
{
  bool isActive;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
}TextInputActive;

typedef struct SDLTextInputBorder
{
  BorderStyle style;
  const char* color;
  uint8_t width;
  uint8_t height;
}TextInputBorder;

typedef struct SDLTextInput
{
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  int64_t radius;
  uint8_t padding;
  uint16_t caretPostion;
  const char* backgroundColor;

  char* text;
  const char* textColor;
  char incomingChar;

  TextInputHover hover;
  TextInputActive active;
  TextInputBorder border;
}TextInput;

void textInputInit(TextInput* txtInput);
#endif

//bool caveTextInputIsInsideBackSpaceEvent(TextInput* txtInput, SDL_MouseButtonEvent event);
//bool caveTextInputIsInsideAppendCharEvent(TextInput* txtInput, SDL_MouseButtonEvent event);
//bool caveTextInputIsInsideHoverEvent(TextInput txtInput, SDL_MouseMotionEvent event);
