/* 
 * File:   Driver_Display.h
 * Author: flavio.luciano
 *
 * Created on 2 de Fevereiro de 2022, 08:06
 */

#ifndef DRIVER_DISPLAY_H
#define	DRIVER_DISPLAY_H

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/system_types.h"
#include "mcc_generated_files/mcc.h"


void DSP_Numero0(void);
void DSP_Numero1(void);
void DSP_Numero2(void);
void DSP_Numero3(void);
void DSP_Numero4(void);
void DSP_Numero5(void);
void DSP_Numero6(void);
void DSP_Numero7(void);
void DSP_Numero8(void);
void DSP_Numero9(void);
void DSP_DigitoApagado(void);
void DSP_Risco(void);


void display_Run(void);
void display_escreve(uint8_t valor);

#endif	/* DRIVER_DISPLAY_H */

