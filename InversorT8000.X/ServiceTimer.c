#include "ServiceTimer.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"

volatile uint32_t *count_aux = 0;

volatile uint32_t tickRate = 0;

void SRV_TIMER_Init(void)
{
    count_aux = &tickRate;
    TMR1_SetInterruptHandler(SRV_TIMER_TickInterrupt);
}

void SRV_TIMER_Run(void)
{
   
}

void SRV_TIMER_TickInterrupt(void)
{
    tickRate++;
}

uint32_t SRV_TIMER_GetTick(void)
{
    
    return *count_aux;
}

/*
void APP_Run()
{

	static uint32_t tick = 0;
	static uint32_t tickLast = 0;
	
	tick = SRV_TIMER_GetTick();
	if((uint32_t)(tick - tickLast) >= 250)
	{
		tickLast = tick;
		
		
	}
	
	APP_LeituraTempo();
	APP_AcionamentoRele();
	
}

void APP_LeituraTempo()
{
	static uint32_t tick = 0;
	static uint32_t tickLast = 0;
	
	tick = SRV_TIMER_GetTick();
	if((uint32_t)(tick - tickLast) >= 250)
	{
		tickLast = tick;
		
		
	}	

}
 * 
 */