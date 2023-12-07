/**********************************************************************
* © 2012 Microchip Technology Inc.
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                    include files                                           */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/

#include "general.h"
#include "periph.h"



/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/
_FPOR(ALTI2C1_OFF & ALTI2C2_OFF);
_FWDT(PLLKEN_ON & FWDTEN_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF & PWMLOCK_OFF);
_FGS(GWRP_OFF & GCP_OFF);

_FICD(ICS_PGD2 & JTAGEN_OFF);	// PGD3 for 28pin 	PGD2 for 44pin
_FOSC(FCKSM_CSECMD & POSCMD_XT);		//XT W/PLL
//_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE); // FRC W/PLL	

/********************Setting Configuration Bits End********************************/


/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: InitPeriph                                                  */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Init the peripherals: PLL, ADC, PWM & GPIO                    */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void InitPeriph(void)
{
	// Configure Oscillator to operate the device at 140Mhz
	// Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
	// Fosc= 8*70/(2*2)= 140Mhz for 8M input clock

	PLLFBD = 68;		        // M=68
	CLKDIVbits.PLLPOST = 0;		// N1=2
	CLKDIVbits.PLLPRE = 0;		// N2=2
	
	
	__builtin_write_OSCCONH(0x03);
	__builtin_write_OSCCONL(0x01);

	while(OSCCONbits.COSC != 0b011);
	// Wait for PLL to lock
	while(OSCCONbits.LOCK != 1);

    // Turn saturation on to insure that overflows will be handled smoothly.
    CORCONbits.SATA  = 0;    


   // ============= Port A ==============
	LATA  = 0x0000;
	TRISA = 0x0003;             // 0000 0000 0000 0011  RA1 - IA ; RA0 - IB
    ANSELA = 0X0003;             // ANSA1 - IA ANSA0 - IB	
    // ============= Port B ==============
    LATB  = 0x0000;
    TRISB = 0x0115;             // 0000 0001 0001 0001  RB15:RB10 - PWM1H:PWM3L;RB0 - IBUS;RB8 - BTN;RB4 - FLT_IP
    ANSELB = 0X0001;             // ANSB0 - IBUS
    // ============= Port C ==============
    LATC  = 0x0000;
    TRISC = 0x00a0;             // 0000 0000 0010 0000   RC5 - RX ; 
    ANSELC = 0x0000;             // 
    // ============= Port D ==============
	LATD  = 0x0000;
	TRISD = 0x0100;	            // 0000 0000 0000 0000; RD8 - Test Point I/P ,RD6 -  LED1 , RD5 - LED2
    // ============= Port E ==============
    LATE  = 0x0000;
    TRISE = 0x2000;             // 0010 0000 0000 0000  ;RE13 - POT ; 
    ANSELE = 0X2000;            // ANSE13 - POT 
    // ============= Port F ==============
    LATF  = 0x0000;
    TRISF = 0x0000;             // 0000 0000 0000 0000  RF1 - TX          
    // ============= Port G ==============
    LATG  = 0x0000;
    TRISG = 0x00C0;             // 0000 0000 0000 0000  

	//set S1 as input
    TRISBbits.TRISB8 = 1;	

	/*Assigning the TX and RX and FLT I/P pins to ports RP97 & RP53 & RP32 to the dsPIC33EPxxMC506*/
	/************** Code section for the low pin count devices ******/
	__builtin_write_OSCCONL(OSCCON & (~(1<<6))); // clear bit 6 

    RPINR19bits.U2RXR = 53;		// Make Pin RP53 U2RX
    RPOR7bits.RP97R = 3;	    // Make Pin RP97 U2TX
	RPINR12bits.FLT1R = 32;		// Make Pin RP32 FLT I/P

	__builtin_write_OSCCONL(OSCCON | (1<<6)); 	 // Set bit 6 	
	/****************************************************************/
    
   // ============= Motor PWM ======================

    // Center aligned PWM.
    // Note: The PWM period is set to dLoopInTcy/2 but since it counts up and 
    // and then down => the interrupt flag is set to 1 at zero => actual 
    // interrupt period is dLoopInTcy

	PHASE1 = LOOPTIME_TCY;
	PHASE2 = LOOPTIME_TCY;
	PHASE3 = LOOPTIME_TCY;
	PTPER = 2*LOOPTIME_TCY+1;

	PWMCON1 = 0x0204;	// Enable PWM output pins and configure them as 
	PWMCON2 = 0x0204;	// complementary mode
	PWMCON3 = 0x0204;

	//I/O pins initially controlled by GPIO
	IOCON1 = 0;
	IOCON2 = 0;
	IOCON3 = 0;

	//configure deadtime
	DTR1 = 0x0000;
	DTR2 = 0x0000;
	DTR3 = 0x0000;

	ALTDTR1 = DDEADTIME;	// 700 ns of dead time
	ALTDTR2 = DDEADTIME;	// 700 ns of dead time
	ALTDTR3 = DDEADTIME;	// 700 ns of dead time

	
	FCLCON1 = 0x3;     //Fault disabled
	FCLCON2 = 0x3;     //Fault disabled
	FCLCON3 = 0x3;     //Fault disabled

	PTCON2 = 0x0000;	// Divide by 1 to generate PWM

    PDC1 = MIN_DUTY;   // Initialise the duty registers
    PDC2 = MIN_DUTY;
    PDC3 = MIN_DUTY;

	IPC23bits.PWM1IP = 4;	// PWM Interrupt Priority 4
	IPC23bits.PWM2IP = 4;	// PWM Interrupt Priority 4
	IPC24bits.PWM3IP = 4;	// PWM Interrupt Priority 4
	IFS5bits.PWM1IF=0;		// Clearing the PWM Interrupt Flag
	IEC5bits.PWM1IE=0;		// Enabling the PWM interrupt

    PTCON = 0x8000;         // Enable PWM for center aligned operation

	//I/O pins controlled by PWM
	IOCON1 = 0xC000;
	Delay(100);			    // Adding this delay allows enough time for high-ESR-type C61 to recover
	IOCON2 = 0xC000;
	Delay(100);			    // Adding this delay allows enough time for high-ESR-type C61 to recover	
	IOCON3 = 0xC000;

    // SEVTCMP: Special Event Compare Count Register 
    // Phase of ADC capture set relative to PWM cycle: 0 offset and counting up
	SEVTCMP = 0;

	// ============= ADC - Measure Current & Pot ======================
    // ADC setup for simultanous sampling on 
    //      CH0=AN13, CH1=AN0, CH2=AN1, CH3=AN2. 
    // Sampling triggered by PWM and stored in signed fractional form.

    // Signed fractional (DOUT = sddd dddd dd00 0000)
    AD1CON1bits.FORM = 3;    
	AD1CON1bits.SSRC = 3;
	AD1CON1bits.SSRCG = 0;
    // Simultaneous Sample Select bit (only applicable when CHPS = 01 or 1x)
    // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
    // Samples CH0 and CH1 simultaneously (when CHPS = 01)
    AD1CON1bits.SIMSAM = 1;  
    // Sampling begins immediately after last conversion completes. 
    // SAMP bit is auto set.
    AD1CON1bits.ASAM = 1;  


    AD1CON2 = 0;
    // Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
    AD1CON2bits.CHPS = 2;  


    AD1CON3 = 0;
    // A/D Conversion Clock Select bits = 6 * Tcy
    AD1CON3bits.ADCS = 6;  


 /* ADCHS: ADC Input Channel Select Register */
    AD1CHS0 = 0;
    // CH0 is AN13 for POT
    AD1CHS0bits.CH0SA = 13;
    // CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2
    AD1CHS123bits.CH123SA = 0;

    /* ADCSSL: ADC Input Scan Select Register */
    AD1CSSL = 0;

    // Turn on A/D module
    AD1CON1bits.ADON = 1;

	// Wait until first conversion takes place to measure offsets.
	Delay(100);

    //Fault enabled 
    FCLCON1 = 0x00FD;  //Fault enabled Fault SRC - Fault 32
	FCLCON2 = 0x00FD;  //Fault enabled Fault SRC - Fault 32
	FCLCON3 = 0x00FD;  //Fault enabled Fault SRC - Fault 32
	return;
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: ResetPeriph                                                 */
/* Function parameters: None                                                  */
/* Function return: None                                                      */
/* Description: Reset the peripherals during runtime/reset configurations     */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void ResetPeriph(void)
{


    // clear and Enable ADC interrupt 
    IFS0bits.AD1IF = 0; 
    IEC0bits.AD1IE = 1;

   /* Initialise duty regs */ 
    PDC1 = MIN_DUTY;
    PDC2 = MIN_DUTY;
    PDC3 = MIN_DUTY;
    return;

}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/******************************************************************************/
/* Function name: Delay                                                       */
/* Function parameters: Delay_Count                                           */
/* Function return: None                                                      */
/* Description: Delay Routine - Can generate Delay in multiple of 100us	      */
/******************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Delay(unsigned int Delay_Count)
{
	int i;
	while (Delay_Count-- > 0)
	{
		for (i = 0;i < 1000;i++);
	}
	return;
}

