#ifndef CAVE_WIDGET_H
#define CAVE_WIDGET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef enum
{
  THEME_DEFAULT = 0,
  THEME_GRUVBOX,
} CaveThemeType;

typedef enum
{
  BUTTON = 0,
  LABEL,
  TEXTINPUT,
  POPUP,
  SLIDER
} CaveWidgetType;

typedef struct
{
  TTF_Font* TTFFont;
  uint8_t size;
  const char* name;
} CaveFont;

typedef enum
{
  LEFT = 0,
  RIGHT,
  TOP,
  BOTTOM,
  ALL
} CaveBorderStyle;

typedef struct
{
  bool isHovered;
} CaveHover;

typedef struct
{
  uint8_t width;
  uint8_t height;
  CaveHover hover;
  CaveBorderStyle style;
} CaveBorder;

typedef enum
{
  VERTICAL = 0,
  HORIZONTAL,
} CaveCaretType;

typedef struct
{
  CaveCaretType type;
  uint16_t postion;
} CaveCaret;

typedef struct
{
  bool isActive;
} CaveActive;

typedef struct
{
  char* text;
  CaveHover hover;
} CaveText;

typedef struct
{
  void* widgetPtr; // A pointer to the widget object (either button or label)
  CaveWidgetType type; // A value to indicate the type of widget (e.g., 0 for button, 1 for label)

  char* UID;
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
  uint8_t padding;
  int64_t radius;

  CaveFont font;
  CaveHover hover;
  CaveActive active;
  CaveBorder border;
} CaveWidget;

void printWidgets();
void setActiveWidget(const char* UID);
bool isWidgetExisted(const char* UID);
const char* widgetName(CaveWidgetType widgetType);

#endif
