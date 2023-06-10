#include <stddef.h>
#include <stdlib.h>

#include "app.h"
#include "textInput.h"

extern App* app;
SDL_Rect caretRect = {0};
CaveTextInput* textInput = NULL;

SDL_Color textColor = {0};
SDL_Color backgroundColor = {0};
SDL_Color textInputBorderColor = {0};

//------------- Region detection -------------//
bool caveTextInputIsInsideAppendCharEvent(CaveTextInput* textInput, SDL_MouseButtonEvent event)
{
  if (event.x >= textInput->widget.x
      && event.x <= textInput->widget.x + textInput->widget.width + textInput->widget.padding
      && event.y >= textInput->widget.y
      && event.y <= textInput->widget.y + textInput->widget.height + textInput->widget.padding)
  {
    if(textInput->caret.type == VERTICAL)
    {
      if(strlen(textInput->text.text) * 8 < textInput->widget.width - caretRect.w * 16)
      {
        textInput->caret.postion += 8;
        return true;
      }
    }
    if(textInput->caret.type == HORIZONTAL)
    {
      if(strlen(textInput->text.text) * 8 < textInput->widget.width - caretRect.w * 2)
      {
        textInput->caret.postion += 8;
        return true;
      }
    }
  }
  return false;
}

bool caveTextInputIsInsideBackSpaceEvent(CaveTextInput* textInput, SDL_MouseButtonEvent event)
{
  if (event.x >= textInput->widget.x
      && event.x <= textInput->widget.x + textInput->widget.width + textInput->widget.padding
      && event.y >= textInput->widget.y
      && event.y <= textInput->widget.y + textInput->widget.height + textInput->widget.padding)
  {
    if(strlen(textInput->text.text) >= 1)
    {
      textInput->caret.postion -= 8;
    }
    return true;
  }
  return false;
}

bool caveTextInputIsInsideHoverEvent(CaveTextInput* textInput, SDL_MouseMotionEvent event)
{
  if (event.x >= textInput->widget.x
      && event.x <= textInput->widget.x + textInput->widget.width + textInput->widget.padding
      && event.y >= textInput->widget.y
      && event.y <= textInput->widget.y + textInput->widget.height + textInput->widget.padding)
  {
    return true;
  }
  return false;
}

//------------- Event Handlers -------------//
int textInputTextInputHandler()
{
  if(caveTextInputIsInsideAppendCharEvent(textInput, app->lastCycleMouseButtonEvent))
  {
    textInput->incomingChar = *app->lastCycleTextInputEvent.text;
    textInput->text.text = (char*)realloc(textInput->text.text, strlen(textInput->text.text) + 1);
    if (NULL == textInput->text.text)
    {
      SDL_Log("Failed to reallocate memory\n");
    }
    textInput->text.text[strlen(textInput->text.text)] = textInput->incomingChar;
    if(NULL != textInput->onCharAppend)
    {
      textInput->onCharAppend();
    }
    //txtInputTest.text[strlen(txtInputTest.text) + 1] = '\0';
  }
  return EXIT_SUCCESS;
}

int txtInputTestBackSpaceHandler()
{
  if(caveTextInputIsInsideBackSpaceEvent(textInput, app->lastCycleMouseButtonEvent))
  {
    if(NULL != textInput->onBackSpace)
    {
      textInput->onBackSpace();
    }
    if(strlen(textInput->text.text) > 0)
    {
      textInput->text.text[strlen(textInput->text.text) - 1] = '\0';
    }
    else
    {
      if(NULL != textInput->onEmpty)
      {
        textInput->onEmpty();
      }
    }
  }
  return EXIT_SUCCESS;
}

int textInputHoverHandler()
{
  if(caveTextInputIsInsideHoverEvent(textInput, app->lastCycleMouseMotionEvent))
  {
    // for external logics
    if(NULL != textInput->onHovered)
    {
      textInput->onHovered(app->lastCycleMouseMotionEvent.x, app->lastCycleMouseMotionEvent.y);
    }

    // for internal logic
    textInput->widget.hover.isHovered = true;
  }
  else
  {
    textInput->widget.hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

//------------- Borders -------------//
void textInputCreateLeftBorder()
{
  SDL_Rect rect = {0};
  if(textInput->widget.border.style == ALL)
  {
    rect.x = textInput->widget.x - textInput->widget.border.width;
    rect.y = textInput->widget.y - textInput->widget.border.height;
    rect.w = textInput->widget.border.width;
    rect.h = textInput->widget.height + textInput->widget.padding + (2 * textInput->widget.border.height);
  }
  else
  {
   rect.x = textInput->widget.x - textInput->widget.border.width;
   rect.y = textInput->widget.y;
   rect.w = textInput->widget.border.width;
   rect.h = textInput->widget.height + textInput->widget.padding;
  }
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateRightBorder()
{
  SDL_Rect rect = {0};
  if(textInput->widget.border.style == ALL)
  {
    rect.x = textInput->widget.x + textInput->widget.width + textInput->widget.padding;
    rect.y = textInput->widget.y - textInput->widget.border.height;
    rect.w = textInput->widget.border.width;
    rect.h = textInput->widget.height + textInput->widget.padding + (2 * textInput->widget.border.height);
  }
  else
  {
    rect.x = textInput->widget.x + textInput->widget.width + textInput->widget.padding;
    rect.y = textInput->widget.y;
    rect.w = textInput->widget.border.width;
    rect.h = textInput->widget.height + textInput->widget.padding;
  }
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateTopBorder()
{
  SDL_Rect rect = {
    textInput->widget.x,
    textInput->widget.y - textInput->widget.border.height,
    textInput->widget.width + textInput->widget.padding,
    textInput->widget.border.height
  };
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateBottomBorder()
{
  SDL_Rect rect = {
    textInput->widget.x ,
    textInput->widget.y + textInput->widget.height + textInput->widget.padding,
    textInput->widget.width + textInput->widget.padding,
    textInput->widget.border.height
  };
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateAllBorder()
{
  textInputCreateLeftBorder();
  textInputCreateRightBorder();
  textInputCreateTopBorder();
  textInputCreateBottomBorder();
}

int textInputCreate()
{
  uint8_t red, green, blue, alpha;
  if (textInput->widget.hover.isHovered)
  {
    hexToRGBA(textInput->text.hover.color, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(textInput->widget.hover.color, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;

    hexToRGBA(textInput->widget.border.hover.color, &red, &green, &blue, &alpha);
    textInputBorderColor.r = red;
    textInputBorderColor.g = green;
    textInputBorderColor.b = blue;
    textInputBorderColor.a = alpha;
  }
  else
  {
    hexToRGBA(textInput->text.color, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(textInput->widget.color, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;

    hexToRGBA(textInput->widget.border.color, &red, &green, &blue, &alpha);
    textInputBorderColor.r = red;
    textInputBorderColor.g = green;
    textInputBorderColor.b = blue;
    textInputBorderColor.a = alpha;
  }

  SDL_Surface* surface = NULL;
  if (!strlen(textInput->text.text))
  {
    // set the caretPostion to 8
    textInput->caret.postion = 8;

    // Optionally, you can create a blank surface with a default size
    surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 1, SDL_PIXELFORMAT_RGBA32);
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
    surface = TTF_RenderText_Solid(app->widget.font.TTFFont, textInput->text.text, textColor);
    if (!surface)
    {
      SDL_Log("Failed to create surface(TTF_RenderText_Solid): %s", TTF_GetError());
      SDL_FreeSurface(surface);
      return EXIT_FAILURE;
    }
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
    textInput->widget.x,
    textInput->widget.y,
    textInput->widget.width + textInput->widget.padding,
    textInput->widget.height + textInput->widget.padding
  };
  SDL_SetRenderDrawColor(app->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  // caret rectangle
  if(VERTICAL == textInput->caret.type)
  {
    caretRect.x = textInput->widget.x + textInput->caret.postion - 4;
    caretRect.y = textInput->widget.y + (textInput->widget.padding / 2);
    caretRect.w = 1;
    caretRect.h = textInput->widget.height - (textInput->widget.padding / 2);
  }
  else
  {
    caretRect.x = textInput->widget.x + textInput->caret.postion - 4;
    caretRect.y = textInput->widget.y * 2 - textInput->widget.padding / 2;
    caretRect.w = 8;
    caretRect.h = 1;
  }
  SDL_SetRenderDrawColor(app->renderer, textColor.r, textColor.g, textColor.b, textColor.a);
  SDL_RenderFillRect(app->renderer, &caretRect);

  //SDL_Log("surface.w: %d", surface->w);
  //SDL_Log("surface.h: %d", surface->h);

  // text rectangle
  SDL_Rect textRect = {
    textInput->widget.x + textInput->widget.padding / 2,
    textInput->widget.y + textInput->widget.padding / 2,
    surface->w,
    surface->h
  };

  //SDL_Rect textRect = {
  //  textInput->x + (textInput->width - surface->w) / 2 + textInput->padding / 2,
  //  textInput->y + (textInput->height - surface->h) / 2 + textInput->padding / 2,
  //  surface->w,
  //  surface->h
  //};

  SDL_RenderCopy(app->renderer, texture, NULL, &textRect);

  // create border
  switch(textInput->widget.border.style)
  {
    case LEFT:
      textInputCreateLeftBorder();
      break;
    case RIGHT:
      textInputCreateRightBorder();
      break;
    case TOP:
      textInputCreateTopBorder();
      break;
    case BOTTOM:
      textInputCreateBottomBorder();
      break;
    case ALL:
      textInputCreateAllBorder();
      break;
    default:
      SDL_Log("ERROR -> unknown border style");
      break;
  }

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}

int textInputCreateWidget()
{
  if(EXIT_SUCCESS == textInputCreate())
  {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int textInputInit(CaveTextInput* txtInput)
{
  textInput = txtInput;
  registerCallBackFunction(&app->hoverHandler, textInputHoverHandler);
  registerCallBackFunction(&app->backSpaceHandler, txtInputTestBackSpaceHandler);
  registerCallBackFunction(&app->textInputHandler, textInputTextInputHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, textInputCreateWidget);

  if( EXIT_FAILURE == addWidget(app, TEXTINPUT, textInput->widget.UID, &textInput))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
