/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33EP128MC204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/reset_types.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/tmr2.h"
#include "App_inversor.h"
/*
                         Main application
 */



//void DSP_Numero0(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetHigh();
//    SEG_F_SetHigh();
//    SEG_G_SetLow();
//}
//
//void DSP_Numero1(void) {
//    SEG_A_SetLow();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetLow();
//    SEG_E_SetLow();
//    SEG_F_SetLow();
//    SEG_G_SetLow();
//}
//
//void DSP_Numero2(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetLow();
//    SEG_D_SetHigh();
//    SEG_E_SetHigh();
//    SEG_F_SetLow();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero3(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetLow();
//    SEG_F_SetLow();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero4(void) {
//    SEG_A_SetLow();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetLow();
//    SEG_E_SetLow();
//    SEG_F_SetHigh();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero5(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetLow();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetLow();
//    SEG_F_SetHigh();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero6(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetLow();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetHigh();
//    SEG_F_SetHigh();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero7(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetLow();
//    SEG_E_SetLow();
//    SEG_F_SetLow();
//    SEG_G_SetLow();
//}
//
//void DSP_Numero8(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetHigh();
//    SEG_F_SetHigh();
//    SEG_G_SetHigh();
//}
//
//void DSP_Numero9(void) {
//    SEG_A_SetHigh();
//    SEG_B_SetHigh();
//    SEG_C_SetHigh();
//    SEG_D_SetHigh();
//    SEG_E_SetLow();
//    SEG_F_SetHigh();
//    SEG_G_SetHigh();
//}
//
//void DSP_DigitoApagado(void) {
//    SEG_A_SetLow();
//    SEG_B_SetLow();
//    SEG_C_SetLow();
//    SEG_D_SetLow();
//    SEG_E_SetLow();
//    SEG_F_SetLow();
//    SEG_G_SetLow();
//}
//
//typedef enum {
//    zero = 0,
//    um,
//    dois,
//    tres,
//    quatro,
//    cinco,
//    seis,
//    sete,
//    oito,
//    nove,
//} DSP_Numeros_e;
//
//typedef enum {
//    stateOff = 0,
//    stateOn,
//} DSP_StateDisplay_e;
//
//typedef void (*ptrFunctionCaracter)(void);
//
//typedef struct {
//    char caracter;
//    ptrFunctionCaracter arrayCaracter[10];
//    void(*desligar)(void);
//} Digito_t;
//
//typedef struct {
//    uint8_t digito;
//    Digito_t arrayDigitos[2];
//    DSP_StateDisplay_e stateDisplay;
//} Display_t;
//
//typedef void (*ptrFunctionStateMultiplexDisplay)(Display_t *display);
//
//typedef struct {
//    ptrFunctionStateMultiplexDisplay mchStateMultiplexDisplay[2];
//    Display_t display;
//} Inversor_t;
//
//Inversor_t inversor;
//
//void Inversor_DisplayRun(void);
//void Inversor_DisplayOn(Display_t *display);
//void Inversor_DisplayOff(Display_t *display);

int main(void) {

//    int i;;
//    for (i = 0; i < 2; i++) {
//        inversor.display.arrayDigitos[i].arrayCaracter[0] = DSP_Numero0;
//        inversor.display.arrayDigitos[i].arrayCaracter[1] = DSP_Numero1;
//        inversor.display.arrayDigitos[i].arrayCaracter[2] = DSP_Numero2;
//        inversor.display.arrayDigitos[i].arrayCaracter[3] = DSP_Numero3;
//        inversor.display.arrayDigitos[i].arrayCaracter[4] = DSP_Numero4;
//        inversor.display.arrayDigitos[i].arrayCaracter[5] = DSP_Numero5;
//        inversor.display.arrayDigitos[i].arrayCaracter[6] = DSP_Numero6;
//        inversor.display.arrayDigitos[i].arrayCaracter[7] = DSP_Numero7;
//        inversor.display.arrayDigitos[i].arrayCaracter[8] = DSP_Numero8;
//        inversor.display.arrayDigitos[i].arrayCaracter[9] = DSP_Numero9;
//        inversor.display.arrayDigitos[i].desligar = DSP_DigitoApagado;
//    }
//    inversor.display.stateDisplay = stateOff;
//    inversor.display.digito = 0;
//    inversor.display.arrayDigitos[0].caracter = 0;
//    inversor.display.arrayDigitos[1].caracter = 0;
//    inversor.mchStateMultiplexDisplay[0] = Inversor_DisplayOff;
//    inversor.mchStateMultiplexDisplay[1] = Inversor_DisplayOn;

    // initialize the device
    SYSTEM_Initialize();
    App_Inversor_Init();    
    
    

    //    PWM_DutyCycleSet(PWM_GENERATOR_1, 0x7FFF); // UH / UL;
    //    PWM_DutyCycleSet(PWM_GENERATOR_2, 0x7FFF); // VH / VL
    //    PWM_DutyCycleSet(PWM_GENERATOR_3, 0x7FFF); // WH / WL

    while (1) {
        
        App_Inversor_Run();
    }
    return 1;
}


//
//void Inversor_DisplayRun(void) {
//    if (inversor.mchStateMultiplexDisplay[inversor.display.stateDisplay] != 0) {
//        inversor.mchStateMultiplexDisplay[inversor.display.stateDisplay](&inversor.display);
//    }
//}
//
//void Inversor_DisplayOn(Display_t *display) {
//    uint8_t digito = display->digito;
//    uint8_t caracter = display->arrayDigitos[digito].caracter;
//    display->arrayDigitos[digito].arrayCaracter[caracter]();
//    if (digito == 0) {
//        DSP_1_SetHigh();
//        DSP_2_SetLow();
//        display->digito = 1;
//    } else if (digito == 1) {
//        DSP_1_SetLow();
//        DSP_2_SetHigh();
//        display->digito = 0;
//    }
//    display->stateDisplay = stateOff;
//}
//
//void Inversor_DisplayOff(Display_t *display) {
//    uint8_t digito = display->digito;
//    display->arrayDigitos[digito].desligar();
//    DSP_1_SetLow();
//    DSP_2_SetLow();
//    display->stateDisplay = stateOn;
//}

/**
 End of File
 */

