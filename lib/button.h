#ifndef CAVE_BUTTON_H
#define CAVE_BUTTON_H

#include "widget.h"

typedef struct
{
  CaveWidget widget;
  CaveText text;

  void (*onLeftClick)(int x, int y);
  void (*onRightClick)(int x, int y);
  void (*onHovered)(int x, int y);
} CaveButton;

int buttonInit(CaveButton* button);

#endif
