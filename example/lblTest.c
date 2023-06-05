#include "lblTest.h"
#include "../lib/app.h"

Label lblTest;

void lblTestInit()
{
  lblTest.UID = "lblTest";
  lblTest.x = 20;
  lblTest.y = 20;
  lblTest.radius = 1;
  lblTest.width = 50;
  lblTest.height = 20;
  lblTest.padding = 6;
  lblTest.text = "Name: ";
  lblTest.textColor = "#FAFAFA";
  lblTest.backgroundColor = app->backgroundColor;// "#1E1E1E"

  labelInit(&lblTest);
}
