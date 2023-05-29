#include "../lib/app.h"
#include "btnTest.h"

#include "lblTest.h"
#include "../lib/util.h"

Button btnTest;

//------------- Event Handlers -------------//
void btnTestLeftClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= btnTest.x
      && app->lastCycleMouseButtonEvent.x <= btnTest.x + btnTest.width + btnTest.padding
      && app->lastCycleMouseButtonEvent.y >= btnTest.y
      && app->lastCycleMouseButtonEvent.y <= btnTest.y + btnTest.height + btnTest.padding)
  {
    SDL_Log("[btnTest] leftButton Clicked!");
  }
}

void btnTestRightClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= btnTest.x
      && app->lastCycleMouseButtonEvent.x <= btnTest.x + btnTest.width + btnTest.padding
      && app->lastCycleMouseButtonEvent.y >= btnTest.y
      && app->lastCycleMouseButtonEvent.y <= btnTest.y + btnTest.height + btnTest.padding)
  {
    SDL_Log("[btnTest] rightButton Clicked!");
  }
}

void btnTestHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= btnTest.x
      && app->lastCycleMouseMotionEvent.x <= btnTest.x + btnTest.width + btnTest.padding
      && app->lastCycleMouseMotionEvent.y >= btnTest.y
      && app->lastCycleMouseMotionEvent.y <= btnTest.y + btnTest.height + btnTest.padding)
  {
    btnTest.isHovered = true;
    return;
  }
  btnTest.isHovered = false;
}

//------------- Widget Creation -------------//
void btnTestWidgetCreate()
{
  ButtonCreate(app->renderer, app->font, btnTest);
}

//------------- Setup/Initialization -------------//
void setupCallbackFunctions()
{
  registerCallBackFunction(&app->leftClickDownHandler, btnTestLeftClickHandler);
  registerCallBackFunction(&app->rightClickDownHandler, btnTestRightClickHandler);
  registerCallBackFunction(&app->hoverHandler, btnTestHoverHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, btnTestWidgetCreate);
}

void initProperties()
{
  btnTest.x = lblTest.x + lblTest.width;
  btnTest.y = lblTest.y;
  btnTest.radius = 50;
  btnTest.width = 60;
  btnTest.height = lblTest.height;
  btnTest.padding = 6;
  btnTest.backgroundColor = "#1E1E1E";//"#262626", #212121

  btnTest.text = "Search";
  btnTest.textColor = "#FAFAFA"; //#DADADA,

  btnTest.isHovered = false;
  btnTest.hoverText = "";
  btnTest.hoverTextColor = "#212121";
  btnTest.hoverBackgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  btnTest.borderColor = "#616161";
  btnTest.borderStyle = ALL;
  btnTest.borderDefaultWidth = 2;
  btnTest.borderDefaultHeight = 2;
}

void btnTestInit()
{
  setupCallbackFunctions();
  initProperties();
}
