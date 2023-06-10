#include "app.h"
#include "widget.h"

#include <stdlib.h>
#include <stdio.h>

void printWidgets()
{
  printf("Number of widgets: %d\n", app->numWidgets);
  for (int i = 0; i < app->numWidgets; i++)
  {
    CaveWidget* widget = &(app->widgets[i]);
    printf("Type: %s, UID: %s\n", widgetName(widget->type), widget->UID);
  }
}

void setActiveWidget(const char* UID)
{
  for (int i = 0; i < app->numWidgets; i++)
  {
    CaveWidget* widget = &(app->widgets[i]);
    if(widget->UID == UID)
    {
      widget->active.isActive = true;
    }
    else{
      widget->active.isActive = false;
    }
  }
}

bool isWidgetExisted(const char* UID)
{
  bool isExists = false;
  for (int i = 0; i < app->numWidgets; i++)
  {
    CaveWidget* widget = &(app->widgets[i]);
    if(widget->UID == UID)
    {
      isExists = true;
      break;
    }
  }
  return isExists;
}

const char* widgetName(CaveWidgetType widgetType)
{
  switch (widgetType)
  {
    case BUTTON: return "BUTTON";
    case LABEL: return "LABEL";
    case TEXTINPUT: return "TEXTINPUT";
    case POPUP: return "POPUP";
    case SLIDER: return "SLIDER";
  }
}
