#ifndef USERPARMS_H
#define USERPARMS_H

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
*******************************************************************************/

#define SPEED_LOOP_CNT       20    // Mention the Speed loop count number of PWM cycles 50us * 20 = 1ms loop
#define DEADTIME_SEC  0.000002     // Dead time in seconds - 2us

#define PWM_DT_ERRATA

#define DDEADTIME      (unsigned int)(DEADTIME_SEC*FCY_HZ)	// Dead time in dTcys

#ifdef PWM_DT_ERRATA
    #define MIN_DUTY  (unsigned int)(DDEADTIME/2 + 1)        // Should be >= DDEADTIME/2 for PWM Errata workaround
#else
    #define MIN_DUTY  0x00
#endif

// This definition can be used to bypass the velocity control loop.
// If TORQUE_MODE is defined, then the potentiometer demand value
// is passed directly to the Q (torque) control loop.
#undef	TORQUE_MODE


// This define is used in case that Imr reference is not calculated,
// but predefined
#define USEIMRREF

// This is a macro used to convert a floating point value to a
// fixed point fractional value.
#define Q15(X) \
   ((X < 0.0) ? (int)(32768*(X) - 0.5) : (int)(32767*(X) + 0.5)) ;

//************** PI Coefficients **************
//******** D Control Loop Coefficients *******
#define     dDqKp           Q15(0.1);
#define     dDqKi           Q15(0.01);        
#define     dDqKc           Q15(0.9999); 
#define     dDqOutMax       Q15(0.7071);

//******** Q Control Loop Coefficients *******
#define     dQqKp           Q15(0.1); 
#define     dQqKi           Q15(0.01); 
#define     dQqKc           Q15(0.9999);
#define     dQqOutMax       Q15(0.7071);

//*** Velocity Control Loop Coefficients *****
#define     dQrefqKp        Q15(0.05);
#define     dQrefqKi        Q15(0.005);
#define     dQrefqKc        Q15(0.9999);
#define     dQrefqOutMax    Q15(0.045);        // 0.045 limit to 0.24A rms (0.00023 A/bit)

//************** ADC Scaling **************
// Scaling constants: Determined by calibration or hardware design. 

#define     dqK             Q15(0.5);
#define     dqKa            Q15(-0.5);	// 0.5 means 1:1 current gain
#define     dqKb            Q15(-0.5);	// 0.5 means 1:1 current gain



//************** Real Time Data Monitor, RTDM *******************

#undef RTDM_DEMO		// This definition enabled Real Time Data Monitor, UART interrupts
					    // to handle RTDM protocol, and array declarations for buffering
					    // information in real time

#ifdef RTDM_DEMO
#define DATA_BUFFER_SIZE 150  //Size in 16-bit Words
#define SNAPDELAY	5 // In number of PWM Interrupts
#define	SNAP1		ParkParm.qIa
#define	SNAP2		ParkParm.qIq
#define SNAP3	    EstimParm.qVelEstim
#define SNAP4	    EstimParm.qRho
#endif

//**************  Motor Parameters **************
//**************  support xls file definitions start **************
// please check project folder for support tuning_params.xls file

#define NOPOLESPAIRS        2       // Number of pole pairs

/* nominal motor speed */
#define NOMINAL_SPEED_RPM 1600

/* Magnetizing current reference value */
#define	MAGNETIZING_CURRENT	151	

/* normalized ls/dt value */
#define NORM_LSDT 8226

/* normalized rs value */
#define NORM_RS  17421

/* inverse flux */
#define NORM_INVPSI  4672

/* normalized Tsample/Tr */
#define NORM_INVTR 275

/* normalized inverse RRTR */
#define NORM_RRINVTR 182

/* normalized inverse Tr */
#define NORM_INVTR2 1711

/* normalized dt value */
#define NORM_DELTAT  1673

// Limitation constants 
/* di = i(t1)-i(t2) limitation */ 
/* high speed limitation, for dt 50us */
/* the value can be taken from attached xls file */
#define D_ILIMIT_HS 197
/* low speed limitation, for dt 8*50us */
#define D_ILIMIT_LS 1398

// Filters constants definitions  
/* BEMF filter for d-q components @ low speeds */
#define KFILTER_ESDQ 374

/* estimated speed filter constatn */
/* a separate constant for field weakening could be defined */
#define KFILTER_VELESTIM 1092

//**************  support xls file definitions end **************

#endif
