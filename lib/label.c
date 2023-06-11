#include <stddef.h>

#include "app.h"
#include "label.h"
#include "util/convertor.h"

extern CaveApp* app;
CaveLabel* label = NULL;

SDL_Color labelColor = {0};
SDL_Color labelTextColor = {0};
SDL_Color labelBorderColor = {0};

//------------- Event Handlers -------------//
int labelHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= label->widget.x
      && app->lastCycleMouseMotionEvent.x <= label->widget.x + label->widget.width + label->widget.padding
      && app->lastCycleMouseMotionEvent.y >= label->widget.y
      && app->lastCycleMouseMotionEvent.y <= label->widget.y + label->widget.height + label->widget.padding)
  {
    // for external logics
    if(NULL != label->onHovered)
    {
      label->onHovered(app->lastCycleMouseMotionEvent.x, app->lastCycleMouseMotionEvent.y);
    }

    // for internal logic
    label->widget.hover.isHovered = true;
  }
  else
  {
    label->widget.hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

int labelLeftClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= label->widget.x
      && app->lastCycleMouseButtonEvent.x <= label->widget.x + label->widget.width + label->widget.padding
      && app->lastCycleMouseButtonEvent.y >= label->widget.y
      && app->lastCycleMouseButtonEvent.y <= label->widget.y + label->widget.height + label->widget.padding)
  {
    if(NULL != label->onLeftClick)
    {
      label->onLeftClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }
  }
  return EXIT_SUCCESS;
}

int labelRightClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= label->widget.x
      && app->lastCycleMouseButtonEvent.x <= label->widget.x + label->widget.width + label->widget.padding
      && app->lastCycleMouseButtonEvent.y >= label->widget.y
      && app->lastCycleMouseButtonEvent.y <= label->widget.y + label->widget.height + label->widget.padding)
  {
    if(NULL != label->onRightClick)
    {
      label->onRightClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }
  }
  return EXIT_SUCCESS;
}

int labelCreate()
{
  uint8_t red, green, blue, alpha;
  if (label->widget.hover.isHovered)
  {
    hexToRGBA(app->theme.label.hover.bg, &red, &green, &blue, &alpha);
    labelColor.r = red;
    labelColor.g = green;
    labelColor.b = blue;
    labelColor.a = alpha;

    hexToRGBA(app->theme.label.hover.text, &red, &green, &blue, &alpha);
    labelTextColor.r = red;
    labelTextColor.g = green;
    labelTextColor.b = blue;
    labelTextColor.a = alpha;

    hexToRGBA(app->theme.label.hover.border, &red, &green, &blue, &alpha);
    labelBorderColor.r = red;
    labelBorderColor.g = green;
    labelBorderColor.b = blue;
    labelBorderColor.a = alpha;
  }
  else
  {
    hexToRGBA(app->theme.label.bg, &red, &green, &blue, &alpha);
    labelColor.r = red;
    labelColor.g = green;
    labelColor.b = blue;
    labelColor.a = alpha;

    hexToRGBA(app->theme.label.text, &red, &green, &blue, &alpha);
    labelTextColor.r = red;
    labelTextColor.g = green;
    labelTextColor.b = blue;
    labelTextColor.a = alpha;

    hexToRGBA(app->theme.label.border, &red, &green, &blue, &alpha);
    labelBorderColor.r = red;
    labelBorderColor.g = green;
    labelBorderColor.b = blue;
    labelBorderColor.a = alpha;
  }

  SDL_Surface* surface = TTF_RenderText_Blended(app->widget.font.TTFFont, label->text.text, labelTextColor);
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
    label->widget.x,
    label->widget.y,
    label->widget.width + label->widget.padding,
    label->widget.height + label->widget.padding
  };
  SDL_SetRenderDrawColor(app->renderer, labelColor.r, labelColor.g, labelColor.b, labelColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  // text rectangle
  SDL_Rect textRect = {
    label->widget.x + (label->widget.width - surface->w) / 2 + label->widget.padding / 2,
    label->widget.y + (label->widget.height - surface->h) / 2 + label->widget.padding / 2,
    surface->w,
    surface->h
  };

  SDL_RenderCopy(app->renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  return EXIT_SUCCESS;
}

int labelCreateWidget()
{
  if(EXIT_SUCCESS == labelCreate())
  {
    //if(EXIT_FAILURE == addWidget(app, LABEL, label->widget.UID, &label))
    //{
    //  SDL_Log("[ERROR] labelInit --> addWidget() failed! ");
    //  return EXIT_FAILURE;
    //}
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int labelInit(CaveLabel* lbl)
{
  label = lbl;
  registerCallBackFunction(&app->hoverHandler, labelHoverHandler);
  registerCallBackFunction(&app->leftClickDownHandler, labelLeftClickDownHandler);
  registerCallBackFunction(&app->rightClickDownHandler, labelRightClickDownHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, labelCreateWidget);

  return EXIT_SUCCESS;
}
