#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "switches.h"

char B1, B2, B3, B4;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;

  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  B1 = (p2val & SW1) ? 0 : 1;
  B2 = (p2val & SW2) ? 0 : 1;
  B3 = (p2val & SW3) ? 0 : 1;
  B4 = (p2val & SW4) ? 0 : 1;

  if(B1){
    alternate();
    buzzer();
  }
  else if(B2){
    buzzer_set_period(0);
    green_blink();
  }
}


  
