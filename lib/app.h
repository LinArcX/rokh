#ifndef _APP_H
#define _APP_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/util.h"

typedef enum CaveWidgetType
{
  BUTTON = 0,
  LABEL,
  TEXTINPUT,
  POPUP,
  SLIDER
} WidgetType;

typedef struct {
    WidgetType type; // A value to indicate the type of widget (e.g., 0 for button, 1 for label)
    char* UID;
    void* widgetPtr; // A pointer to the widget object (either button or label)
} Widget;

#define MAX_WIDGETS 10

typedef struct SDLApp
{
   Widget widgets[MAX_WIDGETS];
   int numWidgets;

  SDL_Window* window;
  SDL_Renderer* renderer;

  TTF_Font* font;
  uint8_t fontSize;
  const char* fontName;

  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  const char* backgroundColor;

  bool isRunnig;
  uint16_t renderLoopDelay; // we need this delay, unless we'll face a high cpu usage. a number between 40 and 80 is ok.

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
}App;

extern App* app;

int initialize(void (*initWidgets)(void));
int render();
void cleanup();

int addWidget(App* app, int widgetType, char* UID, void* widget);
void printWidgets(App* app);

#endif
