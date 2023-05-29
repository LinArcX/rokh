#include <stddef.h>

#include "button.h"
#include "util.h"

SDL_Color borderColor = {0};

void CreateLeftBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {0};
  if(button->borderStyle == ALL)
  {
   rect.x = button->x - button->borderDefaultWidth;
   rect.y = button->y - button->borderDefaultHeight;
   rect.w = button->borderDefaultWidth;
   rect.h = button->height + button->padding + (2 * button->borderDefaultHeight);
  }
  else
  {
   rect.x = button->x - button->borderDefaultWidth;
   rect.y = button->y;
   rect.w = button->borderDefaultWidth;
   rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void CreateRightBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {0};
  if(button->borderStyle == ALL)
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y - button->borderDefaultHeight;
    rect.w = button->borderDefaultWidth;
    rect.h = button->height + button->padding + (2 * button->borderDefaultHeight);
  }
  else
  {
    rect.x = button->x + button->width + button->padding;
    rect.y = button->y;
    rect.w = button->borderDefaultWidth;
    rect.h = button->height + button->padding;
  }
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void CreateTopBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {
    button->x,
    button->y - button->borderDefaultHeight,
    button->width + button->padding,
    button->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void CreateBottomBorder(SDL_Renderer* renderer, const Button* button)
{
  SDL_Rect rect = {
    button->x ,
    button->y + button->height + button->padding,
    button->width + button->padding,
    button->borderDefaultHeight
  };
  SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
  SDL_RenderFillRect(renderer, &rect);
}

void CreateAllBorder(SDL_Renderer* renderer, const Button* button)
{
  CreateLeftBorder(renderer, button);
  CreateRightBorder(renderer, button);
  CreateTopBorder(renderer, button);
  CreateBottomBorder(renderer, button);
}

int createButton(SDL_Renderer* renderer, TTF_Font* font, Button button) {
  uint8_t red, green, blue, alpha;

  hexToRGBA(button.textColor, &red, &green, &blue, &alpha);
  SDL_Color textColor = { red, green, blue, alpha };

  hexToRGBA(button.backgroundColor, &red, &green, &blue, &alpha);
  SDL_Color backgroundColor = { red, green, blue, alpha };

  hexToRGBA(button.borderColor, &red, &green, &blue, &alpha);
  borderColor.r = red;
  borderColor.g = green;
  borderColor.b = blue;
  borderColor.a = alpha;

  if (button.isHovered)
  {
      hexToRGBA(button.hoverTextColor, &red, &green, &blue, &alpha);
      textColor.r = red;
      textColor.g = green;
      textColor.b = blue;
      textColor.a = alpha;

      hexToRGBA(button.hoverBackgroundColor, &red, &green, &blue, &alpha);
      backgroundColor.r = red;
      backgroundColor.g = green;
      backgroundColor.b = blue;
      backgroundColor.a = alpha;
  }

  // Create a surface from the rendered text
  SDL_Surface* surface = TTF_RenderText_Blended(font, button.text, textColor);

  if (!surface)
  {
      SDL_Log("Failed to create surface: %s", TTF_GetError());
      SDL_FreeSurface(surface);
      return EXIT_FAILURE;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture)
  {
      SDL_Log("Failed to create texture: %s", SDL_GetError());
      SDL_DestroyTexture(texture);
      return EXIT_FAILURE;
  }

  // background rectangle
  SDL_Rect backgroundRect = { button.x, button.y, button.width + button.padding, button.height + button.padding };
  SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(renderer, &backgroundRect);

  switch(button.borderStyle)
  {
    case LEFT:
      CreateLeftBorder(renderer, &button);
      break;
    case RIGHT:
      CreateRightBorder(renderer, &button);
      break;
    case TOP:
      CreateTopBorder(renderer, &button);
      break;
    case BOTTOM:
      CreateBottomBorder(renderer, &button);
      break;
    case ALL:
      CreateAllBorder(renderer, &button);
      break;
    default:
       SDL_Log("ERROR -> unknown border style");
      break;
  }

  // Create a destination rectangle for rendering the texture
  SDL_Rect textRect = { button.x + button.padding / 2, button.y + button.padding / 2, button.width, button.height };
  // Render the texture on the screen
  SDL_RenderCopy(renderer, texture, NULL, &textRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  return EXIT_SUCCESS;
}

  //// Render rounded corners
  //SDL_SetRenderDrawColor(app->renderer, 128, 128, 128, 125); // Set color to transparent
  //SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND);
  //SDL_Rect corners[4] = {
  //  { button.x, button.y, button.radius, button.radius },
  //  { button.x + button.width - button.radius, button.y, button.radius, button.radius },
  //  { button.x, button.y + button.height - button.radius, button.radius, button.radius },
  //  { button.x + button.width - button.radius, button.y + button.height - button.radius, button.radius, button.radius }
  //};
  //for (int i = 0; i < 4; i++)
  //{
  //  SDL_RenderFillRect(app->renderer, &corners[i]);
  //}



//void createButton()
//{
//
//}
//
//void generateNodes() {
//    //nodes[0].x = WINDOW_WIDTH / 4;
//    //nodes[0].y = WINDOW_HEIGHT / 2;
//    //sprintf(nodes[0].text, "Node 1");  // Set text for the first node
//
//    //nodes[1].x = (3 * WINDOW_WIDTH) / 4;
//    //nodes[1].y = WINDOW_HEIGHT / 2;
//    //sprintf(nodes[1].text, "Node 2");  // Set text for the second node
//    ////for (int i = 0; i < NUM_NODES; i++) {
//    ////    nodes[i].x = rand() % WINDOW_WIDTH;
//    ////    nodes[i].y = rand() % WINDOW_HEIGHT;
//    ////    sprintf(nodes[i].text, "Node %d", i);  // Set text for each node
//    ////}
//}

//int pointInsideRect(int x, int y, SDL_Rect rect) {
//    return (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h));
//}
//
//void renderNodes() {
//    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
//    SDL_RenderClear(renderer);
//
//    SDL_Color textColor = { 255, 255, 255, 255 };  // Color for the text
//
//    for (int i = 0; i < NUM_NODES; i++) {
//        int depth = 200 + (nodes[i].y * 55) / WINDOW_HEIGHT;  // Increase the depth range
//        SDL_SetRenderDrawColor(renderer, 130, 175, depth, 255);  // Set node color to blue
//
//        // Create a surface from the node's text
//        SDL_Surface* textSurface = TTF_RenderText_Solid(font, nodes[i].text, textColor);
//
//        // Render the node as a filled rectangle
//        SDL_Rect rect;
//        rect.w = nodeWidth + textSurface->w;
//        rect.h = nodeHeight + textSurface->h;
//        rect.x = nodes[i].x - (rect.w / 2);
//        rect.y = nodes[i].y - (rect.h / 2);
//
//        SDL_RenderFillRect(renderer, &rect);
//
//        if (textSurface != NULL)
//        {
//            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//            if (textTexture != NULL) {
//                // Set the position for rendering the text
//                SDL_Rect textRect;
//                textRect.x = nodes[i].x - textSurface->w / 2;
//                textRect.y = nodes[i].y - textSurface->h / 2;
//                textRect.w = textSurface->w;
//                textRect.h = textSurface->h;
//
//                // Render the text texture on the screen
//                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//
//                // Free the text texture
//                SDL_DestroyTexture(textTexture);
//            }
//
//            // Free the text surface
//            SDL_FreeSurface(textSurface);
//        }
//
//    }
//    // Render the line and arrow
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set line and arrow color to red
//
//    // Draw the line
//    SDL_RenderDrawLine(renderer, nodes[0].x + 30, nodes[0].y, nodes[1].x - 30, nodes[1].y);
//
//    // Calculate the position of the arrow
//    int arrowSize = 5;  // Size of the arrow
//    double angle = atan2(nodes[1].y - nodes[0].y, nodes[1].x - nodes[0].x);
//    int arrowX = nodes[1].x - arrowSize * cos(angle);
//    int arrowY = nodes[1].y - arrowSize * sin(angle);
//
//    // Draw the arrow
//    SDL_RenderDrawLine(renderer, nodes[1].x - 30, nodes[1].y, arrowX, arrowY);
//    SDL_RenderDrawLine(renderer, arrowX, arrowY, arrowX - arrowSize * cos(angle + M_PI_4), arrowY - arrowSize * sin(angle + M_PI_4));
//    SDL_RenderDrawLine(renderer, arrowX, arrowY, arrowX - arrowSize * cos(angle - M_PI_4), arrowY - arrowSize * sin(angle - M_PI_4));
//
//    SDL_RenderPresent(renderer);
//}
//
////Button button = {
//  .width = 800,
//  .height = 600,
//  .font = NULL,
//  .window = NULL,
//  .renderer = NULL
//};
//
