#include "btnTest.h"
#include "lblTest.h"
#include "../lib/util.h"

Button btnTest;

void btnTestOnLeftClick(int x, int y)
{
  SDL_Log("[%s.OnLeftClick, %d:%d]", btnTest.UID, x, y);
}

void btnTestOnRightClick(int x, int y)
{
  SDL_Log("[%s.OnRightClick, %d:%d]", btnTest.UID, x, y);
}

void btnTestInit()
{
  btnTest.UID = "btnTest";
  btnTest.x = lblTest.x + lblTest.width;
  btnTest.y = lblTest.y;
  btnTest.radius = 50;
  btnTest.padding = 6;
  btnTest.width = 60;
  btnTest.height = lblTest.height;
  btnTest.backgroundColor = "#1E1E1E";//"#262626", #212121

  btnTest.text = "Search";
  btnTest.textColor = "#FAFAFA"; //#DADADA,

  btnTest.hover.isHovered = false;
  btnTest.hover.textColor = "#212121";
  btnTest.hover.backgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  btnTest.border.color = "#616161";
  btnTest.border.style = ALL;
  btnTest.border.width = 2;
  btnTest.border.height = 2;

  btnTest.onLeftClick = btnTestOnLeftClick;
  btnTest.onRightClick = btnTestOnRightClick;

  buttonInit(&btnTest);
}
