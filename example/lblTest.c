#include "lblTest.h"
#include "../lib/app.h"
#include "../lib/util.h"

Label lblTest;

void lblTestLeftClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= lblTest.x
      && app->lastCycleMouseButtonEvent.x <= lblTest.x + lblTest.width + lblTest.padding
      && app->lastCycleMouseButtonEvent.y >= lblTest.y
      && app->lastCycleMouseButtonEvent.y <= lblTest.y + lblTest.height + lblTest.padding)
  {
    SDL_Log("[lblTest] leftButton Clicked!");
  }
}

void lblTestRightClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= lblTest.x
      && app->lastCycleMouseButtonEvent.x <= lblTest.x + lblTest.width + lblTest.padding
      && app->lastCycleMouseButtonEvent.y >= lblTest.y
      && app->lastCycleMouseButtonEvent.y <= lblTest.y + lblTest.height + lblTest.padding)
  {
    SDL_Log("[lblTest] rightButton Clicked!");
  }
}

void createLblTestWidget()
{
  createLable(app->renderer, app->font, lblTest);
}

void lblTestInit()
{
  // setup callback functions
  registerCallBackFunction(&app->leftClickDownHandler, lblTestLeftClickDownHandler);
  registerCallBackFunction(&app->rightClickDownHandler, lblTestRightClickDownHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, createLblTestWidget);

  // initialize
  lblTest.x = 20;
  lblTest.y = 20;
  lblTest.radius = 1;
  lblTest.width = 50;
  lblTest.height = 20;
  lblTest.padding = 4;
  lblTest.text = "Name: ";
  lblTest.textColor = "#FAFAFA";
  lblTest.backgroundColor = app->backgroundColor;
}
