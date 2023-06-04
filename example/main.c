#include "../lib/app.h"
#include "lblTest.h"
#include "btnTest.h"
#include "txtInputTest.h"

void initWidgets()
{
  lblTestInit();
  btnTestInit();
  txtInputTestInit();
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
