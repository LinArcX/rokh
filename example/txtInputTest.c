#include "txtInputTest.h"
#include "btnTest.h"
#include <string.h>

CaveTextInput txtInputTest;

void txtInputTestOnCharAppend()
{
  SDL_Log("[%s.OnCharAppend] size: %zu", txtInputTest.widget.UID, strlen(txtInputTest.text.text));
}

void txtInputTestOnBackSpace()
{
  SDL_Log("[%s.OnBackSpace] size: %zu", txtInputTest.widget.UID, strlen(txtInputTest.text.text));
}

void txtInputTestOnEmpty()
{
  SDL_Log("[%s.OnEmpty] size: %zu", txtInputTest.widget.UID, strlen(txtInputTest.text.text));
}

int txtInputTestInit()
{
  txtInputTest.widget.UID = "txtInputTest";
  txtInputTest.widget.x = btnTest.widget.x + btnTest.widget.width + btnTest.widget.padding + 10;
  txtInputTest.widget.y = btnTest.widget.y;
  txtInputTest.widget.width = 200;
  txtInputTest.widget.height = btnTest.widget.height;
  txtInputTest.widget.radius = 1;
  txtInputTest.widget.padding = 6;
  txtInputTest.widget.hover.isHovered = false;
  txtInputTest.widget.border.style = ALL;
  txtInputTest.widget.border.width = 2;
  txtInputTest.widget.border.height = 2;

  txtInputTest.text.text = malloc(1); //memset(txtInputTest.text, 0, 1);
  txtInputTest.caret.type = HORIZONTAL;

  txtInputTest.onEmpty = txtInputTestOnEmpty;
  txtInputTest.onBackSpace = txtInputTestOnBackSpace;
  txtInputTest.onCharAppend = txtInputTestOnCharAppend;

  if(EXIT_FAILURE == textInputInit(&txtInputTest))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
