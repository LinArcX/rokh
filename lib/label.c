#include <stddef.h>

#include "label.h"
#include "util.h"

int createLable(SDL_Renderer* renderer, TTF_Font* font, Label label) {
  uint8_t red, green, blue, alpha;

  hexToRGBA(label.textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(label.backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  SDL_Surface* surface = TTF_RenderText_Blended(font, label.text, textColor);
  if (!surface)
  {
    SDL_Log("Failed to create surface: %s", TTF_GetError());
    SDL_FreeSurface(surface);
    return EXIT_FAILURE;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture)
  {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
    SDL_DestroyTexture(texture);
    return EXIT_FAILURE;
  }

  // background rectangle
  SDL_Rect backgroundRect = { label.x, label.y, label.width + label.padding, label.height + label.padding };
  SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(renderer, &backgroundRect);

  // text rectangle
  SDL_Rect textRect = { label.x + label.padding / 2, label.y + label.padding / 2, surface->w, surface->h}; //label.width, label.height };
  SDL_RenderCopy(renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  return EXIT_SUCCESS;
}

//// Render rounded corners
//SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 0); // Set color to transparent
//SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);
//SDL_Rect corners[4] = {
//  { label.x, label.y, label.radius, label.radius },
//  { label.x + label.width - label.radius, label.y, label.radius, label.radius },
//  { label.x, label.y + label.height - label.radius, label.radius, label.radius },
//  { label.x + label.width - label.radius, label.y + label.height - label.radius, label.radius, label.radius }
  //};
  //for (int i = 0; i < 4; i++)
  //{
  //  SDL_RenderFillRect(app->renderer, &corners[i]);
  //}
