#include <stddef.h>

#include "app.h"
#include "textInput.h"

SDL_Color textInputBorderColor = {0};
extern App* app;
TextInput* textInput = NULL;

//------------- Region detection -------------//
bool caveTextInputIsInsideAppendCharEvent(TextInput* textInput, SDL_MouseButtonEvent event)
{
  if (event.x >= textInput->x
      && event.x <= textInput->x + textInput->width + textInput->padding
      && event.y >= textInput->y
      && event.y <= textInput->y + textInput->height + textInput->padding)
  {
    SDL_Log("txtInput size append: %zu", strlen(textInput->text));

   if(strlen(textInput->text) * 8 < textInput->width)
   {
    textInput->caretPostion += 8;
   }

    return true;
  }
  return false;
}

bool caveTextInputIsInsideBackSpaceEvent(TextInput* textInput, SDL_MouseButtonEvent event)
{
  if (event.x >= textInput->x
      && event.x <= textInput->x + textInput->width + textInput->padding
      && event.y >= textInput->y
      && event.y <= textInput->y + textInput->height + textInput->padding)
  {
    SDL_Log("txtInput size backspace: %zu", strlen(textInput->text));

    if(strlen(textInput->text) >= 1)
    {
      textInput->caretPostion -= 8;
    }
    return true;
  }
  return false;
}

bool caveTextInputIsInsideHoverEvent(TextInput textInput, SDL_MouseMotionEvent event)
{
  return false;
}

//------------- Event Handlers -------------//
int txtInputTestTextInputHandler()
{
  if(caveTextInputIsInsideAppendCharEvent(textInput, app->lastCycleMouseButtonEvent))
  {
    textInput->incomingChar = *app->lastCycleTextInputEvent.text;
    textInput->text = (char*)realloc(textInput->text, strlen(textInput->text) + 1);
    if (NULL == textInput->text)
    {
      SDL_Log("Failed to reallocate memory\n");
    }
    textInput->text[strlen(textInput->text)] = textInput->incomingChar;
    //txtInputTest.text[strlen(txtInputTest.text) + 1] = '\0';
  }
  return EXIT_SUCCESS;
}

int txtInputTestBackSpaceHandler()
{
  if(caveTextInputIsInsideBackSpaceEvent(textInput, app->lastCycleMouseButtonEvent))
  {
    if(strlen(textInput->text) > 0)
    {
      textInput->text[strlen(textInput->text) - 1] = '\0';
    }
  }
  return EXIT_SUCCESS;
}

int txtInputTestHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= textInput->x
      && app->lastCycleMouseMotionEvent.x <= textInput->x + textInput->width + textInput->padding
      && app->lastCycleMouseMotionEvent.y >= textInput->y
      && app->lastCycleMouseMotionEvent.y <= textInput->y + textInput->height + textInput->padding)
  {
    textInput->hover.isHovered = true;
  }
  else
  {
    textInput->hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

//------------- Borders -------------//
void textInputCreateLeftBorder()
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
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateRightBorder()
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
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateTopBorder()
{
  SDL_Rect rect = {
    textInput->x,
    textInput->y - textInput->border.height,
    textInput->width + textInput->padding,
    textInput->border.height
  };
  SDL_SetRenderDrawColor(app->renderer, textInputBorderColor.r, textInputBorderColor.g, textInputBorderColor.b, textInputBorderColor.a);
  SDL_RenderFillRect(app->renderer, &rect);
}

void textInputCreateBottomBorder()
{
  SDL_Rect rect = {
    textInput->x ,
    textInput->y + textInput->height + textInput->padding,
    textInput->width + textInput->padding,
    textInput->border.height
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

// SDL_Renderer* renderer, TTF_Font* font,
int textInputCreate()
{
  uint8_t red, green, blue, alpha;

  hexToRGBA(textInput->textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(textInput->backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(textInput->border.color, &red, &green, &blue, &alpha);
  textInputBorderColor.r = red;
  textInputBorderColor.g = green;
  textInputBorderColor.b = blue;
  textInputBorderColor.a = alpha;

  if (textInput->hover.isHovered)
  {
    hexToRGBA(textInput->hover.textColor, &red, &green, &blue, &alpha);
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
    textColor.a = alpha;

    hexToRGBA(textInput->hover.backgroundColor, &red, &green, &blue, &alpha);
    backgroundColor.r = red;
    backgroundColor.g = green;
    backgroundColor.b = blue;
    backgroundColor.a = alpha;
  }

  SDL_Surface* surface = NULL;
  if (!strlen(textInput->text))
  {
    // set the caretPostion to 8
    textInput->caretPostion = 8;

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
    surface = TTF_RenderText_Solid(app->font, textInput->text, textColor);
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
  SDL_Rect backgroundRect = { textInput->x, textInput->y, textInput->width + textInput->padding, textInput->height + textInput->padding };
  SDL_SetRenderDrawColor(app->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  // caret rectangle
  SDL_Rect caretRect = { textInput->x + textInput->caretPostion + 1, textInput->y + textInput->padding, 1, textInput->height - textInput->padding };
  SDL_SetRenderDrawColor(app->renderer, textColor.r, textColor.g, textColor.b, textColor.a);
  SDL_RenderFillRect(app->renderer, &caretRect);

  //SDL_Log("surface.w: %d", surface->w);
  //SDL_Log("surface.h: %d", surface->h);


  // text rectangle
  SDL_Rect textRect = { textInput->x + textInput->padding / 2, textInput->y + textInput->padding / 2, surface->w, surface->h};//textInput.width, textInput.height };
  SDL_RenderCopy(app->renderer, texture, NULL, &textRect);

  // create border
  switch(textInput->border.style)
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

void textInputInit(TextInput* txtInput)
{
  textInput = txtInput;
  registerCallBackFunction(&app->hoverHandler, txtInputTestHoverHandler);
  registerCallBackFunction(&app->backSpaceHandler, txtInputTestBackSpaceHandler);
  registerCallBackFunction(&app->textInputHandler, txtInputTestTextInputHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, textInputCreateWidget);
}

//int textInputInit(SDL_Renderer* renderer, TTF_Font* font, TextInput textInput)
//{
//}
