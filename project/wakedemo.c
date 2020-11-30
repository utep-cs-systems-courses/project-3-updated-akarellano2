#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  if(++secCount ==125){
    state_advance();
    secCount =  0;
    redrawScreen = 1;
  }

  if(secCount ==10 && switch_state_changed == 2){
    state_advance();
    secCount = 0;
    redrawScreen = 1;
  }
  else if(secCount == 30 && switch_state_changed ==4){
    state_advance();
    secCount = 0;
    redrawScreen = 1;
  }
}
  /*
  secCount ++;
  if (secCount == 250) {		/* once/sec 
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    }*/

  

void main()
{
  configureClocks();
  led_init();
  //lcd_init();
  
  buzzer_init();
  switch_init();
  enableWDTInterrupts();

  or_sr(0x10);
  
  P2DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P2OUT |= LED_GREEN;
  configureClocks();
  //lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  //clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      
    }
    P2OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P2OUT |= LED_GREEN;		/* green on */
  }
}

    
    



