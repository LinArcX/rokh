#include <stddef.h>

#include "app.h"
#include "button.h"
#include "util.h"

extern CaveApp* app;
CaveButton* button = NULL;

SDL_Color buttonColor = {0};
SDL_Color buttonTextColor = {0};
SDL_Color buttonBorderColor = {0};

//------------- Event Handlers -------------//
int buttonLeftClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= button->widget.x
      && app->lastCycleMouseButtonEvent.x <= button->widget.x + button->widget.width + button->widget.padding
      && app->lastCycleMouseButtonEvent.y >= button->widget.y
      && app->lastCycleMouseButtonEvent.y <= button->widget.y + button->widget.height + button->widget.padding)
  {
    if(NULL != button->onLeftClick)
    {
      button->onLeftClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }
  }
  return EXIT_SUCCESS;
}

int buttonRightClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= button->widget.x
      && app->lastCycleMouseButtonEvent.x <= button->widget.x + button->widget.width + button->widget.padding
      && app->lastCycleMouseButtonEvent.y >= button->widget.y
      && app->lastCycleMouseButtonEvent.y <= button->widget.y + button->widget.height + button->widget.padding)
  {
    if(NULL != button->onRightClick)
    {
      button->onRightClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }
  }
  return EXIT_SUCCESS;
}

int buttonHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= button->widget.x
      && app->lastCycleMouseMotionEvent.x <= button->widget.x + button->widget.width + button->widget.padding
      && app->lastCycleMouseMotionEvent.y >= button->widget.y
      && app->lastCycleMouseMotionEvent.y <= button->widget.y + button->widget.height + button->widget.padding)
  {
    // for external logics
    if(NULL != button->onHovered)
    {
      button->onHovered(app->lastCycleMouseMotionEvent.x, app->lastCycleMouseMotionEvent.y);
    }

    // for internal logic
    button->widget.hover.isHovered = true;
  }
  else
  {
    button->widget.hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

//------------- Borders -------------//
void ButtonCreateLeftBorder()
{
  SDL_Rect rect = {0};
  if(button->widget.border.style == ALL)
  {
   rect.x = button->widget.x - button->widget.border.width;
   rect.y = button->widget.y - button->widget.border.height;
   rect.w = button->widget.border.width;
   rect.h = button->widget.height + button->widget.padding + (2 * button->widget.border.height);
  }
  else
  {
   rect.x = button->widget.x - button->widget.border.width;
   rect.y = button->widget.y;
   rect.w = button->widget.border.width;
   rect.h = button->widget.height + button->widget.padding;
  }
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateRightBorder()
{
  SDL_Rect rect = {0};
  if(button->widget.border.style == ALL)
  {
    rect.x = button->widget.x + button->widget.width + button->widget.padding;
    rect.y = button->widget.y - button->widget.border.height;
    rect.w = button->widget.border.width;
    rect.h = button->widget.height + button->widget.padding + (2 * button->widget.border.height);
  }
  else
  {
    rect.x = button->widget.x + button->widget.width + button->widget.padding;
    rect.y = button->widget.y;
    rect.w = button->widget.border.width;
    rect.h = button->widget.height + button->widget.padding;
  }
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateTopBorder()
{
  SDL_Rect rect = {
    button->widget.x,
    button->widget.y - button->widget.border.height,
    button->widget.width + button->widget.padding,
    button->widget.border.height
  };
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateBottomBorder()
{
  SDL_Rect rect = {
    button->widget.x ,
    button->widget.y + button->widget.height + button->widget.padding,
    button->widget.width + button->widget.padding,
    button->widget.border.height
  };
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void CreateAllBorder()
{
  ButtonCreateLeftBorder();
  ButtonCreateRightBorder();
  ButtonCreateTopBorder();
  ButtonCreateBottomBorder();
}

int buttonCreate() {
  uint8_t red, green, blue, alpha;
  if (button->widget.hover.isHovered)
  {
    hexToRGBA(app->theme.button.hover.bg, &red, &green, &blue, &alpha);
    buttonColor.r = red;
    buttonColor.g = green;
    buttonColor.b = blue;
    buttonColor.a = alpha;

    hexToRGBA(app->theme.button.hover.text, &red, &green, &blue, &alpha);
    buttonTextColor.r = red;
    buttonTextColor.g = green;
    buttonTextColor.b = blue;
    buttonTextColor.a = alpha;

    hexToRGBA(app->theme.button.hover.border, &red, &green, &blue, &alpha);
    buttonBorderColor.r = red;
    buttonBorderColor.g = green;
    buttonBorderColor.b = blue;
    buttonBorderColor.a = alpha;
  }
  else
  {
    hexToRGBA(app->theme.button.bg, &red, &green, &blue, &alpha);
    buttonColor.r = red;
    buttonColor.g = green;
    buttonColor.b = blue;
    buttonColor.a = alpha;

    hexToRGBA(app->theme.button.text, &red, &green, &blue, &alpha);
    buttonTextColor.r = red;
    buttonTextColor.g = green;
    buttonTextColor.b = blue;
    buttonTextColor.a = alpha;

    hexToRGBA(app->theme.button.border, &red, &green, &blue, &alpha);
    buttonBorderColor.r = red;
    buttonBorderColor.g = green;
    buttonBorderColor.b = blue;
    buttonBorderColor.a = alpha;
  }
  // Create a surface from the rendered text
  SDL_Surface* surface = TTF_RenderText_Blended(app->widget.font.TTFFont, button->text.text, buttonTextColor);
  if (!surface)
  {
    SDL_Log("Failed to create surface: %s", TTF_GetError());
    SDL_FreeSurface(surface);
    return EXIT_FAILURE;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, surface);
  if (!texture)
  {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
    SDL_DestroyTexture(texture);
    return EXIT_FAILURE;
  }

  // background rectangle
  SDL_Rect backgroundRect = {
    button->widget.x,
    button->widget.y,
    button->widget.width + button->widget.padding,
    button->widget.height + button->widget.padding
  };
  SDL_SetRenderDrawColor(app->renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  switch(button->widget.border.style)
  {
    case LEFT:
      ButtonCreateLeftBorder();
      break;
    case RIGHT:
      ButtonCreateRightBorder();
      break;
    case TOP:
      ButtonCreateTopBorder();
      break;
    case BOTTOM:
      ButtonCreateBottomBorder();
      break;
    case ALL:
      CreateAllBorder();
      break;
    default:
       SDL_Log("ERROR -> unknown border style");
      break;
  }

  // text rectangle
  SDL_Rect textRect = {
    button->widget.x + (button->widget.width - surface->w) / 2 + button->widget.padding / 2,
    button->widget.y + (button->widget.height - surface->h) / 2 + button->widget.padding / 2,
    surface->w,
    surface->h
  };
  SDL_RenderCopy(app->renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  return EXIT_SUCCESS;
}

int buttonCreateWidget()
{
  if(EXIT_SUCCESS == buttonCreate())
  {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int buttonInit(CaveButton* btn)
{
  button = btn;
  registerCallBackFunction(&app->hoverHandler, buttonHoverHandler);
  registerCallBackFunction(&app->leftClickDownHandler, buttonLeftClickHandler);
  registerCallBackFunction(&app->rightClickDownHandler, buttonRightClickHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, buttonCreateWidget);

  if(EXIT_FAILURE == addWidget(app, BUTTON, button->widget.UID, &button))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
