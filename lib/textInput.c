#include <stddef.h>

#include "textInput.h"

SDL_Color textInputBorderColor = {0};

void textInputCreateLeftBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {0};
  if(textInput->borderStyle == ALL)
  {
   rect.x = textInput->x - textInput->borderDefaultWidth;
   rect.y = textInput->y - textInput->borderDefaultHeight;
   rect.w = textInput->borderDefaultWidth;
   rect.h = textInput->height + textInput->padding + (2 * textInput->borderDefaultHeight);
  }
  else
  {
   rect.x = textInput->x - textInput->borderDefaultWidth;
   rect.y = textInput->y;
   rect.w = textInput->borderDefaultWidth;
   rect.h = textInput->height + textInput->padding;
  }
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateRightBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {0};
  if(textInput->borderStyle == ALL)
  {
    rect.x = textInput->x + textInput->width + textInput->padding;
    rect.y = textInput->y - textInput->borderDefaultHeight;
    rect.w = textInput->borderDefaultWidth;
    rect.h = textInput->height + textInput->padding + (2 * textInput->borderDefaultHeight);
  }
  else
  {
    rect.x = textInput->x + textInput->width + textInput->padding;
    rect.y = textInput->y;
    rect.w = textInput->borderDefaultWidth;
    rect.h = textInput->height + textInput->padding;
  }
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateTopBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {
    textInput->x,
    textInput->y - textInput->borderDefaultHeight,
    textInput->width + textInput->padding,
    textInput->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateBottomBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {
    textInput->x ,
    textInput->y + textInput->height + textInput->padding,
    textInput->width + textInput->padding,
    textInput->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateAllBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  textInputCreateLeftBorder(renderer, textInput);
  textInputCreateRightBorder(renderer, textInput);
  textInputCreateTopBorder(renderer, textInput);
  textInputCreateBottomBorder(renderer, textInput);
}

int textInputCreate(SDL_Renderer* renderer, TTF_Font* font, TextInput textInput) {
  uint8_t red, green, blue, alpha;

  hexToRGBA(textInput.textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(textInput.backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(textInput.borderColor, &red, &green, &blue, &alpha);
  textInputBorderColor.r = red;
  textInputBorderColor.g = green;
  textInputBorderColor.b = blue;
  textInputBorderColor.a = alpha;

  if (textInput.isHovered)
  {
    hexToRGBA(textInput.hoverTextColor, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(textInput.hoverBackgroundColor, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;
  }

  // Create a surface from the rendered text
  SDL_Surface* surface = TTF_RenderText_Solid(font, textInput.text, textColor);
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
  SDL_Rect backgroundRect = { textInput.x, textInput.y, textInput.width + textInput.padding, textInput.height + textInput.padding };
  SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(renderer, &backgroundRect);

  switch(textInput.borderStyle)
  {
    case LEFT:
      textInputCreateLeftBorder(renderer, &textInput);
      break;
    case RIGHT:
      textInputCreateRightBorder(renderer, &textInput);
      break;
    case TOP:
      textInputCreateTopBorder(renderer, &textInput);
      break;
    case BOTTOM:
      textInputCreateBottomBorder(renderer, &textInput);
      break;
    case ALL:
      textInputCreateAllBorder(renderer, &textInput);
      break;
    default:
      SDL_Log("ERROR -> unknown border style");
      break;
  }

  // Create a destination rectangle for rendering the texture
  SDL_Rect textRect = { textInput.x + textInput.padding / 2, textInput.y + textInput.padding / 2, surface->w, surface->h};//textInput.width, textInput.height };
  // Render the texture on the screen
  SDL_RenderCopy(renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}
