#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6

short redrawScreen = 1;
u_int color = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount++;
  /*
  if(++secCount == 250){
    secCount = 0;
    color = (color == COLOR_GREEN) ? COLOR_PINK : COLOR_GREEN;
    //redrawScreen = 1;
    }*/
  if (secCount == 250 & switch_state_down == 0){
    // redrawScreen = 1;
    secCount = 0;
  }
  else if ( secCount != 250 && switch_state_down == 1){
    secCount = 0;
    //redrawScreen = 1;
  }
  
  else if (secCount != 250 && switch_state_down ==2){
     secCount = 0;
    //redrawScreen = 1;
  }
  else if(secCount != 250 && switch_state_down == 3){
    secCount = 0;
    // redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;

  configureClocks();
  lcd_init();
  init_buzzer();
  switch_init(15);
  // toggle_green();

  enableWDTInterrupts();
  or_sr(0x8);
  clearScreen(COLOR_BLACK);

  //horizontal, vertical
  drawString11x16(5, 10, "B1 find", color, COLOR_BLUE);
  drawString11x16(5, 30, "Nemo", color, COLOR_BLUE);
  
  drawString11x16(5, 55, "B2 find", color, COLOR_BLUE);
  drawString11x16(5, 75, "Dory", color, COLOR_BLUE);

  
  drawString11x16(5, 100, "B3 shape", color, COLOR_BLUE);
  drawString5x7(20, 150, "B4 end", color, COLOR_BLUE);
  while(1){
     state_advance();
  }
  
  /*
  while(1){
   

    
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
	break;
      case 4:
	clearScreen(COLOR_YELLOW);
	//horizontal, vertical
       drawString11x16(5, 10, "B1 find", color, COLOR_BLUE);
       drawString11x16(5, 30, "Nemo", color, COLOR_BLUE);
  
       drawString11x16(5, 55, "B2 find", color, COLOR_BLUE);
       drawString11x16(5, 75, "Dory", color, COLOR_BLUE);

  
        drawString11x16(5, 100, "B3 shape", color, COLOR_BLUE);
        drawString5x7(20, 150, "B4 start over", color, COLOR_BLUE);
	break;
      default:
	redrawScreen = 0;
	break;
      }
  */
  P1OUT &= ~LED_GREEN; //green_off
  or_sr(0x10); // CPU off
  P1OUT |= LED_GREEN; //green on
    //}
}
