#ifndef Estim_H
#define Estim_H


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

#include "UserParms.h"


	
//------------------  C API for Control routine ---------------------

typedef struct {
    int   			  qDeltaT;      // Integration constant
    int   			  qRho;    	    // 
    long  			  qRhoStateVar; //     
    int   			  qOmegaMr;     // 
    int   			  qLastIalpha;  // 
    int   			  qLastIbeta;   // 
    int   			  qDIalpha;     // 
    int   			  qDIbeta;      // 
	int				  qEsa;			// 
	int				  qEsb;			// 
	int				  qEsd;			// 
	int				  qEsq;			// 
	int				  qImr;			// 
	long			  qImrStateVar;	// 
	int				  qDiCounter;	// 
	int				  qVIndalpha;
	int				  qVIndbeta;
	int				  qEsdf;
	long			  qEsdStateVar;
	int				  qEsqf;
	long			  qEsqStateVar;
	int				  qKfilterdq;
	int   			  qVelEstim; 			// Estimated speed in 1.15
	int   			  qVelEstimFilterK; 	// Filter Konstant for Estimated speed in 1.15
	long   			  qVelEstimStateVar; 	// State Variable for Estimated speed in 1.31
	int   			  qOmeg2Estim; 			// Estimated speed in 1.15
	int				  qVelEstimMech;// estimated mechanical speed
	int				  qInvPol;		// 1/polpare numbare
    int   			  qLastValpha;  // Value from last control step Ialpha 
    int   			  qLastVbeta;   // Value from last control step Ibeta
	int				  qDIalphaHS;			// dIalpha/dt
	int				  qDIbetaHS;			// dIbeta/dt
	int				  qLastIalphaHS[8];		//  last  value for Ialpha
	int				  qLastIbetaHS[8];			// last  value for Ibeta
    int				  qDIlimitLS;			// dIalphabeta/dt
	int				  qDIlimitHS;			// dIalphabeta/dt
	long			  qIqInvTr2;




    } tEstimParm;


typedef struct {
	int				   qRs;			//
	int				   qLsDt;		//
	int				   qInvPsi;		//
	int				   qInvTr;		//
	int				   qRrInvTr;	//
	int				   qInvTr2;
    } tMotorEstimParm;

void	Estim(void);
void	InitEstimParm(void);
#endif
