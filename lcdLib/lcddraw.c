/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}
/* will draw figure of fish */
void drawFish(u_char col, u_char row,  u_int colorBGR, u_char center)
{
  
  u_char r;
  u_char c; 
 
  //tail for fish, two triangles combined
  for(r = center; r > 0; r--){
    for(c = center; c>=r; c--){
      drawPixel(col + c, row+ r, colorBGR);// bottom tail
      drawPixel(col + c, row-r+1, colorBGR); // top tail
    }
  }

  //body of the fish
  fillRectangle(col-(center*2-center/2),row-center/2,center*2, center, colorBGR);
  //eye of the fish
  fillRectangle(col-center-center/4, row-center/4, center/4, center/4, COLOR_BLACK);
  //fin of fish
  for(r = center/2; r > 0; r--){
    for(c = center/2; c>=r; c--){
      drawPixel(col/2 + c, row+center/4+ r, COLOR_RED);// bottom tail
    }
  } 
}

void drawDiamond(u_char col, u_char row, u_char center, u_int colorBGR)
{
  u_char r;
  u_char c;

  //top part of the diamond
  for(r = 0; r< center; r++){
    for(c = 0; c < r; c++){
      drawPixel(center+col + c, row+r, colorBGR);
      drawPixel(center+col - c,row+r, colorBGR);
    }  
  }

  for(c = 0; c < center; c++){
    for(r = center; r < center*2 -c; r++){
      drawPixel(center+col + c,row+r, colorBGR);
      drawPixel(center+col - c,row+r, colorBGR);
    }
  }
  
}
/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01; 
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

void drawChar11x16(u_char rcol, u_char rrow, char c, // what will draw each letter
	      u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x0001; //shortens the character vertically, the bigger the number 
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 10, rrow + 16);
  while(row < 17){
    while( col < 11){
      u_int colorBGR = (font_11x16[oc][col] &bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<=1;
    row++;
  }
}


/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawString11x16(u_char col, u_char row, char *string, // made from method drawString5x7
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar11x16(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 12;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

