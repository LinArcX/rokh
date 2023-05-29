#include "app.h"

int main()
{
  if (EXIT_FAILURE == initialize())
  {
    return EXIT_FAILURE;
  }

  render();

  cleanup();
  return EXIT_SUCCESS;
}
