/* 
 * File:   App_inversor.h
 * Author: flavio.luciano
 *
 * Created on January 26, 2022, 1:50 PM
 */

#ifndef APP_INVERSOR_H
#define	APP_INVERSOR_H
#include "mcc_generated_files/system.h"

void App_Inversor_Init(void);
void App_Inversor_Run(void);
void App_inversor_Frequencia_60(uint8_t state);
void App_Inversor_ContaTempo(uint8_t tempo);

void App_inversor_leituraKeyboard(void);
void App_Inversor_KeyBoard(void);

void Zera_tickStart(void);


void App_Inversor_GravaMemoria(void);
void App_Inversor_LerMemoria(void);

void App_Inversor_PiscaDisplay(uint16_t valor);

void App_Inversor_ConfigTime_1(void);
void App_Inversor_ConfigTime_2(void);
void App_Inversor_ConfigTime_3(void);
void App_invensor_Controller(void);

void App_inversor_Frequencia_45(uint8_t state);
void App_inversor_Frequencia_75(uint8_t state); 

void App_inversor_Frequencia_0(uint8_t state); 

int gerar_frequencia( uint8_t freq);

void media_leituraAD_temperatura(void);

void media_leituraAD_Corrente(void);


#endif	/* APP_INVERSOR_H */

