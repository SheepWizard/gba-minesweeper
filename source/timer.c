#include "timer.h"

volatile static u32 decisecond = 0;

IWRAM_CODE volatile void timer_irq()
{
  decisecond++;
  REG_IF = IRQ_TIMER0; // Acknowledge the interrupt
}

u32 get_timer()
{
  return decisecond;
}

void stop_timer()
{
  REG_TM0CNT = 0;
}

void start_timer()
{
  decisecond = 0;
  REG_TM0CNT = 0;          // Stop Timer 0
  REG_TM0D = -0x4000 / 10; // Load the timer with the value for 1ms (assuming 16.78 MHz clock and /1024 prescaler)
  REG_TM0CNT = TM_ENABLE | TM_IRQ | TM_FREQ_1024;
  REG_ISR_MAIN = timer_irq;
  REG_IE |= IRQ_TIMER0;
  REG_IME = 1; // Tell the GBA to enable interrupts;
}