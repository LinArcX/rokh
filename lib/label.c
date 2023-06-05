#include <stddef.h>

#include "app.h"
#include "label.h"

SDL_Color labelBorderColor = {0};
extern App* app;
Label* label = NULL;

int labelCreate() {
  uint8_t red, green, blue, alpha;

  hexToRGBA(label->textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(label->backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  SDL_Surface* surface = TTF_RenderText_Blended(app->font, label->text, textColor);
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
  SDL_Rect backgroundRect = { label->x, label->y, label->width + label->padding, label->height + label->padding };
  SDL_SetRenderDrawColor(app->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  // text rectangle
  SDL_Rect textRect = { label->x + label->padding / 2, label->y + label->padding / 2, surface->w, surface->h}; //label.width, label.height };
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

void labelInit(Label* lbl)
{
  label = lbl;
  registerCallBackFunction(&app->widgetCreatorHandler, labelCreateWidget);
}
