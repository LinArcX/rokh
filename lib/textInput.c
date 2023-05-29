#include <stddef.h>
#include "textInput.h"

SDL_Color textInputBorderColor = {0};
//------------- Region detection -------------//
bool textInputIsInside_MouseButtonEvent(TextInput txtInput, SDL_MouseButtonEvent event)
{
  if (event.x >= txtInput.x
      && event.x <= txtInput.x + txtInput.width + txtInput.padding
      && event.y >= txtInput.y
      && event.y <= txtInput.y + txtInput.height + txtInput.padding)
  {
    return true;
  }
  return false;
}

bool textInputIsInside_MouseMotionEvent(TextInput txtInput, SDL_MouseMotionEvent event)
{
  if (event.x >= txtInput.x
      && event.x <= txtInput.x + txtInput.width + txtInput.padding
      && event.y >= txtInput.y
      && event.y <= txtInput.y + txtInput.height + txtInput.padding)
  {
    return true;
  }
  return false;
}
//------------- Borders -------------//
void textInputCreateLeftBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {0};
  if(textInput->border.style == ALL)
  {
    rect.x = textInput->x - textInput->border.width;
    rect.y = textInput->y - textInput->border.height;
    rect.w = textInput->border.width;
    rect.h = textInput->height + textInput->padding + (2 * textInput->border.height);
  }
  else
  {
   rect.x = textInput->x - textInput->border.width;
   rect.y = textInput->y;
   rect.w = textInput->border.width;
   rect.h = textInput->height + textInput->padding;
  }
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateRightBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {0};
  if(textInput->border.style == ALL)
  {
    rect.x = textInput->x + textInput->width + textInput->padding;
    rect.y = textInput->y - textInput->border.height;
    rect.w = textInput->border.width;
    rect.h = textInput->height + textInput->padding + (2 * textInput->border.height);
  }
  else
  {
    rect.x = textInput->x + textInput->width + textInput->padding;
    rect.y = textInput->y;
    rect.w = textInput->border.width;
    rect.h = textInput->height + textInput->padding;
  }
  SDL_SetRenderDrawColor(renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void textInputCreateTopBorder(SDL_Renderer* renderer, const TextInput* textInput)
{
  SDL_Rect rect = {
    textInput->x,
    textInput->y - textInput->border.height,
    textInput->width + textInput->padding,
    textInput->border.height
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
    textInput->border.height
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

int textInputCreate(SDL_Renderer* renderer, TTF_Font* font, TextInput textInput)
{
  uint8_t red, green, blue, alpha;

  hexToRGBA(textInput.textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(textInput.backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(textInput.border.color, &red, &green, &blue, &alpha);
  textInputBorderColor.r = red;
  textInputBorderColor.g = green;
  textInputBorderColor.b = blue;
  textInputBorderColor.a = alpha;

  if (textInput.hover.isHovered)
  {
    hexToRGBA(textInput.hover.textColor, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(textInput.hover.backgroundColor, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;
  }

  SDL_Surface* surface = NULL;
  if (!strlen(textInput.text))
  {
    // Optionally, you can create a blank surface with a default size
    Uint32 format = SDL_PIXELFORMAT_RGBA32;// SDL_PIXELFORMAT_RGBA8888
    surface = SDL_CreateRGBSurface(format, 1, 1, 1, 0, 0, 0, 0);
    if (!surface)
    {
      SDL_Log("Failed to create surface(SDL_CreateRGBSurface): %s", SDL_GetError());
      SDL_FreeSurface(surface);
      return EXIT_FAILURE;
    }
    SDL_SetSurfaceAlphaMod(surface, SDL_ALPHA_TRANSPARENT);
  }
  else
  {
    surface = TTF_RenderText_Solid(font, textInput.text, textColor);
    if (!surface)
    {
      SDL_Log("Failed to create surface(TTF_RenderText_Solid): %s", TTF_GetError());
      SDL_FreeSurface(surface);
      return EXIT_FAILURE;
    }
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

  // text rectangle
  SDL_Rect textRect = { textInput.x + textInput.padding / 2, textInput.y + textInput.padding / 2, surface->w, surface->h};//textInput.width, textInput.height };
  SDL_RenderCopy(renderer, texture, NULL, &textRect);

  // create border
  switch(textInput.border.style)
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

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}
