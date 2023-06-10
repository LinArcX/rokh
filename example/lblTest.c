#include "lblTest.h"
#include "../lib/app.h"

CaveLabel lblTest;

int lblTestInit()
{
  lblTest.widget.UID = "lblTest";
  lblTest.widget.x = 20;
  lblTest.widget.y = 20;
  lblTest.widget.radius = 1;
  lblTest.widget.width = 50;
  lblTest.widget.height = 20;
  lblTest.widget.padding = 6;
  lblTest.text.text = "Name: ";

  if(EXIT_FAILURE == labelInit(&lblTest))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
