#include <stddef.h>

#include "button.h"
#include "util.h"

SDL_Color borderColor = {0};

//------------- Borders -------------//
void ButtonCreateLeftBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {0};
  if(button->borderStyle == ALL)
  {
   rect.x = button->x - button->borderDefaultWidth;
   rect.y = button->y - button->borderDefaultHeight;
   rect.w = button->borderDefaultWidth;
   rect.h = button->height + button->padding + (2 * button->borderDefaultHeight);
  }
  else
  {
   rect.x = button->x - button->borderDefaultWidth;
   rect.y = button->y;
   rect.w = button->borderDefaultWidth;
   rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void ButtonCreateRightBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {0};
  if(button->borderStyle == ALL)
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y - button->borderDefaultHeight;
    rect.w = button->borderDefaultWidth;
    rect.h = button->height + button->padding + (2 * button->borderDefaultHeight);
  }
  else
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y;
    rect.w = button->borderDefaultWidth;
    rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void ButtonCreateTopBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {
    button->x,
    button->y - button->borderDefaultHeight,
    button->width + button->padding,
    button->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void ButtonCreateBottomBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {
    button->x ,
    button->y + button->height + button->padding,
    button->width + button->padding,
    button->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void CreateAllBorder(SDL_Renderer* renderer, const Button* button)
{
  ButtonCreateLeftBorder(renderer, button);
  ButtonCreateRightBorder(renderer, button);
  ButtonCreateTopBorder(renderer, button);
  ButtonCreateBottomBorder(renderer, button);
}

int ButtonCreate(SDL_Renderer* renderer, TTF_Font* font, Button button) {
  uint8_t red, green, blue, alpha;

  hexToRGBA(button.textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(button.backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(button.borderColor, &red, &green, &blue, &alpha);
  borderColor.r = red;
  borderColor.g = green;
  borderColor.b = blue;
  borderColor.a = alpha;

  if (button.isHovered)
  {
      hexToRGBA(button.hoverTextColor, &red, &green, &blue, &alpha);
      textColor.r = red;
      textColor.g = green;
      textColor.b = blue;
      textColor.a = alpha;

      hexToRGBA(button.hoverBackgroundColor, &red, &green, &blue, &alpha);
      backgroundColor.r = red;
      backgroundColor.g = green;
      backgroundColor.b = blue;
      backgroundColor.a = alpha;
  }

  // Create a surface from the rendered text
  SDL_Surface* surface = TTF_RenderText_Blended(font, button.text, textColor);
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
  SDL_Rect backgroundRect = { button.x, button.y, button.width + button.padding, button.height + button.padding };
  SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(renderer, &backgroundRect);

  switch(button.borderStyle)
  {
    case LEFT:
      ButtonCreateLeftBorder(renderer, &button);
      break;
    case RIGHT:
      ButtonCreateRightBorder(renderer, &button);
      break;
    case TOP:
      ButtonCreateTopBorder(renderer, &button);
      break;
    case BOTTOM:
      ButtonCreateBottomBorder(renderer, &button);
      break;
    case ALL:
      CreateAllBorder(renderer, &button);
      break;
    default:
       SDL_Log("ERROR -> unknown border style");
      break;
  }

  // text rectangle
  SDL_Rect textRect = { button.x + button.padding / 2, button.y + button.padding / 2, surface->w, surface->h};//button.width, button.height };
  SDL_RenderCopy(renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}
