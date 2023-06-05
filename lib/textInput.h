#ifndef CAVE_TEXT_INPUT_H
#define CAVE_TEXT_INPUT_H

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct CaveTextInputHover
{
  bool isHovered;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
} TextInputHover;

typedef struct CaveTextInputActive
{
  bool isActive;
  const char* textColor;
  const char* borderColor;
  const char* backgroundColor;
} TextInputActive;

typedef struct CaveTextInputBorder
{
  BorderStyle style;
  const char* color;
  uint8_t width;
  uint8_t height;
} TextInputBorder;

typedef struct CaveTextInput
{
  char* UID;
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

  void (*onBackSpace)(void);
  void (*onEmpty)(void);
  void (*onCharAppend)(void);
  void (*onHovered)(void);

}TextInput;

void textInputInit(TextInput* txtInput);

#endif
