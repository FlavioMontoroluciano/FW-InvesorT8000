#include "App_inversor.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/reset_types.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/mcc.h"

#include "Driver_Display.h"
#include "Driver_InversorPWM.h"
#include "ServiceTimer.h"

//#include "flash.h"


// Allocate and reserve a page of flash for this test to use.  The compiler/linker will reserve this for data and not place any code here.
static __prog__ uint8_t flashTestPage[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog), aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));


#define LimiteCiclo 20000
#define vTMR2 303

/*
 * medidas com divisão por 100 em 1Khz
 * RampaMAX = 4200;
 * RampaMIN = 3050; // 45 Hz
 * RampaMAX = 4200;
 * RampaMIN = 2200; // 60 Hz
 * RampaMAX = 4200;
 * RampaMIN = 1720; // 75 Hz
 */

#define setMax_45 7000
#define setMin_45 3050

#define setMax_60 7000
#define setMin_60 2200

#define setMax_75 7000
#define setMin_75 1720

typedef struct {
    bool CH1_click;
    bool CH1_click_10s;
    uint8_t CH1_clicked;

    bool CH2_click;
    bool CH2_click_10s;
    uint8_t CH2_clicked;


    bool CH3_click;
    bool CH3_click_10s;
    uint8_t CH3_clicked;

    bool CTA_click;
    uint8_t CTA_clicked;

} keyboard_t;

keyboard_t keyboard;

uint16_t RampaMAX = 30;
uint16_t RampaMIN = 10;

uint16_t valorHz = 30;
bool StartStop = false;
bool ligado = false;
bool fazendoRampa = false;
bool ligaDesliga = false;

uint16_t tempoLigado = 0;

uint16_t Time_T1 = 0;
uint16_t Time_T2 = 0;
uint16_t Time_T3 = 0;

uint16_t contCiclo = 0;

uint8_t SelecaoFreq = 45;


uint32_t flash_storage_address;
bool result;
uint32_t write_data[4];
uint32_t read_data[4];

bool configTime1 = false;
bool configTime2 = false;
bool configTime3 = false;

bool AtingiuLimite = false;

uint16_t IncFreq = 10000;

bool gravarCiclo = false;
bool gravarCicloOK = false;

uint32_t tickStart = 0;
uint32_t tickLastStart = 0;

uint8_t incdec = 1;

#define NUM_SAMPLES 3 // Número de amostras para calcular a média

// Variáveis para armazenar as amostras do ADC
uint16_t adcValues[4];
uint8_t sampleIndex = 0;
uint16_t mediaADC = 0;
bool lendoADC1 = false;

uint16_t leituraAD_corrente = 0;


#define PLL_OUTPUT_FREQUENCY 7370000UL
#define FCY (PLL_OUTPUT_FREQUENCY / 2)


void __delay_ms(uint32_t DelayCount);

void __delay_ms(uint32_t DelayCount)
{
  uint32_t StartTime = 0;                    // Start Time
  StartTime = SRV_TIMER_GetTick();        // Get CoreTimer value for StartTime
  while ( (uint32_t)(SRV_TIMER_GetTick() - StartTime) < DelayCount ) {};
}

// Tamanho da tabela de seno
#define TABELA_SENO_TAMANHO 256
// Frequência do Timer2 (Hz)
#define TIMER2_FREQUENCY 1000000 


void configurarFrequenciaTimer2(unsigned int frequencia_desejada) {
    unsigned int frequencia_clock = 30401250; // Frequência do clock do sistema
    unsigned int prescaler = 1; // Valor do prescaler desejado (no caso, 1:1)

    // Calcula o valor do registrador PR2 com base na frequência desejada
    unsigned int valor_pr2 = (frequencia_clock / (prescaler * frequencia_desejada)) - 1;

    // Configuração do timer TMR2
    TMR2 = 0x00; // Reinicia o timer
    PR2 = valor_pr2; // Define o valor do registrador PR2
    T2CON = 0x8000; // Configura os bits de controle do timer

    // Outras configurações necessárias para o seu sistema
   // if (TMR2_InterruptHandler == NULL) {
      //  TMR2_SetInterruptHandler(&TMR2_CallBack);
   // }
    IFS0bits.T2IF = false;
    IEC0bits.T2IE = true;
	
   // tmr2_obj.timerElapsed = false;
}
 

void gerar_asenoid(void) {
    if (StartStop){
        controle_inversor(1, valorHz);  
    }
    
}

void My_ISR(void) {
   // ADC1_SoftwareTriggerDisable(); // trigger next conversion
   // media_leituraAD_temperatura();       
}

void media_leituraAD_temperatura(void)
{
    static uint8_t stateAD = 0;  
    static uint16_t timeOutAD = 0;
    static uint16_t contCorrenteAD = 0;
     
    switch(stateAD)
    {
        case 0 :           
            ADC1_Enable();
            ADC1_ChannelSelect(AN6_Temperatura);
            stateAD = 1;
            break;
        case 1:
             ADC1_SoftwareTriggerEnable();
             stateAD = 2;
            break;
        case 2:
            ADC1_SoftwareTriggerDisable();
            stateAD = 3;
            break;
        case 3:
            if( ADC1_IsConversionComplete(AN6_Temperatura)){
              stateAD = 4;  
            }
            else{
                timeOutAD++;
                if(timeOutAD >= 3){
                   stateAD = 5; 
                } 
            }
            
            break;
        case 4:
            mediaADC = ADC1_ConversionResultGet(AN6_Temperatura);
            if(mediaADC < 502 && mediaADC > 0)
            {
              contCorrenteAD++;
              if ((contCorrenteAD >= 3)) 
              {              
                contCorrenteAD = 0;
                              
                ligaDesliga = false;             
                tempoLigado = 0;

                if(SelecaoFreq == 45)
                {
                   App_inversor_Frequencia_45(0);  
                }           
                else if(SelecaoFreq == 60)
                {
                  App_inversor_Frequencia_60(0);  
                }
                else if(SelecaoFreq == 75)
                {
                  App_inversor_Frequencia_75(0);  
                } 
                StartStop = false;    
                setDesligaClearPWM();
                PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_3, 0);    

              }
            }
            else{
               contCorrenteAD = 0; 
            }
            stateAD = 5; 
            break;
        case 5:
            ADC1_Disable();
            stateAD = 0;                    
            break;
    } 
    
    
    
}

void media_leituraAD_Corrente(void)
{
    static uint8_t stateAD = 0;  
    static uint16_t timeOutAD = 0;
    static uint16_t contCorrenteAD = 0;
     
    switch(stateAD)
    {
        case 0 :           
            ADC1_Enable();
            ADC1_ChannelSelect(AN2_corrente);
            stateAD = 1;
            break;
        case 1:
             ADC1_SoftwareTriggerEnable();
             stateAD = 2;
            break;
        case 2:
            ADC1_SoftwareTriggerDisable();
            stateAD = 3;
            break;
        case 3:
            if( ADC1_IsConversionComplete(AN2_corrente)){
              stateAD = 4;  
            }
            else{
                timeOutAD++;
                if(timeOutAD >= 3){
                   stateAD = 5; 
                } 
            }
            
            break;
        case 4:
            leituraAD_corrente = ADC1_ConversionResultGet(AN2_corrente);
            if(leituraAD_corrente >= 65)
            {
              contCorrenteAD++;
              if ((contCorrenteAD >= 3)) 
              {              
                contCorrenteAD = 0;
                              
                ligaDesliga = false;             
                tempoLigado = 0;
                
                PHASE1 = 0x1F40;
                PHASE2 = 0x1F40;
                PHASE3 = 0x1F40;

                if(SelecaoFreq == 45)
                {
                   App_inversor_Frequencia_45(0);  
                }           
                else if(SelecaoFreq == 60)
                {
                  App_inversor_Frequencia_60(0);  
                }
                else if(SelecaoFreq == 75)
                {
                  App_inversor_Frequencia_75(0);  
                } 
                    
                PHASE1 = 0x1F40;
                PHASE2 = 0x1F40;
                PHASE3 = 0x1F40;
                
                StartStop = false;    
                setDesligaClearPWM();
                PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_3, 0);    

              }
            }
            else{
               contCorrenteAD = 0; 
            }
            stateAD = 5; 
            break;
        case 5:
            ADC1_Disable();
            stateAD = 0;                    
            break;
    } 
}

void App_Inversor_GravaMemoria(void) {
    // Get flash page aligned address of flash reserved above for this test.
    flash_storage_address = FLASH_GetErasePageAddress((uint32_t) & flashTestPage[0]);
    FLASH_Unlock(FLASH_UNLOCK_KEY);

    result = FLASH_ErasePage(flash_storage_address);

    // Fill first 4 flash words with data
    // For this product we must write two adjacent words at a one time.
    write_data[0] = Time_T1;
    write_data[1] = Time_T2;
    write_data[2] = Time_T3;
    write_data[3] = contCiclo;

    // For this product we must write two adjacent words at a one time.
    result = FLASH_WriteDoubleWord24(flash_storage_address, write_data[0], write_data[1]);
    result &= FLASH_WriteDoubleWord24(flash_storage_address + 4U,
            write_data[2], write_data[3]);

    // Clear Key for NVM Commands so accidental call to flash routines will not corrupt flash
    FLASH_Lock();

}

void App_Inversor_LerMemoria(void) {

    // Get flash page aligned address of flash reserved above for this test.
    flash_storage_address = FLASH_GetErasePageAddress((uint32_t) & flashTestPage[0]);

    // read the flash words to verify the data
    read_data[0] = FLASH_ReadWord24(flash_storage_address);
    read_data[1] = FLASH_ReadWord24(flash_storage_address + 2U);
    read_data[2] = FLASH_ReadWord24(flash_storage_address + 4U);
    read_data[3] = FLASH_ReadWord24(flash_storage_address + 6U);
}

void App_Inversor_Init(void) {
   Time_T1 = 3;    
   Time_T2 = 3;    
   Time_T3 = 4;    

    valorHz = RampaMAX;
    TMR1_Start();
    SRV_TIMER_Init();
    ADC1_Initialize();
    
    //TMR3_SetInterruptHandler(My_ISR);
    //TMR3_Start();    
  
    PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
    PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
    PWM_DutyCycleSet(PWM_GENERATOR_3, 0);
    PWM_Enable();

    TMR2_SetInterruptHandler(gerar_asenoid);
    TMR2_Start();

    setDefazagem(0);

    LD1_Toggle();

    TMR2_Period16BitSet(vTMR2 + RampaMIN);

    display_escreve(0);
    
   
    
    __delay_ms(2000);
    
     Rele_220V_SetHigh();
     
     setDesligaClearPWM();
     
     CTA_SetDigitalInput();
    
}

void App_Inversor_ConfigTime_1(void) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static uint16_t timeOut = 0;

    App_Inversor_KeyBoard();
    //App_Inversor_PiscaDisplay(Time_T1);

    display_Run();

    if (keyboard.CH1_click) {
        keyboard.CH1_click = false;
        timeOut = 0;
        Time_T1++;
        if (Time_T1 > 99) {
            Time_T1 = 1;
        }
    }

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) > 1) {
        tickLast = tick;

        App_inversor_Frequencia_60(0);

        timeOut++;
        if (timeOut > 10000) {
            timeOut = 0;
            configTime1 = false;
            App_Inversor_GravaMemoria();
        }
    }
}

void App_Inversor_ConfigTime_2(void) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static uint16_t timeOut = 0;

    App_Inversor_KeyBoard();
    App_Inversor_PiscaDisplay(Time_T2);
    //App_inversor_Frequencia_60(0);
    display_Run();

    if (keyboard.CH2_click) {
        keyboard.CH2_click = false;
        timeOut = 0;
        Time_T2++;
        if (Time_T2 > 99) {
            Time_T2 = 1;
        }
    }

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) > 1) {
        tickLast = tick;

        timeOut++;
        if (timeOut > 10000) {
            timeOut = 0;
            configTime2 = false;
            App_Inversor_GravaMemoria();
        }
    }
}

void App_Inversor_ConfigTime_3(void) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static uint16_t timeOut = 0;

    App_Inversor_KeyBoard();
    App_Inversor_PiscaDisplay(Time_T3);
   // App_inversor_Frequencia_60(0);
    display_Run();

    if (keyboard.CH3_click) {
        keyboard.CH3_click = false;
        timeOut = 0;
        Time_T3++;
        if (Time_T3 > 99) {
            Time_T3 = 1;
        }
    }

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) > 1) {
        tickLast = tick;

        timeOut++;
        if (timeOut > 10000) {
            timeOut = 0;
            configTime3 = false;
            App_Inversor_GravaMemoria();
        }
    }
}

void App_Inversor_PiscaDisplay(uint16_t valor) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;

    static bool flag = false;

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) >  300) {
        tickLast = tick;

        flag ^= 1;

        if (flag)
            display_escreve(100);
        else
            display_escreve(valor);

    }
}

void App_Inversor_KeyBoard(void) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) > 160) {
        tickLast = tick;

        //tecla 1
        if (CH1_GetValue() == 1) {
            keyboard.CH1_clicked++;
            if (keyboard.CH1_clicked == 2) {
                keyboard.CH1_click = true;
            }
            if (keyboard.CH1_clicked == 100) {
                keyboard.CH1_click_10s = true;
                keyboard.CH1_click = false;
                keyboard.CH1_clicked = 104;
            }
        } else {
            keyboard.CH1_clicked = 0;
            keyboard.CH1_click = false;
        }
        // tecla 2
        if (CH2_GetValue() == 1) {
            keyboard.CH2_clicked++;
            if (keyboard.CH2_clicked == 2) {
                keyboard.CH2_click = true;
            }
            if (keyboard.CH2_clicked == 100) {
                keyboard.CH2_click_10s = true;
                keyboard.CH2_click = false;
                keyboard.CH2_clicked = 104;
            }
        } else {
            keyboard.CH2_clicked = 0;
            keyboard.CH2_click = false;
        }
        // tecla 3
        if (CH3_GetValue() == 1) {
            keyboard.CH3_clicked++;
            if (keyboard.CH3_clicked == 2) {
                keyboard.CH3_click = true;
            }
            if (keyboard.CH3_clicked == 100) {
                keyboard.CH3_click_10s = true;
                keyboard.CH3_click = false;
                keyboard.CH3_clicked = 104;
            }
        } else {
            keyboard.CH3_clicked = 0;
            keyboard.CH3_click = false;
        }
        
//        //CTA
//        if (CTA_GetValue() == 0) {
//            if (++keyboard.CTA_clicked == 2) {
//                keyboard.CTA_click = true;
//                keyboard.CTA_clicked = 4;
//            }
//        } else {
//            keyboard.CTA_clicked = 0;
//            keyboard.CTA_click = false;
//        }

    }


}

void App_inversor_leituraKeyboard(void) {

    //tecla 1
    if (keyboard.CH1_click) {
        keyboard.CH1_click = false;
        ligaDesliga ^= 1;

        if (ligaDesliga) {
            Rele_Porta_SetHigh();
            Zera_tickStart();
            StartStop = false;
            setDefazagem(1);
            RampaMAX = setMax_45;
            RampaMIN = setMin_45; // 45 Hz
            valorHz = RampaMAX;
            ligado = false;
            fazendoRampa = false;
            tempoLigado = Time_T1;
            SelecaoFreq = 45;
        }
    }
    //tecla 2
    if (keyboard.CH2_click) {
        keyboard.CH2_click = false;
        ligaDesliga ^= 1;

        if (ligaDesliga) {
            Rele_Porta_SetHigh();
            Zera_tickStart();
            StartStop = false;
            setDefazagem(1);
            RampaMAX = setMax_60;
            RampaMIN = setMin_60; // 60 Hz
            valorHz = RampaMAX;
            ligado = false;
            fazendoRampa = false;
            tempoLigado = Time_T2;
            SelecaoFreq = 60;
        }
    }
    //tecla 3
    if (keyboard.CH3_click) {
        keyboard.CH3_click = false;
        ligaDesliga ^= 1;

        if (ligaDesliga) {
            Rele_Porta_SetHigh();
            Zera_tickStart();
            StartStop = false;
            setDefazagem(1);
            RampaMAX = setMax_75;
            RampaMIN = setMin_75; // 75 Hz
            valorHz = RampaMAX;
            ligado = false;
            fazendoRampa = false;
            tempoLigado = Time_T3;
            SelecaoFreq = 75;
        }
    }


    if (keyboard.CH1_click_10s == true) {
        keyboard.CH1_click_10s = false;        
    }
    if (keyboard.CH2_click_10s == true) {
        keyboard.CH2_click_10s = false;       
    }
    if (keyboard.CH3_click_10s == true) {
        keyboard.CH3_click_10s = false;        
    }

}

void Zera_tickStart(void) {
    tickStart = SRV_TIMER_GetTick();
    tickLastStart = tickStart;
}

void App_Inversor_ContaTempo(uint8_t tempo) {


    tickStart = SRV_TIMER_GetTick();

    if((uint32_t)(tickStart - tickLastStart) >= 60000) {
        tickLastStart = tickStart;
        tempoLigado--;
        if (ligaDesliga == true && tempoLigado == 0) {            
            ligaDesliga = false;
        }
    }

}

void App_Inversor_Run(void) {

    display_Run();
    App_Inversor_KeyBoard();
    
//======= teste de frenquancia =================== 
////    // PCLKDIV 4; 
////    PTCON2 = 0x02; //4k
//    
//    // PCLKDIV 2; 
//    PTCON2 = 0x01; // 8k  
////    
////    // PCLKDIV 1; 
////    PTCON2 = 0x00; // 16k  
//    
//    StartStop = 1;
//    valorHz = (uint16_t)(gerar_frequencia(75));
//    TMR2_Period16BitSet(vTMR2 + valorHz);
//===============================================
    
    
//    if (configTime1) {
//        App_Inversor_ConfigTime_1();
//    } else if (configTime2) {
//        App_Inversor_ConfigTime_2();
//    } else if (configTime3) {
//        App_Inversor_ConfigTime_3();
//    } else if (AtingiuLimite == true) {
//        ligaDesliga = false;
//        tempoLigado = 0;
//        display_escreve(200);
//        App_inversor_Frequencia_60(0);
//        if (gravarCicloOK == true) {
//            gravarCicloOK = false;
//            App_Inversor_GravaMemoria();
//        }
//    } else 
    
    //if (AtingiuLimite == false) {
        App_invensor_Controller();
   // }


}

void App_invensor_Controller(void) {
    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static bool animaEmegercia = false;
    static uint16_t contAnima = 0;
    static uint16_t contCorrente = 0;   
    static uint16_t contTemperatura = 0;
    static bool ligadoEmergencia = false;
    
    static uint16_t delayEmergencia = 0;
    //static bool lendoAD = false;
    // static int conversion = 0, i = 0;

    static uint16_t calcMediaTemp = 0;
    static uint16_t MediaTemp = 0;
    uint16_t leituraTemp = 0;

    App_inversor_leituraKeyboard();
    App_Inversor_ContaTempo(tempoLigado);

    tick = SRV_TIMER_GetTick();
        
    if((uint32_t)(tick - tickLast) >= 100 || (tick == 0)) {
        tickLast = tick;
                     
//        //----- leitura da temperatura -----------------------------------
        if (ligado) {           
           // media_leituraAD_temperatura();
        } 
//        //=============================================

         media_leituraAD_Corrente();
         
        //- verifica a corente ----------
        if ( ITRIP_GetValue() == 1  ) {  // resistores de 18k ( r28) e 1k6 ( r27 )
            contCorrente++;
            if ((contCorrente >= 5)) {
                contCorrente = 0;
                ligaDesliga = false;             
                tempoLigado = 0;
               // display_escreve(200);
                //AtingiuLimite = true;
                if(SelecaoFreq == 45)
                {
                   App_inversor_Frequencia_45(0);  
                }           
                else if(SelecaoFreq == 60)
                {
                  App_inversor_Frequencia_60(0);  
                }
                else if(SelecaoFreq == 75)
                {
                  App_inversor_Frequencia_75(0);  
                }    
                
            }
        } else {
            contCorrente = 0;
        }        
        
        //======================================

        //CTA
        if (CTA_GetValue() == 1) {
            ligadoEmergencia = true;
            delayEmergencia = 0;
            ligaDesliga = false;
            contAnima++;
            if (contAnima >= 3) 
            {
                contAnima = 0;
                if(animaEmegercia == 1)
                {
                    animaEmegercia = 0;
                }
                else
                {
                   animaEmegercia = 1; 
                }                
            }
            
            if (animaEmegercia == 1) 
            {
                display_escreve(0);
                display_Run();
                LD1_SetHigh();
                
            } 
            else 
            {
                display_escreve(100);
                display_Run();
                LD1_SetLow();
            }
        }
        else{
            ligadoEmergencia = false;  
        }
       //=============================== 

        if (gravarCicloOK == true) {
            gravarCicloOK = false;
            App_Inversor_GravaMemoria();
        }

        if (ligaDesliga){ LD1_Toggle();}
           // LD1_Toggle();

    }

    if (ligaDesliga == false) {
        
        if(SelecaoFreq == 45)
        {
         App_inversor_Frequencia_45(0);   
        }
        else if( SelecaoFreq == 60)
        {
          App_inversor_Frequencia_60(0);  
        }
        else if( SelecaoFreq == 75)
        {
          App_inversor_Frequencia_75(0);  
        }
        
        if(ligadoEmergencia == false)
        {
          display_escreve(0);
          LD1_SetHigh();  
        }
        
    } else if (ligaDesliga == true) {
        if(SelecaoFreq == 45)
        {
            App_inversor_Frequencia_45(1);   
        }
        else if( SelecaoFreq == 60)
        {
            App_inversor_Frequencia_60(1); 
        }
        else if( SelecaoFreq == 75)
        {
          App_inversor_Frequencia_75(1);   
        }
        display_escreve(tempoLigado);
        
    }
}

void App_inversor_Frequencia_75(uint8_t state) {

     static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    
    static uint16_t checkValor = 0;
    static uint16_t contSubida = 0;
    static uint8_t incdec = 10;     
    static uint16_t trocafreq = 0;
    static uint16_t voltaFase = 0x1F40;

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) >= 1 || tick == 0)
    {
        tickLast = tick;

        if (state == 1) 
        {                          
            StartStop = true;
            
            if (ligado == false)
            {   
               // configurarFrequenciaTimer2(16000);
                
                ////    // PCLKDIV 4; 
                ////    PTCON2 = 0x02; //4k
                //    
                //    // PCLKDIV 2; 
                //    PTCON2 = 0x01; // 8k  
                ////    
                ////    // PCLKDIV 1; 
                PTCON2 = 0x00; // 16k  
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
                contSubida++;
                if(contSubida >= 85) {
                  contSubida = 0;
                  incdec++; 
                }
                
                valorHz = (uint16_t)(gerar_frequencia(incdec));                
                if (incdec >= 75) 
                {
                  incdec = 75;                 
                  ligado = true;
                  fazendoRampa = false;
                  IncFreq = (uint16_t)(gerar_frequencia(incdec));
                  valorHz = IncFreq;                 
                }                              
            }
            else{
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
              valorHz = (uint16_t)(gerar_frequencia(75));
              fazendoRampa = false;         
            }   

        } 
        else if (state == 0) 
        {
            
                if(incdec < 30){
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                else{ 
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }

            if (++contSubida >= 25) 
            {
               contSubida = 0;
               incdec--;
               valorHz = (uint16_t)(gerar_frequencia(incdec));       
            }                                 
            
            if (incdec <= 10) 
            {
                voltaFase = 0x1F40;
                incdec = 10;
                trocafreq = 0;              
                contSubida = 0;
                valorHz = 3050;
                ligado = false;
                StartStop = false;
                fazendoRampa = false;
                ligaDesliga = false;
                setDesligaClearPWM();
                PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_3, 0);
//                if (gravarCiclo == true) {
//                    gravarCiclo = false;
//                    gravarCicloOK = true;
//                }
                Rele_Porta_SetLow();
            }
            
           
        }

        if (checkValor != valorHz) {
            checkValor = valorHz;
            TMR2_Period16BitSet(vTMR2 + valorHz);
        }
        

    }


}

void App_inversor_Frequencia_60(uint8_t state) {

    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    
    static uint16_t checkValor = 0;
    static uint16_t contSubida = 0;
    static uint8_t incdec = 10;     
    static uint16_t trocafreq = 0;
    static uint16_t voltaFase = 0x1F40;

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) >= 1 || tick == 0)
    {
        tickLast = tick;

        if (state == 1) 
        {                          
            StartStop = true;
            
            if (ligado == false)
            {   
               // configurarFrequenciaTimer2(16000);
                
                ////    // PCLKDIV 4; 
                ////    PTCON2 = 0x02; //4k
                //    
                //    // PCLKDIV 2; 
                //    PTCON2 = 0x01; // 8k  
                ////    
                ////    // PCLKDIV 1; 
                PTCON2 = 0x00; // 16k  
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
                contSubida++;
                if(contSubida >= 85) {
                  contSubida = 0;
                  incdec++; 
                }
                
                valorHz = (uint16_t)(gerar_frequencia(incdec));                
                if (incdec >= 60) 
                {
                  incdec = 60;                 
                  ligado = true;
                  fazendoRampa = false;
                  IncFreq = (uint16_t)(gerar_frequencia(incdec));
                  valorHz = IncFreq;                 
                }                              
            }
            else{
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
              valorHz = (uint16_t)(gerar_frequencia(60));
              fazendoRampa = false;         
            }   

        } 
        else if (state == 0) 
        {
            
                if(incdec < 30){
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                else{ 
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }

            if (++contSubida >= 25) 
            {
               contSubida = 0;
               incdec--;
               valorHz = (uint16_t)(gerar_frequencia(incdec));       
            }                                 
            
            if (incdec <= 10) 
            {
                voltaFase = 0x1F40;
                incdec = 10;
                trocafreq = 0;              
                contSubida = 0;
                valorHz = 3050;
                ligado = false;
                StartStop = false;
                fazendoRampa = false;
                ligaDesliga = false;
                setDesligaClearPWM();
                PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_3, 0);
//                if (gravarCiclo == true) {
//                    gravarCiclo = false;
//                    gravarCicloOK = true;
//                }
                Rele_Porta_SetLow();
            }
            
           
        }

        if (checkValor != valorHz) {
            checkValor = valorHz;
            TMR2_Period16BitSet(vTMR2 + valorHz);
        }
        

    }

}

void App_inversor_Frequencia_45(uint8_t state) {

    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    
    static uint16_t checkValor = 0;
    static uint16_t contSubida = 0;
    static uint8_t incdec = 10;     
    static uint16_t trocafreq = 0;
    static uint16_t voltaFase = 0x1F40;

    tick = SRV_TIMER_GetTick();
    if((uint32_t)(tick - tickLast) >= 1 || tick == 0)
    {
        tickLast = tick;

        if (state == 1) 
        {                          
            StartStop = true;
            
            if (ligado == false)
            {   
               // configurarFrequenciaTimer2(16000);
                
                ////    // PCLKDIV 4; 
                ////    PTCON2 = 0x02; //4k
                //    
                //    // PCLKDIV 2; 
                //    PTCON2 = 0x01; // 8k  
                ////    
                ////    // PCLKDIV 1; 
                PTCON2 = 0x00; // 16k  
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
                contSubida++;
                if(contSubida >= 85) {
                  contSubida = 0;
                  incdec++; 
                }
                
                valorHz = (uint16_t)(gerar_frequencia(incdec));                
                if (incdec >= 45) 
                {
                  incdec = 45;                 
                  ligado = true;
                  fazendoRampa = false;
                  IncFreq = (uint16_t)(gerar_frequencia(incdec));
                  valorHz = IncFreq;                 
                }                              
            }
            else{
                
                if(incdec < 30){
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;                    
                }
                else{
                    voltaFase--;
                    if(voltaFase <= 0xFA0){
                        voltaFase = 0xFA0;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                
              valorHz = (uint16_t)(gerar_frequencia(45));
              fazendoRampa = false;         
            }   

        } 
        else if (state == 0) 
        {
            
                if(incdec < 30){
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }
                else{ 
                    voltaFase = voltaFase + 500;
                    if(voltaFase >= 0x1F40){
                        voltaFase = 0x1F40;
                    }
                    PHASE1 = voltaFase;
                    PHASE2 = voltaFase;
                    PHASE3 = voltaFase;
                }

            if (++contSubida >= 25) 
            {
               contSubida = 0;
               incdec--;
               valorHz = (uint16_t)(gerar_frequencia(incdec));       
            }                                 
            
            if (incdec <= 10) 
            {
                voltaFase = 0x1F40;
                incdec = 10;
                trocafreq = 0;              
                contSubida = 0;
                valorHz = 3050;
                ligado = false;
                StartStop = false;
                fazendoRampa = false;
                ligaDesliga = false;
                setDesligaClearPWM();
                PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_2, 0);
                PWM_DutyCycleSet(PWM_GENERATOR_3, 0);
//                if (gravarCiclo == true) {
//                    gravarCiclo = false;
//                    gravarCicloOK = true;
//                }
                Rele_Porta_SetLow();
            }
            
           
        }

        if (checkValor != valorHz) {
            checkValor = valorHz;
            TMR2_Period16BitSet(vTMR2 + valorHz);
        }
        

    }

}




int gerar_frequencia( uint8_t freq)
{
    static int result = 0;
         
    if(freq <= 1)
    {       
       result = 23600; 
    }
    else if(freq == 2)
    {       
       result = 22600;
    }
    else if(freq == 3)
    {
       result = 21600;
    }
    else if(freq == 4)
    {
       
       result = 20600;
    }
    else if(freq == 5)
    {
       result = 19600;
    }
    else if(freq == 6)
    {
       result = 18600;
    }
    else if(freq == 7)
    {
       result = 16800;
    }
    else if(freq == 8)
    {
       result = 14000;
    }
    else if(freq == 9)
    {
       result = 12500;    
    }
    else if( freq == 10)
    {
       result = 10800; 
    }
    else if( freq == 11)
    {
       result = 10000; 
    }
    else if( freq == 12)
    {
       result = 9000; 
    }
    else if( freq == 13)
    {
       result = 8500; 
    }
    else if( freq == 14)
    {
       result = 8000; 
    }
    else if( freq == 15)
    {
       result = 7500; 
    }
    else if( freq == 16)
    {
       result = 7000; 
    }
    else if( freq == 17)
    {
       result = 6500; 
    }
    else if( freq == 18)
    {
       result = 6200; 
    }
    else if( freq == 19)
    {
       result = 5900; 
    }
    else if( freq == 20)
    {
       result = 5600; 
    }
    else if( freq == 21)
    {
       result = 5200; 
    }
    else if( freq == 22)
    {
       result = 5000; 
    }
    else if( freq == 23)
    {
       result = 4800; 
    }
    else if( freq == 24)
    {
       result = 4600; 
    }
    else if( freq == 25)
    {
       result = 4300; 
    }
    else if( freq == 26)
    {
       result = 4180; 
    }
    else if( freq == 27)
    {
       result = 4000; 
    }
    else if( freq == 28)
    {
       result = 3900; 
    }
    else if( freq == 29)
    {
       result = 3700; 
    }
    else if( freq == 30)
    {
       result = 3500; 
    }
    else if( freq == 31)
    {
       result = 3450; 
    }
    else if( freq == 32)
    {
       result = 3350; 
    }
    else if( freq == 33)
    {
       result = 3250; 
    } 
    else if( freq == 34)
    {
       result = 3150; 
    }
    else if( freq == 35)
    {
       result = 3050; 
    }
    else if( freq == 36)
    {
       result = 2950; 
    }
    else if( freq == 37)
    {
       result = 2850; 
    }
    else if( freq == 38)
    {
       result = 2750; 
    }
    else if( freq == 39)
    {
       result = 2700; 
    }
    else if( freq == 40)
    {
       result = 2650; 
    }
    else if( freq == 41)
    {
       result = 2550; 
    }
    else if( freq == 42)
    {
       result = 2480; 
    }
    else if( freq == 43)
    {
       result = 2440; 
    }
    else if( freq == 44)
    {
       result = 2380; 
    }
    else if( freq == 45)
    {
       result = 2300; 
    }
    else if( freq == 46)
    {
       result = 2250; 
    }
    else if( freq == 47)
    {
       result = 2200; 
    }
    else if( freq == 48)
    {
       result = 2150; 
    }
    else if( freq == 49)
    {
       result = 2100; 
    }
    else if( freq == 50)
    {
       result = 2050; 
    }
    else if( freq == 51)
    {
       result = 2000; 
    }
    else if( freq == 52)
    {
       result = 1950; 
    }
    else if( freq == 53)
    {
       result = 1930; 
    }
    else if( freq == 54)
    {
       result = 1900; 
    }
    else if( freq == 55)
    {
       result = 1840; 
    }
    else if( freq == 56)
    {
       result = 1800; 
    }    
    else if( freq == 57)
    {
       result = 1750; 
    }
    else if( freq == 58)
    {
       result = 1730; 
    }
    else if( freq == 59)
    {
       result = 1700; 
    }
    else if( freq == 60)
    {
       result = 1650; 
    }
    else if( freq == 61)
    {
       result = 1630; 
    }
    else if( freq == 62)
    {
       result = 1600; 
    }
    else if( freq == 63)
    {
       result = 1580; 
    }
    else if( freq == 64)
    {
       result = 1550; 
    }
    else if( freq == 65)
    {
       result = 1500; 
    }
    else if( freq == 66)
    {
       result = 1480; 
    }
    else if( freq == 67)
    {
       result = 1450; 
    }
    else if( freq == 68)
    {
       result = 1430; 
    }
    else if( freq == 69)
    {
       result = 1420; 
    }
    else if( freq == 70)
    {
       result = 1390; 
    }
    else if( freq == 71)
    {
       result = 1350; 
    }
    else if( freq == 72)
    {
       result = 1320; 
    }
    else if( freq == 73)
    {
       result = 1300; 
    }
    else if( freq == 74)
    {
       result = 1280; 
    }
    else if( freq >= 75)
    {
       result = 1250; 
    }    
       
    if(result < 1250)
    {
        result = 1250;
    }   
        
    return result;    
     
    
}

