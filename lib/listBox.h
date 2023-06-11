#ifndef CAVE_LIST_BOX_H
#define CAVE_LIST_BOX_H

#include "widget.h"
#include "label.h"

typedef struct
{
  CaveText header;
  CaveLabel* items;
  CaveWidget widget;

  int num_items;
  int top_item;
  int selected_item;
  int visible_items;

  void (*onItemLeftClick)(int x, int y);
  void (*onItemRightClick)(int x, int y);
  void (*onHovered)(int x, int y);

} CaveListBox;

int listBoxInit(CaveListBox* listBox);

#endif
