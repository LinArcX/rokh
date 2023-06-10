#include "../lib/app.h"
#include "lblTest.h"
#include "btnTest.h"
#include "txtInputTest.h"

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
  return EXIT_SUCCESS;
}

int main()
{
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
