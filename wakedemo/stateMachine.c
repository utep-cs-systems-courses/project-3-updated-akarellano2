#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#define C4 1911
#define D4 1703
#define B4 1012

//int color = COLOR_GREEN;
//#include "functionsDraw.h"

static int state = 0;

char toggle = 0; //on or off
char times = 0; //times led is on
void fish()
{
  
  switch(state){

  case 0:
    clearScreen(COLOR_BLUE);
    drawFish(40,50, COLOR_ORANGE, 20);
    state = 1;
     break;
  case 1:
    clearScreen(COLOR_BLUE);
    drawFish(50,50, COLOR_ORANGE, 20);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_BLUE);
    drawFish(60,50, COLOR_ORANGE, 20);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_BLUE);
    drawFish(70, 50, COLOR_ORANGE, 20);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_BLUE);
    drawFish(80, 50, COLOR_ORANGE, 20);
    state = 1;
    break;
  }
}

void fish2()
{
  
  switch(state){

  case 0:
    clearScreen(COLOR_RED);
    drawFish(40,50, COLOR_BLUE, 20);
    state = 1;
     break;
  case 1:
    clearScreen(COLOR_RED);
    drawFish(50,50, COLOR_BLUE, 20);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_RED);
    drawFish(60,50, COLOR_BLUE, 20);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_RED);
    drawFish(70, 50, COLOR_BLUE, 20);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_RED);
    drawFish(80, 50, COLOR_BLUE, 20);
    state = 1;
    break;
  }
}

void changeColor()
{
  
  switch(state){
  case 1:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20,20, COLOR_RED);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20, 20, COLOR_YELLOW);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20,20, COLOR_BLUE);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20,20, COLOR_BLACK);
    state = 1;
    break;
  }
}

void buzzer()
{
  static char next  = 0;

  switch(next){
  case 1:
    buzzer_set_period(C4);
    next++;
    break;
  case 2:
    buzzer_set_period(B4);
    next++;
    break;
  case 3:
    buzzer_set_period(D4);
    next++;
    break;
  default:
    next++;
    break;
  }
}

void toggle_green_led()
{
  if(times < 70){
    times++;
    toggle = toggle_green(toggle);
    led_update;
  }
  else{
    times = 0;
  }
}

void state_advance()
{
  static char next_state;

  switch(switch_state_down){
      case 1:
        fish();
	break;
      case 2:
	
	fish2();
	buzzer();
	break;
      case 3:
        changeColor();
	//toggle_green_led();
	break;
      case 4:
	toggle_green_led();
	//changeColor();
	/*clearScreen(COLOR_YELLOW);
	  drawString11x16(5, 100, "BYE", COLOR_RED, COLOR_BLUE);*/
	//horizontal, vertical
      	break;
  }
}

    








    
/*    
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

void dim25(){ //dim light to 25 %
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 0;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 0;
    dimState = 3;
  case 3:
    red_on = 1;
    dimState = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim50(){ // dim light 50 %
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 1;
    dimState = 3;
    break;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim75(){ //dim light 75%
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 1;
    dimState = 2;
    break;
  case 2:
    red_on = 1;
    dimState = 3;
    break;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_changed = 1;
  led_update();
}
*/
