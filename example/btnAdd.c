#include "app.h"
#include "btnAdd.h"
#include "lblAdd.h"
#include "../lib/util.h"

Button btnAdd;

void btnAddLeftClickHandler()
{
  if (app->mouse_x >= btnAdd.x
      && app->mouse_x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && app->mouse_y >= btnAdd.y
      && app->mouse_y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    SDL_Log("[btnAdd] leftButton Clicked!");
  }
}

void btnAddRightClickHandler()
{
  if (app->mouse_x >= btnAdd.x
      && app->mouse_x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && app->mouse_y >= btnAdd.y
      && app->mouse_y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    SDL_Log("[btnAdd] rightButton Clicked!");
  }
}

void btnAddHoverHandler()
{
  if (app->mouse_x >= btnAdd.x
      && app->mouse_x <= btnAdd.x + btnAdd.width + btnAdd.padding
      && app->mouse_y >= btnAdd.y
      && app->mouse_y <= btnAdd.y + btnAdd.height + btnAdd.padding)
  {
    btnAdd.isHovered = true;
    return;
  }
  btnAdd.isHovered = false;
}

void createBtnAddWidget()
{
  createButton(app->renderer, app->font, btnAdd);
}

void initBtnAdd()
{
  // setup callback functions
  registerCallBackFunction(&app->leftClickDownHandler, btnAddLeftClickHandler);
  registerCallBackFunction(&app->rightClickDownHandler, btnAddRightClickHandler);
  registerCallBackFunction(&app->hoverHandler, btnAddHoverHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, createBtnAddWidget);

  // initialize
  btnAdd.x = lblAdd.x + lblAdd.width;
  btnAdd.y = lblAdd.y;
  btnAdd.radius = 50;
  btnAdd.width = 60;
  btnAdd.height = lblAdd.height;
  btnAdd.padding = 6;
  btnAdd.backgroundColor = "#1E1E1E";//"#262626", #212121

  btnAdd.text = "Search";
  btnAdd.textColor = "#FAFAFA"; //#DADADA,

  btnAdd.isHovered = false;
  btnAdd.hoverText = "";
  btnAdd.hoverTextColor = "#212121";
  btnAdd.hoverBackgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  btnAdd.borderColor = "#616161";
  btnAdd.borderStyle = ALL;
  btnAdd.borderDefaultWidth = 2;
  btnAdd.borderDefaultHeight = 2;
}
