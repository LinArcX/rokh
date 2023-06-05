#include "app.h"
#include "util.h"

#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

App* app;

int windowPositionChangeHandler()
{
  app->x = app->lastCycleWindowEvent.data1;
  app->y = app->lastCycleWindowEvent.data2;

  SDL_Log("Window moved to (%d, %d)\n", app->x, app->y);
  return EXIT_SUCCESS;
}

int windowKeyboardHandler()
{
  if (app->lastCycleKeyboardEvent.keysym.sym == SDLK_F4 && (app->lastCycleKeyboardEvent.keysym.mod & KMOD_ALT))
  {
    app->isRunnig = false;
  }
  return EXIT_SUCCESS;
}

//------------- Initialization -------------//
void initApp()
{
  app = malloc(sizeof(App));

  app->window = NULL;
  app->renderer = NULL;

  app->font = NULL;
  app->fontSize = 14;
  app->fontName = "monaco.ttf"; //CourierPrime.ttf, FantasqueSansMono.ttf

  app->x = 0;
  app->y = 0;
  app->width = 800;
  app->height = 600;
  app->backgroundColor = "#757575";// #262626

  app->isRunnig = true;
  app->renderLoopDelay = 40;

  app->hoverHandler = NULL;
  app->selectionHandler = NULL;

  app->textInputHandler = NULL;

  app->keyboardHandler = NULL;
  app->backSpaceHandler = NULL;

  app->leftClickUpHandler = NULL;
  app->leftClickDownHandler = NULL;
  app->rightClickUpHandler = NULL;
  app->rightClickDownHandler = NULL;

  app->widgetCreatorHandler = NULL;
  app->widgetPositionChangedHandler = NULL;

  registerCallBackFunction(&app->keyboardHandler, windowKeyboardHandler);
  registerCallBackFunction(&app->widgetPositionChangedHandler, windowPositionChangeHandler);
}

int initFont()
{
  if (TTF_Init() < 0) {
      printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  app->font = TTF_OpenFont(app->fontName, app->fontSize);
  if (app->font == NULL) {
      printf("Font loading failed. SDL_ttf Error: %s\n", TTF_GetError());
      return EXIT_FAILURE;
  }

  // Enable text anti-aliasing
  if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
  {
    printf("Warning: Failed to enable anti-aliasing\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int initSDL()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->window= SDL_CreateWindow("Galaxy of Nodes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->width, app->height, SDL_WINDOW_SHOWN);
  if (app->window == NULL) {
      printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  app->renderer= SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (app->renderer == NULL) {
      printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  if(EXIT_FAILURE == initFont())
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int initialize(void (*initWidget)(void))
{
  initApp();

  if(EXIT_FAILURE == initSDL())
  {
    return EXIT_FAILURE;
  }

  initWidget();
  return EXIT_SUCCESS;
}

//------------- Rendering -------------//
int render()
{
  SDL_Event event;

  while (app->isRunnig)
  {
    while (SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          {
            app->isRunnig = false;
          } break;
        case SDL_KEYUP:
          break;
        case SDL_KEYDOWN:
          {
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
              //int mouseX, mouseY;
              //SDL_GetMouseState(&app->mouse_x, &app->mouse_y);
              app->lastCycleKeyboardBackSpaceEvent = event.key;
              callFunctions(app->backSpaceHandler);
            }
            else
            {
              app->lastCycleKeyboardEvent = event.key;
              callFunctions(app->keyboardHandler);
            }
          } break;
        case SDL_TEXTINPUT:
          {
            app->lastCycleTextInputEvent = event.text;
            callFunctions(app->textInputHandler);
          } break;
        case SDL_MOUSEBUTTONDOWN:
          {
            app->lastCycleMouseButtonEvent = event.button;
            if (event.button.button == SDL_BUTTON_LEFT)
            {
              callFunctions(app->leftClickDownHandler);
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
              callFunctions(app->rightClickDownHandler);
            }
          } break;
        case SDL_MOUSEBUTTONUP:
          {
            app->lastCycleMouseButtonEvent = event.button;
            if (event.button.button == SDL_BUTTON_LEFT)
            {
              callFunctions(app->leftClickUpHandler);
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
              callFunctions(app->rightClickUpHandler);
            }
          } break;
        case SDL_MOUSEMOTION:
          {
            app->lastCycleMouseMotionEvent = event.motion;
            callFunctions(app->hoverHandler);
          } break;
        case SDL_MOUSEWHEEL:
          break;
        case SDL_WINDOWEVENT:
          {
            if (event.window.event == SDL_WINDOWEVENT_MOVED)
            {
              app->lastCycleWindowEvent = event.window;
              callFunctions(app->widgetPositionChangedHandler);
            }
          } break;
        default:
          break;
      }
    }

    uint8_t red, green, blue, alpha;
    hexToRGBA(app->backgroundColor, &red, &green, &blue, &alpha);

    SDL_SetRenderDrawColor(app->renderer, red, green, blue, alpha);
    SDL_RenderClear(app->renderer);

    if(EXIT_FAILURE == callFunctions(app->widgetCreatorHandler))
    {
      return EXIT_FAILURE;
    }

    SDL_RenderPresent(app->renderer);
    SDL_Delay(app->renderLoopDelay);
  }
  return EXIT_SUCCESS;
}

//------------- CleanUp -------------//
void cleanup()
{
  TTF_CloseFont(app->font);
  TTF_Quit();

  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_Quit();

  freeCallBackFunctionList(app->hoverHandler);

  freeCallBackFunctionList(app->leftClickDownHandler);
  freeCallBackFunctionList(app->leftClickUpHandler);
  freeCallBackFunctionList(app->rightClickDownHandler);
  freeCallBackFunctionList(app->rightClickUpHandler);

  freeCallBackFunctionList(app->keyboardHandler);
  freeCallBackFunctionList(app->textInputHandler);

  freeCallBackFunctionList(app->widgetCreatorHandler);
  freeCallBackFunctionList(app->widgetPositionChangedHandler);

  free(app);
  app = NULL;
}


int addWidget(App* app, int widgetType, char* UID, void* widget)
{
  if (app->numWidgets < MAX_WIDGETS) {
    Widget newWidget;
    newWidget.type = widgetType;
    newWidget.UID = UID;
    newWidget.widgetPtr = widget;
    app->widgets[app->numWidgets++] = newWidget;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void printWidgets(App* app)
{
  printf("Number of widgets: %d\n", app->numWidgets);
  for (int i = 0; i < app->numWidgets; i++)
  {
    Widget* widget = &(app->widgets[i]);
    printf("Type: %d, UID: %s\n", i, widget->UID);
    //switch (widget->type)
    //{
    //  case BUTTON:
    //    break;
    //  case LABEL:
    //    printf("Type: %d: Label\n", i);
    //    break;
    //  case TEXTINPUT:
    //    printf("Type: %d: TextInput\n", i);
    //    break;
    //  default:
    //    printf("Type: %d: Unknown\n", i);
    //    break;
    //}
  }
}
