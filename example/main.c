#include "../lib/app.h"

#include "lblTest.h"
#include "btnTest.h"
#include "lstBoxTest.h"
#include "txtInputTest.h"

extern CaveApp* app;

int initWidgets()
{
  if(EXIT_FAILURE == lblTestInit())
  {
    return EXIT_FAILURE;
  }
  if(EXIT_FAILURE == btnTestInit())
  {
    return EXIT_FAILURE;
  }
  if(EXIT_FAILURE == txtInputTestInit())
  {
    return EXIT_FAILURE;
  }
  //if(EXIT_FAILURE == lstBoxTestInit())
  //{
  //  return EXIT_FAILURE;
  //}
  return EXIT_SUCCESS;
}

int main()
{
  app = malloc(sizeof(CaveApp));
  app->widget.x = 0;
  app->widget.y = 0;
  app->widget.width = 1000;
  app->widget.height = 600;
  app->widget.font.size = 12;
  app->widget.font.name = "monaco.ttf"; // "CourierPrime.ttf", "FantasqueSansMono.ttf"
  app->renderLoopDelay = 40;
  setTheme(THEME_GRUVBOX);

  if (EXIT_FAILURE == initialize(initWidgets))
  {
    return EXIT_FAILURE;
  }

  if (EXIT_FAILURE == render())
  {
  return EXIT_FAILURE;
  }

  cleanup();
  return EXIT_SUCCESS;
}
