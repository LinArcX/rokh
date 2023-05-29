#include "app.h"
#include "btnAdd.h"
#include "txtInputTest.h"
#include <string.h>
#include "../lib/util.h"

TextInput txtInputTest;

//------------- Event Handlers -------------//
void txtInputTestHoverHandler()
{
  if(textInputIsInside_MouseMotionEvent(txtInputTest, app->lastCycleMouseMotionEvent))
  {
    txtInputTest.hover.isHovered = true;
    return;
  }
  txtInputTest.hover.isHovered = false;
}

void txtInputTestBackSpaceHandler()
{
  if(textInputIsInside_MouseButtonEvent(txtInputTest, app->lastCycleMouseButtonEvent))
  {
    if(strlen(txtInputTest.text) > 0)
    {
      txtInputTest.text[strlen(txtInputTest.text) - 1] = '\0';
    }
  }
}

void txtInputTestTextInputHandler()
{
  if(textInputIsInside_MouseButtonEvent(txtInputTest, app->lastCycleMouseButtonEvent))
  {
    txtInputTest.incomingChar = *app->lastCycleTextInputEvent.text;
    txtInputTest.text = (char*)realloc(txtInputTest.text, strlen(txtInputTest.text) + 1);
    if (NULL == txtInputTest.text)
    {
      SDL_Log("Failed to reallocate memory\n");
    }
    txtInputTest.text[strlen(txtInputTest.text)] = txtInputTest.incomingChar;
    //txtInputTest.text[strlen(txtInputTest.text) + 1] = '\0';
  }
}

//------------- Widget Creation -------------//
void txtInputTestCreateTestWidget()
{
  textInputCreate(app->renderer, app->font, txtInputTest);
}

//------------- Setup/Initialization -------------//
void txtInputTestInitProperties()
{
  txtInputTest.x = btnAdd.x + btnAdd.width + btnAdd.padding + 10;
  txtInputTest.y = 20;
  txtInputTest.radius = 1;
  txtInputTest.padding = 2;
  txtInputTest.width = 200;
  txtInputTest.height = 20;
  txtInputTest.backgroundColor = "#DADADA"; //#262626

  txtInputTest.text = malloc(1);
  memset(txtInputTest.text, ' ', 1);
  txtInputTest.textColor = "#262626"; //#DADADA, #FAFAFA

  txtInputTest.hover.isHovered = false;
  txtInputTest.hover.textColor = "#212121";
  txtInputTest.hover.borderColor = "#212121";
  txtInputTest.hover.backgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  txtInputTest.border.style = ALL;
  txtInputTest.border.color = "#616161";
  txtInputTest.border.width = 2;
  txtInputTest.border.height = 2;
}

void txtInputTestSetupCallbackFunctions()
{
  registerCallBackFunction(&app->hoverHandler, txtInputTestHoverHandler);
  registerCallBackFunction(&app->backSpaceHandler, txtInputTestBackSpaceHandler);
  registerCallBackFunction(&app->textInputHandler, txtInputTestTextInputHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, txtInputTestCreateTestWidget);
}

void TxtInputTestInit()
{
  txtInputTestInitProperties();
  txtInputTestSetupCallbackFunctions();
}
