/* 
 * File:   Driver_InversorPWM.h
 * Author: flavio.luciano
 *
 * Created on January 26, 2022, 1:52 PM
 */

#ifndef DRIVER_INVERSORPWM_H
#define	DRIVER_INVERSORPWM_H

#include "mcc_generated_files/system.h"

void controle_inversor(uint8_t state, uint16_t freq);
void setDefazagem(uint16_t def);
void fase1(uint8_t frequencia);
void fase2(uint8_t frequencia);
void fase3(uint8_t frequencia);

void setDesligaClearPWM();

#endif	/* DRIVER_INVERSORPWM_H */

