#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "../lcdLib/lcddraw.h"
#include "lcdutils.h"
#include "stateMachine.h"


int main(void) {
  configureClocks();
  led_init();
  lcd_init();
  
  buzzer_init();
  switch_init();
  enableWDTInterrupts();

  or_sr(0x18);
}
