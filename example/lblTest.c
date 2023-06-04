#include "lblTest.h"
#include "../lib/app.h"

Label lblTest;

int lblTestInit()
{
  lblTest.x = 20;
  lblTest.y = 20;
  lblTest.radius = 1;
  lblTest.width = 50;
  lblTest.height = 20;
  lblTest.padding = 4;
  lblTest.text = "Name: ";
  lblTest.textColor = "#FAFAFA";
  lblTest.backgroundColor = app->backgroundColor;
  return EXIT_SUCCESS;
}
