#include "app.h"

#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// #FF7043 #FF8A65 #66BB6A #A5D6A7 #1E1E1E #262626 #212121 #9E9E9E #8a919c #9c9891 #8a919c #616161 #BDBDBD #DADADA #FAFAFA

App* app;

int windowPositionChangeHandler()
{
  app->widget.x = app->lastCycleWindowEvent.data1;
  app->widget.y = app->lastCycleWindowEvent.data2;

  SDL_Log("Window moved to (%d, %d)\n", app->widget.x, app->widget.y);
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

  app->widget.font.TTFFont = NULL;
  app->widget.font.size = 14;
  app->widget.font.name = "monaco.ttf"; //CourierPrime.ttf, FantasqueSansMono.ttf

  app->widget.x = 0;
  app->widget.y = 0;
  app->widget.width = 800;
  app->widget.height = 600;
  app->widget.color = "#969696";

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
  if (TTF_Init() < 0)
  {
    printf("SDL_ttf initialization failed. SDL_ttf Error: %s\n", TTF_GetError());
    return EXIT_FAILURE;
  }

  app->widget.font.TTFFont = TTF_OpenFont(app->widget.font.name, app->widget.font.size);
  if (app->widget.font.TTFFont == NULL)
  {
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
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  app->window= SDL_CreateWindow("Cave Sample",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    app->widget.width,
    app->widget.height,
    SDL_WINDOW_SHOWN);
  if (app->window == NULL)
  {
    printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  app->renderer= SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (app->renderer == NULL)
  {
    printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if(EXIT_FAILURE == initFont())
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int initialize(int (*initWidget)(void))
{
  initApp();

  if(EXIT_FAILURE == initSDL())
  {
    return EXIT_FAILURE;
  }

  if( EXIT_FAILURE == initWidget())
  {
    return EXIT_FAILURE;
  }
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
    hexToRGBA(app->widget.color, &red, &green, &blue, &alpha);

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
  TTF_CloseFont(app->widget.font.TTFFont);
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
  if (app->numWidgets < MAX_WIDGETS)
  {
    CaveWidget newWidget;
    if(isWidgetExisted(UID))
    {
      SDL_Log("Widget:[%s] already exists! ", UID);
      return EXIT_FAILURE;
    }
    else
    {
      newWidget.type = widgetType;
      newWidget.UID = UID;
      newWidget.widgetPtr = widget;
      app->widgets[app->numWidgets++] = newWidget;
      return EXIT_SUCCESS;
    }
  }
  SDL_Log("You've added widgets more than MAX_WIDGETS[%d]", MAX_WIDGETS);
  return EXIT_FAILURE;
}
