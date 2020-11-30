#include <msp430.h>
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"
#include "lcdutils.h"
#include "libTimer.h"
#include "lcddraw.h"

void

  __interrupt_vec(WDT_VECTOR) WDT(){ /*250 interrupts per second */

    static char blink_count = 0;

    /*
    if((++blink_count == 60) && s2){
      buzzer();
      blink_count = 0;
      }*/

    if(++blink_count == 62 && switch_state_changed== 1){
      toggle_green();
      // buzzer_advance();
      blink_count = 0;
    }
    if(blink_count == 250 && switch_state_changed ==2){
      red_blink();
      clearScreen(COLOR_PINK);
    }
    if(blink_count ==250 && switch_state_changed == 3){
      alternate();
      diamond_colors();
      blink_count = 0;
    }
    if(switch_state_changed == 4){
      toggle_green();
      blink_count = 0;
    }
  }
  
