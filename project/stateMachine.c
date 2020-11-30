
#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"
#include "../lcdLib/lcdutils.h"
#include "../lcdLib/lcddraw.h"

#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012

static char state = 0;
static char sb = 1;
/*
char toggle_red() // will make red led turn on
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
} 
*/        
char toggle_green() //green will blink only
{
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;
 
}

char red_blink() // red light will blink
{
  static char state = 0;
  switch(state){

  case 0:
    green_on = 1;
    // red_on = 0;
    state = 1;
    break;
  case 1:
    // green_on = 0;
    green_on = 0;
    state = 0;
    break;
  }
  return 1;
}

void diamond_colors()
{
  static char change_color = 0;
  switch(change_color = 0){
  case 0:
    drawDiamond(40, 40, 20, COLOR_PINK);
    change_color++;
    break;
  case 1:
    drawDiamond(40, 40, 20, COLOR_GREEN);
    change_color++;
    break;
  case 2:
    drawDiamond(40, 40, 20, COLOR_BLUE);
    change_color++;
    break;
  case 3:
    drawDiamond(40, 40, 20, COLOR_ORANGE);
    change_color = 0;
    break;
  }
}

/*
char toggle_green() //will make green led turn on
{
  green_on = 1;
  red_on - 0;
  led_changed = 1;
  led_update();
}
*/

char alternate(){ // switch between both
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  switch(color){
  case R: changed = red_blink(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  led_changed = changed;
  led_update();
}

/*
char alternate_led() // will make both alternate
{
  switch(state){

  case 0:
    toggle_red();
    state = 1; //advancing state
    break;

  case 1:
    toggle_green();
    state = 0;
    break;
  }
}
*/
