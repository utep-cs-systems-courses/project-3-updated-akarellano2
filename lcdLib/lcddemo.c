/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  drawString11x16(20,100, "hello", COLOR_GREEN, COLOR_RED); // first num x axis, 2nd y axis
  /*
  u_char x;
  for(x = 0; x<70; x++){
    drawPixel(0, 40, COLOR_RED);
    }*/
  
  drawFish(50,40, COLOR_ORANGE,30);// col, row, color, center
  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  drawDiamond(0, 70, 15, COLOR_WHITE);
}
