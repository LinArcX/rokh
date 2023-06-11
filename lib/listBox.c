#include <stddef.h>

#include "listBox.h"
#include "app.h"
#include "label.h"
#include "util/convertor.h"

extern CaveApp* app;
CaveListBox* listBox = NULL;
SDL_Color listBoxBorderColor = {0};

//------------- Event Handlers -------------//
int listBoxlHoverHandler()
{
  if (app->lastCycleMouseMotionEvent.x >= listBox->widget.x
      && app->lastCycleMouseMotionEvent.x <= listBox->widget.x + listBox->widget.width + listBox->widget.padding
      && app->lastCycleMouseMotionEvent.y >= listBox->widget.y
      && app->lastCycleMouseMotionEvent.y <= listBox->widget.y + listBox->widget.height + listBox->widget.padding)
  {
    // for external logics
    if(NULL != listBox->onHovered)
    {
      listBox->onHovered(app->lastCycleMouseMotionEvent.x, app->lastCycleMouseMotionEvent.y);
    }

    // for internal logic
    listBox->widget.hover.isHovered = true;
  }
  else
  {
    listBox->widget.hover.isHovered = false;
  }
  return EXIT_SUCCESS;
}

int listBoxLeftClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= listBox->widget.x
      && app->lastCycleMouseButtonEvent.x <= listBox->widget.x + listBox->widget.width + listBox->widget.padding
      && app->lastCycleMouseButtonEvent.y >= listBox->widget.y
      && app->lastCycleMouseButtonEvent.y <= listBox->widget.y + listBox->widget.height + listBox->widget.padding)
  {
    if(NULL != listBox->onItemLeftClick)
    {
      listBox->onItemLeftClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }

    // Check if an item is clicked
    for (int i = listBox->top_item; i < listBox->top_item + listBox->visible_items; i++)
    {
      SDL_Rect itemRect = {
        listBox->widget.x,
        listBox->widget.y + (i - listBox->top_item) * listBox->widget.height,
        listBox->widget.width,
        listBox->widget.height };

      // Check if an item is clicked
      if (app->lastCycleMouseButtonEvent.x >= itemRect.x
          && app->lastCycleMouseButtonEvent.x < itemRect.x + itemRect.w
          && app->lastCycleMouseButtonEvent.y >= itemRect.y
          && app->lastCycleMouseButtonEvent.y < itemRect.y + itemRect.h)
      {
        listBox->selected_item = i;
        break;
      }
    }
  }
  return EXIT_SUCCESS;
}

int listBoxRightClickDownHandler()
{
  if (app->lastCycleMouseButtonEvent.x >= listBox->widget.x
      && app->lastCycleMouseButtonEvent.x <= listBox->widget.x + listBox->widget.width + listBox->widget.padding
      && app->lastCycleMouseButtonEvent.y >= listBox->widget.y
      && app->lastCycleMouseButtonEvent.y <= listBox->widget.y + listBox->widget.height + listBox->widget.padding)
  {
    if(NULL != listBox->onItemRightClick)
    {
      listBox->onItemRightClick(app->lastCycleMouseButtonEvent.x, app->lastCycleMouseButtonEvent.y);
    }
  }
  return EXIT_SUCCESS;
}

//CaveLabel lbl;
int listBoxCreate()
{
  uint8_t red, green, blue, alpha;

  // background rectangle
  SDL_Rect backgroundRect = {
    listBox->widget.x,
    listBox->widget.y,
    listBox->widget.width + listBox->widget.padding,
    listBox->widget.height + listBox->widget.padding
  };

  SDL_Color listBoxBgColor = {0};
  hexToRGBA(app->theme.listBox.bg, &red, &green, &blue, &alpha);
  listBoxBgColor.r = red;
  listBoxBgColor.g = green;
  listBoxBgColor.b = blue;
  listBoxBgColor.a = alpha;

  SDL_SetRenderDrawColor(app->renderer, listBoxBgColor.r, listBoxBgColor.g, listBoxBgColor.b, listBoxBgColor.a);
  SDL_RenderFillRect(app->renderer, &backgroundRect);

  return EXIT_SUCCESS;
}

int listBoxCreateWidget()
{
  if(EXIT_SUCCESS == listBoxCreate())
  {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int listBoxInit(CaveListBox* lstBox)
{
  listBox = lstBox;
  //registerCallBackFunction(&app->hoverHandler, listBoxlHoverHandler);
  //registerCallBackFunction(&app->leftClickDownHandler, listBoxLeftClickDownHandler);
  //registerCallBackFunction(&app->rightClickDownHandler, listBoxRightClickDownHandler);
  registerCallBackFunction(&app->widgetCreatorHandler, listBoxCreateWidget);


  // Render the items
  for (int i = listBox->top_item; i < listBox->top_item + listBox->visible_items && i < listBox->num_items; i++)
  {
    //lbl.widget.UID = concatStrings(listBox->widget.UID, intToString(i));
    //lbl.widget.width = listBox->widget.width;
    //lbl.widget.height = listBox->widget.height/2;
    ////lbl.widget.radius = 1;
    ////lbl.widget.padding = 2;
    //lbl.widget.x = listBox->widget.x + listBox->widget.padding / 2;
    //lbl.widget.y = listBox->widget.y + listBox->widget.padding / 2 + (i - listBox->top_item) * listBox->widget.height/2;

    listBox->items[i].widget.UID = concatStrings(listBox->widget.UID, intToString(i));
    listBox->items[i].widget.x = listBox->widget.x + listBox->widget.padding / 2;
    listBox->items[i].widget.y = listBox->widget.y + listBox->widget.padding / 2 + (i - listBox->top_item) * listBox->widget.height / 2;
    listBox->items[i].widget.width = 50;//listBox->widget.width;
    listBox->items[i].widget.height = 60;//listBox->widget.height / listBox->num_items;
    //listBox->items[0].widget.hover.isHovered = false;
    //listBox->items[0].text.text = "h";
    //listBox->items[0].text.hover.isHovered = false;

    if(EXIT_FAILURE == labelInit(&listBox->items[i]))
    {
      SDL_Log("[ERROR] listBoxCreate() --> labelInit() failed! ");
      return EXIT_FAILURE;
    }
    //if(EXIT_FAILURE == labelCreate())
    //{
    //  SDL_Log("[ERROR] listBoxCreate() --> labelCreate() failed! ");
    //  return EXIT_FAILURE;
    //}
  }


  if(EXIT_FAILURE == addWidget(app, LISTBOX, listBox->widget.UID, &listBox))
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

    //const char* tmp = intToString(i);
    //char* tmp2 = strcat(listBox->widget.UID, tmp);

    //if (i == listBox->selected_item)
    //{
    //  listBoxItemTextColor = listBoxItemSelectedColor;
    //}
    //// Render the background of the item
    //SDL_Rect itemRect =
    //{
    //  listBox->widget.x,
    //  listBox->widget.y + (i - listBox->top_item) * listBox->widget.height,
    //  listBox->widget.width,
    //  listBox->widget.height
    //};

    //SDL_Color listBoxItemsColor = {0};
    //hexToRGBA(app->theme.listBox.items, &red, &green, &blue, &alpha);
    //listBoxItemsColor.r = red;
    //listBoxItemsColor.g = green;
    //listBoxItemsColor.b = blue;
    //listBoxItemsColor.a = alpha;

    //SDL_SetRenderDrawColor(app->renderer, listBoxItemsColor.r, listBoxItemsColor.g, listBoxItemsColor.b, listBoxItemsColor.a);
    //SDL_RenderFillRect(app->renderer, &itemRect);

    //// Render the text of the item
    //SDL_Color listBoxItemTextColor = {0};
    //hexToRGBA(app->theme.listBox.text, &red, &green, &blue, &alpha);
    //listBoxItemTextColor.r = red;
    //listBoxItemTextColor.g = green;
    //listBoxItemTextColor.b = blue;
    //listBoxItemTextColor.a = alpha;

    //SDL_Color listBoxItemSelectedColor = {0};
    //hexToRGBA(app->theme.listBox.selected, &red, &green, &blue, &alpha);
    //listBoxItemSelectedColor.r = red;
    //listBoxItemSelectedColor.g = green;
    //listBoxItemSelectedColor.b = blue;
    //listBoxItemSelectedColor.a = alpha;

    //if (i == listBox->selected_item)
    //{
    //  listBoxItemTextColor = listBoxItemSelectedColor;
    //}
    //SDL_Surface* itemTextSurface = TTF_RenderText_Solid(app->widget.font.TTFFont, listBox->items[i], listBoxItemTextColor);
    //SDL_Texture* itemTextTexture = SDL_CreateTextureFromSurface(app->renderer, itemTextSurface);

    //SDL_Rect itemTextRect = { itemRect.x + 5, itemRect.y + 5, itemTextSurface->w, itemTextSurface->h };
    //SDL_RenderCopy(app->renderer, itemTextTexture, NULL, &itemTextRect);

    //SDL_FreeSurface(itemTextSurface);
    //SDL_DestroyTexture(itemTextTexture);
