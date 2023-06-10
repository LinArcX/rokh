#include <stddef.h>

#include "app.h"
#include "label.h"

extern CaveApp* app;
CaveLabel* label = NULL;
SDL_Color labelBorderColor = {0};

int labelCreate()
{
  uint8_t red, green, blue, alpha;

  hexToRGBA(app->theme.label.bg, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(app->theme.label.text, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  SDL_Surface* surface = TTF_RenderText_Blended(app->widget.font.TTFFont, label->text.text, textColor);
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
  SDL_SetRenderDrawColor(app->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
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
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int labelInit(CaveLabel* lbl)
{
  label = lbl;
  registerCallBackFunction(&app->widgetCreatorHandler, labelCreateWidget);

  if(EXIT_FAILURE == addWidget(app, LABEL, label->widget.UID, &label))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
