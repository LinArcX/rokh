#ifndef CAVE_LABEL_H
#define CAVE_LABEL_H

#include "widget.h"

typedef struct
{
  CaveWidget widget;
  CaveText text;

  void (*onLeftClick)(int x, int y);
  void (*onRightClick)(int x, int y);
  void (*onHovered)(int x, int y);
} CaveLabel;

int labelCreate();
int labelInit(CaveLabel* label);

#endif
