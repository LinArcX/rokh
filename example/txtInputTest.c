#include "txtInputTest.h"
#include "btnTest.h"
#include <string.h>

TextInput txtInputTest;

void txtInputTestOnCharAppend()
{
  SDL_Log("[%s.OnCharAppend] size: %zu", txtInputTest.UID, strlen(txtInputTest.text));
}

void txtInputTestOnBackSpace()
{
  SDL_Log("[%s.OnBackSpace] size: %zu", txtInputTest.UID, strlen(txtInputTest.text));
}

void txtInputTestOnEmpty()
{
  SDL_Log("[%s.OnEmpty] size: %zu", txtInputTest.UID, strlen(txtInputTest.text));
}

void txtInputTestInit()
{
  txtInputTest.UID = "txtInputTest";
  txtInputTest.x = btnTest.x + btnTest.width + btnTest.padding + 10;
  txtInputTest.y = btnTest.y;
  txtInputTest.radius = 1;
  txtInputTest.padding = 6;
  txtInputTest.width = 200;
  txtInputTest.height = btnTest.height;
  txtInputTest.backgroundColor = "#DADADA"; //#262626

  txtInputTest.text = malloc(1);
  //memset(txtInputTest.text, 0, 1);
  txtInputTest.textColor = "#262626"; //#DADADA, #FAFAFA

  txtInputTest.hover.isHovered = false;
  txtInputTest.hover.textColor = "#212121";
  txtInputTest.hover.borderColor = "#212121";
  txtInputTest.hover.backgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  txtInputTest.border.style = ALL;
  txtInputTest.border.color = "#616161";
  txtInputTest.border.width = 2;
  txtInputTest.border.height = 2;

  txtInputTest.onEmpty = txtInputTestOnEmpty;
  txtInputTest.onBackSpace = txtInputTestOnBackSpace;
  txtInputTest.onCharAppend = txtInputTestOnCharAppend;

  textInputInit(&txtInputTest);
}
