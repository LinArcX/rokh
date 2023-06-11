#include "lstBoxTest.h"
#include "../lib/app.h"
#include "txtInputTest.h"
#include "../lib/util/convertor.h"

CaveListBox lstBoxTest;

int lstBoxTestInit()
{
  lstBoxTest.header.text = "Choose: ";
  lstBoxTest.widget.UID = "lstBoxTest";
  lstBoxTest.widget.x = txtInputTest.widget.x + txtInputTest.widget.width + txtInputTest.widget.padding + 10;
  lstBoxTest.widget.y = txtInputTest.widget.y;
  lstBoxTest.widget.radius = 1;
  lstBoxTest.widget.width = 50;
  lstBoxTest.widget.height = 120;
  lstBoxTest.widget.padding = 4;
  lstBoxTest.widget.hover.isHovered = false;
  lstBoxTest.widget.border.style = ALL;
  lstBoxTest.widget.border.width = 2;
  lstBoxTest.widget.border.height = 2;

  int itemsCount = 4;
  CaveLabel items[itemsCount];
  items[0].text.text = "Apple";
  items[1].text.text = "Orange";
  items[2].text.text = "Coconut";
  items[3].text.text = "Strawberry";
  lstBoxTest.items = items;
  lstBoxTest.num_items = itemsCount;
  lstBoxTest.top_item = 0;
  lstBoxTest.visible_items = 3;
  lstBoxTest.selected_item = -1;

  if(EXIT_FAILURE == listBoxInit(&lstBoxTest))
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

  //char* itemsNames[] = {
  //  "Apple",
  //  "Orange",
  //  "Coconut",
  //  "Strawberry"
  //};
  //char** items = generateStringList(itemsCount, itemsNames);
  //
  //  //for (int i = 0; i < num_strings; i++)
  //{
  //  free(strings[i]);
  //}
  //free(strings);
