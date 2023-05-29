#include "app.h"
#include "lblAdd.h"
#include "../lib/util.h"

Label lblAdd;

void lblAddLeftClickDownHandler()
{
  if (app->mouse_x >= lblAdd.x
      && app->mouse_x <= lblAdd.x + lblAdd.width + lblAdd.padding
      && app->mouse_y >= lblAdd.y
      && app->mouse_y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    SDL_Log("[lblAdd] leftButton Clicked!");
  }
}

void lblAddRightClickDownHandler()
{
  if (app->mouse_x >= lblAdd.x
      && app->mouse_x <= lblAdd.x + lblAdd.width + lblAdd.padding
      && app->mouse_y >= lblAdd.y
      && app->mouse_y <= lblAdd.y + lblAdd.height + lblAdd.padding)
  {
    SDL_Log("[lblAdd] rightButton Clicked!");
  }
}

void createLblAddWidget()
{
  createLable(app->renderer, app->font, lblAdd);
}

void initLblAdd()
{
  // setup callback functions
  registerCallBackFunction(&app->leftClickDownHandler, lblAddLeftClickDownHandler);
  registerCallBackFunction(&app->rightClickDownHandler, lblAddRightClickDownHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, createLblAddWidget);

  // initialize
  lblAdd.x = 20;
  lblAdd.y = 20;
  lblAdd.radius = 1;
  lblAdd.width = 50;
  lblAdd.height = 20;
  lblAdd.padding = 4;
  lblAdd.text = "Name: ";
  lblAdd.textColor = "#FAFAFA";
  lblAdd.backgroundColor = app->backgroundColor;
}
