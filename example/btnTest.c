#include "btnTest.h"
#include "lblTest.h"

CaveButton btnTest;

void btnTestOnLeftClick(int x, int y)
{
  printWidgets();
}

void btnTestOnRightClick(int x, int y)
{
  SDL_Log("[%s.OnRightClick, %d:%d]", btnTest.widget.UID, x, y);
}

int btnTestInit()
{
  btnTest.widget.UID = "btnTest";
  btnTest.widget.x = lblTest.widget.x + lblTest.widget.width;
  btnTest.widget.y = lblTest.widget.y;
  btnTest.widget.width = 60;
  btnTest.widget.height = lblTest.widget.height;
  btnTest.widget.radius = 50;
  btnTest.widget.padding = 6;

  btnTest.text.text = "Search";
  btnTest.widget.hover.isHovered = false;

  btnTest.text.color = "#E0E0E0";
  btnTest.widget.color = "#757575";
  btnTest.widget.border.color = "#616161";

  btnTest.text.hover.color = "#EEEEEE";
  btnTest.widget.hover.color = "#616161";
  btnTest.widget.border.hover.color = "#424242";

  btnTest.widget.border.style = ALL;
  btnTest.widget.border.width = 2;
  btnTest.widget.border.height = 2;

  btnTest.onLeftClick = btnTestOnLeftClick;
  btnTest.onRightClick = btnTestOnRightClick;

  if(EXIT_FAILURE == buttonInit(&btnTest))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
