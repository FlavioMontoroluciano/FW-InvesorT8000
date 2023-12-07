#include "Driver_InversorPWM.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/reset_types.h"
#include "mcc_generated_files/pwm.h"


#define IncDuty 0x28//0x46 //0xBE //0x26//0x20 //0x32

#define MaxPWM 0xFA0//0xFA  //0x1F4

#define ValorDefazagem1 0xA5 //0xA7  // 0xA5

#define ValorDefazagem2 0xA8 //0xA7  // 0xA5

uint16_t defazagem = 0;
uint8_t etapa = 0;


uint16_t valDef_1 = 0;
uint16_t valDef_2 = 0;

bool liberaFase1 = false;
bool liberaFase2 = false;
bool liberaFase3 = false;

uint16_t dutyCyle_Fase1 = 0;
bool flag_Fase1 = true;
bool flag_90_Fase1 = false;


uint16_t dutyCyle_Fase2 = 0;
bool flag_Fase2 = true;
bool flag_90_Fase2 = false;

uint16_t dutyCyle_Fase3 = 0;
bool flag_Fase3 = true;

void setDefazagem(uint16_t def) {
    defazagem = def;

    if (def >= 1) {
        liberaFase1 = true;
        liberaFase2 = false;
        liberaFase3 = false;
    } else {
        liberaFase1 = false;
        liberaFase2 = false;
        liberaFase3 = false;
    }

    dutyCyle_Fase1 = 0;
    flag_Fase1 = true;
    flag_90_Fase1 = false;

    dutyCyle_Fase2 = 0;
    flag_Fase2 = true;
    flag_90_Fase2 = false;

    dutyCyle_Fase3 = 0;
    flag_Fase3 = true;


    valDef_1 = (uint16_t) (MaxPWM - (MaxPWM * 0.33));

    valDef_2 = (uint16_t) (MaxPWM - (MaxPWM * 0.33));


}

#define TABLE_SIZE 258 
#define MAX_PWM 0xFA0

const int senoTable[TABLE_SIZE] = {
    1, 32, 63, 94, 125, 156, 187, 218, 249, 280,
    311, 342, 373, 404, 435, 466, 497, 528, 559, 590,
    621, 652, 683, 714, 745, 776, 807, 838, 869, 900,
    931, 962, 993, 1024, 1055, 1086, 1117, 1148, 1179, 1210,
    1241, 1272, 1303, 1334, 1365, 1396, 1427, 1458, 1489, 1520,
    1551, 1582, 1613, 1644, 1675, 1706, 1737, 1768, 1799, 1830,
    1861, 1892, 1923, 1954, 1985, 2016, 2047, 2078, 2109, 2140,
    2171, 2202, 2233, 2264, 2295, 2326, 2357, 2388, 2419, 2450,
    2481, 2512, 2543, 2574, 2605, 2636, 2667, 2698, 2729, 2760,
    2791, 2822, 2853, 2884, 2915, 2946, 2977, 3008, 3039, 3070,
    3101, 3132, 3163, 3194, 3225, 3256, 3287, 3318, 3349, 3380,
    3411, 3442, 3473, 3504, 3535, 3566, 3597, 3628, 3659, 3690,
    3721, 3752, 3783, 3814, 3845, 3876, 3907, 3938, 3969, 4000,
    3969, 3938, 3907, 3876, 3845, 3814, 3783, 3752, 3721, 3690,
    3659, 3628, 3597, 3566, 3535, 3504, 3473, 3442, 3411, 3380,
    3349, 3318, 3287, 3256, 3225, 3194, 3163, 3132, 3101, 3070,
    3039, 3008, 2977, 2946, 2915, 2884, 2853, 2822, 2791, 2760,
    2729, 2698, 2667, 2636, 2605, 2574, 2543, 2512, 2481, 2450,
    2419, 2388, 2357, 2326, 2295, 2264, 2233, 2202, 2171, 2140,
    2109, 2078, 2047, 2016, 1985, 1954, 1923, 1892, 1861, 1830,
    1799, 1768, 1737, 1706, 1675, 1644, 1613, 1582, 1551, 1520,
    1489, 1458, 1427, 1396, 1365, 1334, 1303, 1272, 1241, 1210,
    1179, 1148, 1117, 1086, 1055, 1024, 993, 962, 931, 900,
    869, 838, 807, 776, 745, 714, 683, 652, 621, 590,
    559, 528, 497, 466, 435, 404, 373, 342, 311, 280,
    249, 218, 187, 156, 125, 94, 63, 32, 1
};


//const uint16_t senoTable[TABLE_SIZE] = {
//    0x01, 0x09, 0x11, 0x19, 0x21, 0x29, 0x31, 0x39,
//    0x41, 0x49, 0x51, 0x59, 0x61, 0x69, 0x71, 0x79,
//    0x81, 0x89, 0x91, 0x99, 0xA1, 0xA9, 0xB1, 0xB9,
//    0xC1, 0xC9, 0xD1, 0xD9, 0xE1, 0xE9, 0xF1, 0xF9,
//    0x101, 0x109, 0x111, 0x119, 0x121, 0x129, 0x131, 0x139,
//    0x141, 0x149, 0x151, 0x159, 0x161, 0x169, 0x171, 0x179,
//    0x181, 0x189, 0x191, 0x199, 0x1A1, 0x1A9, 0x1B1, 0x1B9,
//    0x1C1, 0x1C9, 0x1D1, 0x1D9, 0x1E1, 0x1E9, 0x1F1, 0x1F9,
//    0x201, 0x209, 0x211, 0x219, 0x221, 0x229, 0x231, 0x239,
//    0x241, 0x249, 0x251, 0x259, 0x261, 0x269, 0x271, 0x279,
//    0x281, 0x289, 0x291, 0x299, 0x2A1, 0x2A9, 0x2B1, 0x2B9,
//    0x2C1, 0x2C9, 0x2D1, 0x2D9, 0x2E1, 0x2E9, 0x2F1, 0x2F9,
//    0x301, 0x309, 0x311, 0x319, 0x321, 0x329, 0x331, 0x339,
//    0x341, 0x349, 0x351, 0x359, 0x361, 0x369, 0x371, 0x379,
//    0x381, 0x389, 0x391, 0x399, 0x3A1, 0x3A9, 0x3B1, 0x3B9,
//    0x3C1, 0x3C9, 0x3D1, 0x3D9, 0x3E1, 0x3E9, 0x3F1, 0x3F9,
//    0x401, 0x409, 0x411, 0x419, 0x421, 0x429, 0x431, 0x439,
//    0x441, 0x449, 0x451, 0x459, 0x461, 0x469, 0x471, 0x479,
//    0x481, 0x489, 0x491, 0x499, 0x4A1, 0x4A9, 0x4B1, 0x4B9,
//    0x4C1, 0x4C9, 0x4D1, 0x4D9, 0x4E1, 0x4E9, 0x4F1, 0x4F9,
//    0x501, 0x509, 0x511, 0x519, 0x521, 0x529, 0x531, 0x539,
//    0x541, 0x549, 0x551, 0x559, 0x561, 0x569, 0x571, 0x579,
//    0x581, 0x589, 0x591, 0x599, 0x5A1, 0x5A9, 0x5B1, 0x5B9,
//    0x5C1, 0x5C9, 0x5D1, 0x5D9, 0x5E1, 0x5E9, 0x5F1, 0x5F9,
//    0x601, 0x609, 0x611, 0x619, 0x621, 0x629, 0x631, 0x639,
//    0x641, 0x649, 0x651, 0x659, 0x661, 0x669, 0x671, 0x679,
//    0x681, 0x689, 0x691, 0x699, 0x6A1, 0x6A9, 0x6B1, 0x6B9,
//    0x6C1, 0x6C9, 0x6D1, 0x6D9, 0x6E1, 0x6E9, 0x6F1, 0x6F9,
//    0x701, 0x709, 0x711, 0x719, 0x721, 0x729, 0x731, 0x739,
//    0x741, 0x749, 0x751, 0x759, 0x761, 0x769, 0x771, 0x779,
//    0x781, 0x789, 0x791, 0x799, 0x7A1, 0x7A9, 0x7B1, 0x7B9,
//    0x7C1, 0x7C9, 0x7D1, 0x7D9, 0x7E1, 0x7E9, 0x7F1, 0x7F9,
//    0x801, 0x809, 0x811, 0x819, 0x821, 0x829, 0x831, 0x839,
//    0x841, 0x849, 0x851, 0x859, 0x861, 0x869, 0x871, 0x879,
//    0x881, 0x889, 0x891, 0x899, 0x8A1, 0x8A9, 0x8B1, 0x8B9,
//    0x8C1, 0x8C9, 0x8D1, 0x8D9, 0x8E1, 0x8E9, 0x8F1, 0x8F9,
//    0x901, 0x909, 0x911, 0x919, 0x921, 0x929, 0x931, 0x939,
//    0x941, 0x949, 0x951, 0x959, 0x961, 0x969, 0x971, 0x979,
//    0x981, 0x989, 0x991, 0x999, 0x9A1, 0x9A9, 0x9B1, 0x9B9,
//    0x9C1, 0x9C9, 0x9D1, 0x9D9, 0x9E1, 0x9E9, 0x9F1, 0x9F9,
//    0xA01, 0xA09, 0xA11, 0xA19, 0xA21, 0xA29, 0xA31, 0xA39,
//    0xA41, 0xA49, 0xA51, 0xA59, 0xA61, 0xA69, 0xA71, 0xA79,
//    0xA81, 0xA89, 0xA91, 0xA99, 0xAA1, 0xAA9, 0xAB1, 0xAB9,
//    0xAC1, 0xAC9, 0xAD1, 0xAD9, 0xAE1, 0xAE9, 0xAF1, 0xAF9,
//    0xB01, 0xB09, 0xB11, 0xB19, 0xB21, 0xB29, 0xB31, 0xB39,
//    0xB41, 0xB49, 0xB51, 0xB59, 0xB61, 0xB69, 0xB71, 0xB79,
//    0xB81, 0xB89, 0xB91, 0xB99, 0xBA1, 0xBA9, 0xBB1, 0xBB9,
//    0xBC1, 0xBC9, 0xBD1, 0xBD9, 0xBE1, 0xBE9, 0xBF1, 0xBF9,
//    0xC01, 0xC09, 0xC11, 0xC19, 0xC21, 0xC29, 0xC31, 0xC39,
//    0xC41, 0xC49, 0xC51, 0xC59, 0xC61, 0xC69, 0xC71, 0xC79,
//    0xC81, 0xC89, 0xC91, 0xC99, 0xCA1, 0xCA9, 0xCB1, 0xCB9,
//    0xCC1, 0xCC9, 0xCD1, 0xCD9, 0xCE1, 0xCE9, 0xCF1, 0xCF9,
//    0xD01, 0xD09, 0xD11, 0xD19, 0xD21, 0xD29, 0xD31, 0xD39,
//    0xD41, 0xD49, 0xD51, 0xD59, 0xD61, 0xD69, 0xD71, 0xD79,
//    0xD81, 0xD89, 0xD91, 0xD99, 0xDA1, 0xDA9, 0xDB1, 0xDB9,
//    0xDC1, 0xDC9, 0xDD1, 0xDD9, 0xDE1, 0xDE9, 0xDF1, 0xDF9,
//    0xE01, 0xE09, 0xE11, 0xE19, 0xE21, 0xE29, 0xE31, 0xE39,
//    0xE41, 0xE49, 0xE51, 0xE59, 0xE61, 0xE69, 0xE71, 0xE79,
//    0xE81, 0xE89, 0xE91, 0xE99, 0xEA1, 0xEA9, 0xEB1, 0xEB9,
//    0xEC1, 0xEC9, 0xED1, 0xED9, 0xEE1, 0xEE9, 0xEF1, 0xEF9,
//    0xF01, 0xF09, 0xF11, 0xF19, 0xF21, 0xF29, 0xF31, 0xF39,
//    0xF41, 0xF49, 0xF51, 0xF59, 0xF61, 0xF69, 0xF71, 0xF79,
//    0xF81, 0xF89, 0xF91, 0xF99, 0xFA1, 0xFA9, 0xFB1, 0xFB9,
//    0xFC1, 0xFC9, 0xFD1, 0xFD9, 0xFE1, 0xFE9, 0xFF1, 0xFF9,
//    0x001
//};

uint8_t index = 0 , index2 = 0 , index3 = 0;
bool flagfase2 = false;
bool flagfase3 = false;
    
void setDesligaClearPWM()
{
    index = 0 , index2 = 0 , index3 = 0;
    flagfase2 = false;
    flagfase3 = false;
}

void controle_inversor(uint8_t state, uint16_t freq) {


//    if (flag_90_Fase1 == true && dutyCyle_Fase1 <= valDef_1 && liberaFase2 == false) {
//        liberaFase2 = true;
//    }
//    if (flag_90_Fase2 == true && dutyCyle_Fase2 <= valDef_2 && liberaFase3 == false) {
//        liberaFase3 = true;
//    }
//
//
//    if (liberaFase1 == true) {
//        fase1(0);
//    }
//    if (liberaFase2 == true) {
//        fase2(0);
//    }
//    if (liberaFase3 == true) {
//        fase3(0);
//    }

   
    static uint16_t increment = 0;
     
    
    // Define a frequência do sinal senoidal
    float frequency = (float)freq;
    
    // Calcula o incremento do índice baseado na frequência
    //increment = (TABLE_SIZE * frequency) / 9999.6;  // Dividido por 8000 para ajustar a escala correta
    
    // Obtém os valores senoidais correspondentes aos índices atuais
    uint16_t senoValue1 = senoTable[index];
    uint16_t senoValue2 = senoTable[index2];
    uint16_t senoValue3 = senoTable[index3];
    
    // Calcula os duty cycles dos PWMs
    uint16_t dutyCycle1 = senoValue1;//(senoValue1 * MAX_PWM) / 0xFA0;
    uint16_t dutyCycle2 = senoValue2;//(senoValue2 * MAX_PWM) / 0xFA0;
    uint16_t dutyCycle3 = senoValue3;//(senoValue3 * MAX_PWM) / 0xFA0;
    
    // Atualiza os PWMs com os duty cycles calculados
    PWM_DutyCycleSet(PWM_GENERATOR_1, dutyCycle1);
    PWM_DutyCycleSet(PWM_GENERATOR_2, dutyCycle2);
    PWM_DutyCycleSet(PWM_GENERATOR_3, dutyCycle3);
    
    // Incrementa o índice na tabela de seno
    index ++;
    if(index >= 85)
    {
        flagfase2 = true;
    }
    if(index2 >= 85)
    {
        flagfase3 = true;
    }
    if(flagfase2)
    {
        index2++;
        if (index2 >= TABLE_SIZE) {
            index2 = 0;
        }        
    }
    if(flagfase3)
    {
        index3++;
        if (index3 >= TABLE_SIZE) {
            index3 = 0;
        }
    }
    
    // Verifica os limites do índice
    if (index >= TABLE_SIZE) {
        index = 0;
    }
    
    // Chamadas das funções de fase com a defasagem de 120 graus
//    fase1(state);
//    fase2(state);
//    fase3(state);
    
}

void fase1(uint8_t frequencia) {


    if (flag_Fase1) {
        dutyCyle_Fase1 = dutyCyle_Fase1 + IncDuty;
        if (dutyCyle_Fase1 >= MaxPWM) {
            dutyCyle_Fase1 = MaxPWM;
            flag_90_Fase1 = true;
            flag_Fase1 = false;
        }
    } else {
        dutyCyle_Fase1 = dutyCyle_Fase1 - IncDuty;
        if (dutyCyle_Fase1 <= 0) {
            dutyCyle_Fase1 = 0;
            flag_Fase1 = true;
        }
    }
    PWM_DutyCycleSet(PWM_GENERATOR_1, dutyCyle_Fase1);

}

void fase2(uint8_t frequencia) {

    if (flag_Fase2) {
        dutyCyle_Fase2 = dutyCyle_Fase2 + IncDuty;
        if (dutyCyle_Fase2 >= MaxPWM) {
            dutyCyle_Fase2 = MaxPWM;
            flag_90_Fase2 = true;
            flag_Fase2 = false;
        }
    } else {
        dutyCyle_Fase2 = dutyCyle_Fase2 - IncDuty;
        if (dutyCyle_Fase2 <= 0) {
            dutyCyle_Fase2 = 0;
            flag_Fase2 = true;
        }
    }

    PWM_DutyCycleSet(PWM_GENERATOR_2, dutyCyle_Fase2);

}

void fase3(uint8_t frequencia) {

    if (flag_Fase3) {
        dutyCyle_Fase3 = dutyCyle_Fase3 + IncDuty;
        if (dutyCyle_Fase3 >= MaxPWM) {
            dutyCyle_Fase3 = MaxPWM;
            flag_Fase3 = false;
            //    }
        }
    } else {
        dutyCyle_Fase3 = dutyCyle_Fase3 - IncDuty;
        if (dutyCyle_Fase3 <= 0) {
            dutyCyle_Fase3 = 0;
            flag_Fase3 = true;
        }
    }

    PWM_DutyCycleSet(PWM_GENERATOR_3, dutyCyle_Fase3);

}