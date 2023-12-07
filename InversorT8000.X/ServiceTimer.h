/* 
 * File:   ServiceTimer.h
 * Author: flavio.luciano
 *
 * Created on October 1, 2020, 10:35 AM
 */

#ifndef SERVICETIMER_H
#define	SERVICETIMER_H

#include <stdint.h>
#include <stdbool.h>

void SRV_TIMER_Init(void);
void SRV_TIMER_Run(void);
void SRV_TIMER_TickInterrupt(void);
uint32_t SRV_TIMER_GetTick(void);

void ServiceCoreTime_Interrupt(void);


#endif	/* SERVICETIMER_H */

