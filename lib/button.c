#include <stddef.h>

#include "app.h"
#include "button.h"

SDL_Color buttonBorderColor = {0};
extern App* app;
Button* button = NULL;

//------------- Event Handlers -------------//
int buttonLeftClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= button->x
      && app->lastCycleMouseButtonEvent.x <= button->x + button->width + button->padding
      && app->lastCycleMouseButtonEvent.y >= button->y
      && app->lastCycleMouseButtonEvent.y <= button->y + button->height + button->padding)
  {
    SDL_Log("[btnTest] leftButton Clicked!");
  }
  return EXIT_SUCCESS;
}

int buttonRightClickHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= button->x
      && app->lastCycleMouseButtonEvent.x <= button->x + button->width + button->padding
      && app->lastCycleMouseButtonEvent.y >= button->y
      && app->lastCycleMouseButtonEvent.y <= button->y + button->height + button->padding)
  {
    SDL_Log("[btnTest] rightButton Clicked!");
  }
  return EXIT_SUCCESS;
}

int buttonHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= button->x
      && app->lastCycleMouseMotionEvent.x <= button->x + button->width + button->padding
      && app->lastCycleMouseMotionEvent.y >= button->y
      && app->lastCycleMouseMotionEvent.y <= button->y + button->height + button->padding)
  {
    button->hover.isHovered = true;
  }
  else
  {
    button->hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

//------------- Borders -------------//
void ButtonCreateLeftBorder()
{
  SDL_Rect rect = {0};
  if(button->border.style == ALL)
  {
   rect.x = button->x - button->border.width;
   rect.y = button->y - button->border.height;
   rect.w = button->border.width;
   rect.h = button->height + button->padding + (2 * button->border.height);
  }
  else
  {
   rect.x = button->x - button->border.width;
   rect.y = button->y;
   rect.w = button->border.width;
   rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateRightBorder()
{
  SDL_Rect rect = {0};
  if(button->border.style == ALL)
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y - button->border.height;
    rect.w = button->border.width;
    rect.h = button->height + button->padding + (2 * button->border.height);
  }
  else
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y;
    rect.w = button->border.width;
    rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateTopBorder()
{
  SDL_Rect rect = {
    button->x,
    button->y - button->border.height,
    button->width + button->padding,
    button->border.height
  };
  SDL_SetRenderDrawColor(app->renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void ButtonCreateBottomBorder()
{
  SDL_Rect rect = {
    button->x ,
    button->y + button->height + button->padding,
    button->width + button->padding,
    button->border.height
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

  hexToRGBA(button->textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(button->backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(button->border.color, &red, &green, &blue, &alpha);
  buttonBorderColor.r = red;
  buttonBorderColor.g = green;
  buttonBorderColor.b = blue;
  buttonBorderColor.a = alpha;

  if (button->hover.isHovered)
  {
    hexToRGBA(button->hover.textColor, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(button->hover.backgroundColor, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;
  }

  // Create a surface from the rendered text
  SDL_Surface* surface = TTF_RenderText_Blended(app->font, button->text, textColor);
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
  SDL_Rect backgroundRect = { button->x, button->y, button->width + button->padding, button->height + button->padding };
  SDL_SetRenderDrawColor(app->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  switch(button->border.style)
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
  SDL_Rect textRect = { button->x + button->padding / 2, button->y + button->padding / 2, surface->w, surface->h};//button.width, button.height };
  SDL_RenderCopy(app->renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}

int buttonCreateWidget()
{
  if(EXIT_SUCCESS == buttonCreate())
  {
    if(EXIT_SUCCESS == addWidget(app, BUTTON, &button))
    {
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

void buttonInit(Button* btn)
{
  button = btn;
  registerCallBackFunction(&app->hoverHandler, buttonHoverHandler);
  registerCallBackFunction(&app->leftClickDownHandler, buttonLeftClickHandler);
  registerCallBackFunction(&app->rightClickDownHandler, buttonRightClickHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, buttonCreateWidget);
}

//------------- Widget Creation -------------//
//void btnTestWidgetCreate()
//{
//  ButtonCreate(app->renderer, app->font, btnTest);
//}
