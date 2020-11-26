
#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012

static char state = 0;
static char sb = 1;

char toggle_red() // will make red led turn on
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}
char green_blink() //green will blink only
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


char toggle_green() //will make green led turn on
{
  green_on = 1;
  red_on - 0;
  led_changed = 1;
  led_update();
}

char alternate(){ // switch between both
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  switch(color){
  case R: changed = red_blink(); color = G; break;
  case G: changed = green_blink(); color = R; break;
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
void buzzer() //song1
{
  int letters[] = {C4,D4,F4,G4,B4}; //notes of song

  int i = 0;
  while(i <sizeof(letters)){ // move across notes
    int count = 0;
    while(count < 20){
      int count2 = 0;
      while(count2 < 30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(letters[i]);
    i++;
  }
}
