#include "txtInputTest.h"

//#include "../lib/app.h"
#include "../lib/util.h"

#include "btnTest.h"
#include <string.h>

TextInput txtInputTest;

void txtInputTestInit()
{
  txtInputTest.x = btnTest.x + btnTest.width + btnTest.padding + 10;
  txtInputTest.y = 20;
  txtInputTest.width = 200;
  txtInputTest.height = 20;
  txtInputTest.radius = 1;
  txtInputTest.padding = 2;
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

  textInputInit(&txtInputTest);
}
