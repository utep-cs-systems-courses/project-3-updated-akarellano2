#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

void
{
  __interrupt_vec(WDT_VECTOR) WDT(){ /*250 interrupts per second */

    static char blink_count = 0;

    if((++blink_count == 60) && s2){
      buzzer();
      blink_count = 0;
    }
  }
