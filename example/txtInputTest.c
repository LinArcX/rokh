#include "app.h"
#include "btnAdd.h"
#include "txtInputTest.h"
#include <string.h>
#include "../lib/util.h"

TextInput txtInputTest;

void txtInputTestTextInputHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= txtInputTest.x
      && app->lastCycleMouseButtonEvent.x <= txtInputTest.x + txtInputTest.width + txtInputTest.padding
      && app->lastCycleMouseButtonEvent.y >= txtInputTest.y
      && app->lastCycleMouseButtonEvent.y <= txtInputTest.y + txtInputTest.height + txtInputTest.padding)
  {
    txtInputTest.newChar = *app->lastCycleTextInputEvent.text;
    txtInputTest.text = (char*)realloc(txtInputTest.text, strlen(txtInputTest.text) + 1);
    if (NULL == txtInputTest.text)
    {
      SDL_Log("Failed to reallocate memory\n");
    }
    txtInputTest.text[strlen(txtInputTest.text)] = txtInputTest.newChar;
    //txtInputTest.text[strlen(txtInputTest.text) + 1] = '\0';
  }
}

void txtInputTestBackSpaceHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= txtInputTest.x
      && app->lastCycleMouseButtonEvent.x <= txtInputTest.x + txtInputTest.width + txtInputTest.padding
      && app->lastCycleMouseButtonEvent.y >= txtInputTest.y
      && app->lastCycleMouseButtonEvent.y <= txtInputTest.y + txtInputTest.height + txtInputTest.padding)
  {
    if(strlen(txtInputTest.text) > 0)
    {
      txtInputTest.text[strlen(txtInputTest.text) - 1] = '\0';
    }
  }
}

void textInputCreateTestWidget()
{
  textInputCreate(app->renderer, app->font, txtInputTest);
}

void initTxtInputTest()
{
  // initialize
  txtInputTest.x = btnAdd.x + btnAdd.width + btnAdd.padding + 10;
  txtInputTest.y = 20;
  txtInputTest.radius = 1;
  txtInputTest.width = 200;
  txtInputTest.height = 20;
  txtInputTest.padding = 2;
  txtInputTest.backgroundColor = "#DADADA"; //#262626

  txtInputTest.text = malloc(1);
  memset(txtInputTest.text, ' ', 1);
  //txtInputTest.text = " ";
  txtInputTest.textColor = "#212121"; //#DADADA, #FAFAFA
                                      //
  txtInputTest.isHovered = false;
  txtInputTest.hoverText = "";
  txtInputTest.hoverTextColor = "#212121";
  txtInputTest.hoverBackgroundColor = "#A5D6A7"; //#FF7043, #FF8A65, #66BB6A, #1E1E1E

  txtInputTest.borderColor = "#616161";
  txtInputTest.borderStyle = ALL;
  txtInputTest.borderDefaultWidth = 2;
  txtInputTest.borderDefaultHeight = 2;

  // setup callback functions
  registerCallBackFunction(&app->backSpaceHandler, txtInputTestBackSpaceHandler);
  registerCallBackFunction(&app->textInputHandler, txtInputTestTextInputHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, textInputCreateTestWidget);
}

  //int lengthText = strlen(txtInputTest.text);
  //txtInputTest.text = (char*)realloc(txtInputTest.text, lengthText + strlen(txtInputTest.newText) + 1);
  //
  //  //for(size_t i = 0; i < strlen(txtInputTest.newText); i++)
  //{
  //  txtInputTest.text[lengthText + i] = txtInputTest.newText[i];
  //}
  //
  //  //txtInputTest.newText = malloc(1);
  //memset(txtInputTest.newText, ' ', 1);
