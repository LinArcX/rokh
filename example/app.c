#include "app.h"
#include "lblAdd.h"
#include "btnAdd.h"
#include "txtInputTest.h"
#include "../lib/util.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

App* app;

void windowPositionChangeHandler(){
  SDL_Log("Window moved to (%d, %d)\n", app->x, app->y);
}

//------------- Initialization -------------//
void initApp()
{
  app = malloc(sizeof(App));

  app->window = NULL;
  app->renderer = NULL;

  app->font = NULL;
  app->fontName = "monaco.ttf"; //FantasqueSansMono
  app->fontSize = 14;

  app->x = 0;
  app->y = 0;
  app->mouse_x = 0;
  app->mouse_y = 0;
  app->width = 800;
  app->height = 600;
  app->backgroundColor = "#262626";// "#757575";

  app->hoverHandler = NULL;

  app->leftClickUpHandler = NULL;
  app->leftClickDownHandler = NULL;
  app->rightClickUpHandler = NULL;
  app->rightClickDownHandler = NULL;

  app->backSpaceHandler = NULL;
  app->textInputHandler = NULL;

  app->widgetCreatorHandler = NULL;
  app->widgetPositionChangedHandler = NULL;

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

int initialize()
{
  initApp();

  if(EXIT_FAILURE == initSDL())
  {
    return EXIT_FAILURE;
  }

  // init your widgets here
  initLblAdd();
  initBtnAdd();
  initTxtInputTest();

  return EXIT_SUCCESS;
}

//------------- Rendering -------------//
void render()
{
  int quit = 0;
  SDL_Event event;

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          {
            quit = 1;
          } break;
        case SDL_KEYDOWN:
          {
            if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_ALT))
            {
              quit = 1;
            }
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
              int mouseX, mouseY;
              SDL_GetMouseState(&app->mouse_x, &app->mouse_y);
              callFunctions(app->backSpaceHandler);
            }
          } break;
        case SDL_TEXTINPUT:
          {
            int mouseX, mouseY;
            SDL_GetMouseState(&app->mouse_x, &app->mouse_y);
            txtInputTest.newChar = *event.text.text;
            callFunctions(app->textInputHandler);
          } break;
        case SDL_MOUSEBUTTONDOWN:
          {
            app->mouse_x = event.button.x;
            app->mouse_y = event.button.y;

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
            app->mouse_x = event.button.x;
            app->mouse_y = event.button.y;

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
            app->mouse_x = event.motion.x;
            app->mouse_y = event.motion.y;
            callFunctions(app->hoverHandler);
          } break;
        case SDL_MOUSEWHEEL:
          break;
        case SDL_WINDOWEVENT:
          {
            if (event.window.event == SDL_WINDOWEVENT_MOVED)
            {
              app->x = event.window.data1;
              app->y = event.window.data2;
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

    callFunctions(app->widgetCreatorHandler);

    SDL_RenderPresent(app->renderer);
    // we need this delay, unless we'll face a high cpu usage. a number between 60 and 100 is ok.
    SDL_Delay(60);
  }
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

  freeCallBackFunctionList(app->backSpaceHandler);
  freeCallBackFunctionList(app->textInputHandler);

  freeCallBackFunctionList(app->widgetCreatorHandler);
  freeCallBackFunctionList(app->widgetPositionChangedHandler);

  free(app);
  app = NULL;
}

            //int len = strlen(txtInputTest.newText);
            //txtInputTest.newText = (char*)realloc(txtInputTest.newText, len + 1);
            //if (txtInputTest.newText == NULL) {
            //  SDL_Log("Failed to reallocate memory\n");
            //}

            //txtInputTest.newText[len] = *event.text.text;
            ////txtInputTest.newText[len + 1] = '\0';
