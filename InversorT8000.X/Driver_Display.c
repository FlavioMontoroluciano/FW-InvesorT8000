#include "Driver_Display.h"
#include "mcc_generated_files/pin_manager.h"

#define delay() {int i = 0; for(i=0;i <100;i++){}}

typedef struct {
    uint8_t Dig1;
    uint8_t Dig2;

    uint8_t valorNum;
} numero_t;

numero_t numero;

void DSP_Numero0(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetHigh();
    SEG_F_SetHigh();
    SEG_G_SetLow();
}

void DSP_Numero1(void) {
    SEG_A_SetLow();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetLow();
    SEG_E_SetLow();
    SEG_F_SetLow();
    SEG_G_SetLow();
}

void DSP_Numero2(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetLow();
    SEG_D_SetHigh();
    SEG_E_SetHigh();
    SEG_F_SetLow();
    SEG_G_SetHigh();
}

void DSP_Numero3(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetLow();
    SEG_F_SetLow();
    SEG_G_SetHigh();
}

void DSP_Numero4(void) {
    SEG_A_SetLow();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetLow();
    SEG_E_SetLow();
    SEG_F_SetHigh();
    SEG_G_SetHigh();
}

void DSP_Numero5(void) {
    SEG_A_SetHigh();
    SEG_B_SetLow();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetLow();
    SEG_F_SetHigh();
    SEG_G_SetHigh();
}

void DSP_Numero6(void) {
    SEG_A_SetHigh();
    SEG_B_SetLow();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetHigh();
    SEG_F_SetHigh();
    SEG_G_SetHigh();
}

void DSP_Numero7(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetLow();
    SEG_E_SetLow();
    SEG_F_SetLow();
    SEG_G_SetLow();
}

void DSP_Numero8(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetHigh();
    SEG_F_SetHigh();
    SEG_G_SetHigh();
}

void DSP_Numero9(void) {
    SEG_A_SetHigh();
    SEG_B_SetHigh();
    SEG_C_SetHigh();
    SEG_D_SetHigh();
    SEG_E_SetLow();
    SEG_F_SetHigh();
    SEG_G_SetHigh();
}

void DSP_DigitoApagado(void) {
    SEG_A_SetLow();
    SEG_B_SetLow();
    SEG_C_SetLow();
    SEG_D_SetLow();
    SEG_E_SetLow();
    SEG_F_SetLow();
    SEG_G_SetLow();
}
void DSP_Risco(void) {
    SEG_A_SetLow();
    SEG_B_SetLow();
    SEG_C_SetLow();
    SEG_D_SetLow();
    SEG_E_SetLow();
    SEG_F_SetLow();
    SEG_G_SetHigh();
}

typedef enum {
    zero = 0,
    um,
    dois,
    tres,
    quatro,
    cinco,
    seis,
    sete,
    oito,
    nove,
} DSP_Numeros_e;

void display_Run(void) {

    static uint32_t tick = 0;
    static uint32_t tickLast = 0;
    static bool multiplex = false;
    static uint8_t val = 0;

   // tick = SRV_TIMER_GetTick();
    //if((uint32_t)(tick - tickLast) > 1) {
        tickLast = tick;

        if (multiplex) {
            DSP_1_SetLow();
            DSP_2_SetLow();            
            DSP_1_SetHigh();
            DSP_2_SetLow();
            val = numero.Dig1;

        } else {
            DSP_1_SetLow();
            DSP_2_SetLow();            
            DSP_2_SetHigh();
            val = numero.Dig2;
        }

        if (numero.valorNum == 100) {
            DSP_DigitoApagado();
        } 
        else if(numero.valorNum == 200)
        {
            DSP_Risco();
        }
        else {
            switch (val) {
                case 0:
                    DSP_Numero0();
                    break;
                case 1:
                    DSP_Numero1();
                    break;
                case 2:
                    DSP_Numero2();
                    break;
                case 3:
                    DSP_Numero3();
                    break;
                case 4:
                    DSP_Numero4();
                    break;
                case 5:
                    DSP_Numero5();
                    break;
                case 6:
                    DSP_Numero6();
                    break;
                case 7:
                    DSP_Numero7();
                    break;
                case 8:
                    DSP_Numero8();
                    break;
                case 9:
                    DSP_Numero9();
                    break;
            }
        }


        multiplex ^= 1;
        DSP_DigitoApagado();
        delay(); 
                
        
        
    //}
}

void display_escreve(uint8_t valor) {

    char txt[2];
    numero.valorNum = valor;
    //sprintf(txt,"%d",valor);

    numero.Dig1 = (uint8_t) (valor / 10);
    numero.Dig2 = (uint8_t) (valor % 10);

}