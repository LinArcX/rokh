#ifndef CAVE_APP_H
#define CAVE_APP_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../lib/util.h"
#include "widget.h"

#define CAVE_MAX_WIDGETS 10000

typedef struct
{
  struct
  {
    char bg[8];
  } window;

  struct
  {
    char bg[8];
    char border[8];
    char text[8];
    struct
    {
      char bg[8];
      char border[8];
      char text[8];

    } hover;
  } label;

  struct
  {
    char bg[8];
    char border[8];
    char text[8];
    struct
    {
      char bg[8];
      char border[8];
      char text[8];

    } hover;
  } button;

  struct
  {
    char bg[8];
    char border[8];
    char text[8];
    struct
    {
      char bg[8];
      char border[8];
      char text[8];

    } hover;
  } textInput;

} CaveTheme;

typedef struct
{
  SDL_Window* window;
  SDL_Renderer* renderer;

  bool isRunnig;
  uint16_t renderLoopDelay; // we need this delay, unless we'll face a high cpu usage. a number between 40 and 80 is ok.

  int numWidgets;
  CaveWidget widget;
  CaveWidget widgets[CAVE_MAX_WIDGETS];
  CaveTheme theme;

  Node* hoverHandler;
  Node* selectionHandler;

  Node* textInputHandler;

  Node* keyboardHandler;
  Node* backSpaceHandler;

  Node* leftClickDownHandler;
  Node* leftClickUpHandler;
  Node* rightClickDownHandler;
  Node* rightClickUpHandler;

  Node* widgetCreatorHandler;
  Node* widgetPositionChangedHandler;

  SDL_Event            lastCycleEvent;
  SDL_WindowEvent      lastCycleWindowEvent;

  SDL_KeyboardEvent    lastCycleKeyboardEvent;
  SDL_KeyboardEvent    lastCycleKeyboardBackSpaceEvent;

  SDL_MouseButtonEvent lastCycleMouseButtonEvent;
  SDL_MouseMotionEvent lastCycleMouseMotionEvent;

  SDL_TextInputEvent   lastCycleTextInputEvent;
  SDL_TextEditingEvent lastCycleTextEditingEvent;
} CaveApp;

extern CaveApp* app;

int initialize(int (*initWidgets)(void));
int render();
void cleanup();
int addWidget(CaveApp* app, int widgetType, char* UID, void* widget);
void setTheme(uint8_t themeType);

#endif
