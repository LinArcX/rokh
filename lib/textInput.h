#ifndef CAVE_TEXT_INPUT_H
#define CAVE_TEXT_INPUT_H

#include "widget.h"

typedef struct
{
  CaveWidget widget;
  CaveText text;
  CaveCaret caret;
  char incomingChar;

  void (*onBackSpace)(void);
  void (*onEmpty)(void);
  void (*onCharAppend)(void);
  void (*onHovered)(int x, int y);

} CaveTextInput;

int textInputInit(CaveTextInput* txtInput);

#endif
