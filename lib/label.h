#ifndef CAVE_LABEL_H
#define CAVE_LABEL_H

#include "widget.h"

typedef struct
{
  CaveWidget widget;
  CaveText text;
} CaveLabel;

int labelInit(CaveLabel* label);

#endif
