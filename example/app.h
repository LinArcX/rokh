#ifndef _APP_H
#define _APP_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/util.h"

typedef struct SDLApp
{
  SDL_Window* window;
  SDL_Renderer* renderer;

  SDL_Event            lastCycleEvent;
  SDL_WindowEvent      lastCycleWindowEvent;

  SDL_KeyboardEvent    lastCycleKeyboardEvent;
  SDL_KeyboardEvent    lastCycleKeyboardBackSpaceEvent;

  SDL_MouseButtonEvent lastCycleMouseButtonEvent;
  SDL_MouseMotionEvent lastCycleMouseMotionEvent;

  SDL_TextInputEvent   lastCycleTextInputEvent;
  SDL_TextEditingEvent lastCycleTextEditingEvent;

  TTF_Font* font;
  const char* fontName;
  uint8_t fontSize;

  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;

  int mouse_x;
  int mouse_y;

  bool isRunnig;

  const char* backgroundColor;

  Node* hoverHandler;

  Node* leftClickDownHandler;
  Node* leftClickUpHandler;
  Node* rightClickDownHandler;
  Node* rightClickUpHandler;

  Node* keyboardHandler;
  Node* backSpaceHandler;
  Node* textInputHandler;

  Node* widgetCreatorHandler;
  Node* widgetPositionChangedHandler;
}App;

extern App* app;

int initialize();
void render();
void cleanup();

#endif
