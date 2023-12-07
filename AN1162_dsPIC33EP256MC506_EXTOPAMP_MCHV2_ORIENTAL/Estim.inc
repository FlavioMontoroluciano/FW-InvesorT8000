;/**********************************************************************
;* © 2012 Microchip Technology Inc.
;*
;* SOFTWARE LICENSE AGREEMENT:
;* Microchip Technology Incorporated ("Microchip") retains all ownership and 
;* intellectual property rights in the code accompanying this message and in all 
;* derivatives hereto.  You may use this code, and any derivatives created by 
;* any person or entity by or on your behalf, exclusively with Microchip's
;* proprietary products.  Your acceptance and/or use of this code constitutes 
;* agreement to the terms and conditions of this notice.
;*
;* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
;* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
;* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
;* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
;* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
;*
;* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
;* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
;* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
;* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
;* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
;* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
;* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
;* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
;* HAVE THIS CODE DEVELOPED.
;*
;* You agree that you are solely responsible for testing the code and 
;* determining its suitability.  Microchip has no obligation to modify, test, 
;* certify, or support the code.
;*
;*******************************************************************************/

; Variables for Speed estimation

	  .equ Estim_qDeltaT,		0   ; 
      .equ Estim_qRho,			2   ; 
      .equ Estim_qRhoStateVar_L,4  	; 
      .equ Estim_qRhoStateVar_H,6  	; 
      .equ Estim_qOmegaMr,		8   ; 
	  .equ Estim_qLastIalpha,	10	; 
	  .equ Estim_qLastIbeta,	12	; 
	  .equ Estim_qDIalpha,		14	; 
	  .equ Estim_qDIbeta,		16	; 
	  .equ Estim_qEsa,			18	; 
	  .equ Estim_qEsb,			20	; 
	  .equ Estim_qEsd,			22	; 
	  .equ Estim_qEsq,			24	;
	  .equ Estim_qImr,			26	; 
	  .equ Estim_qImrStateVar_L,28  ;
	  .equ Estim_qImrStateVar_H,30  ;
	  .equ Estim_qDiCounter,	32	;
	  .equ Estim_qVIndalpha,	34	;
	  .equ Estim_qVIndbeta,		36	;
	  .equ Estim_qEsdf,			38	;
	  .equ Estim_qEsdStateVar_L,40	;
	  .equ Estim_qEsqf,			44 	;
	  .equ Estim_qEsqStateVar_L,46 	;
	  .equ Estim_qEsqStateVar_H,48 	;
	  .equ Estim_qKfilterdq,	50  	;
	  .equ Estim_qVelEstim,		52 	;			// Estimated speed in 1.15
	  .equ Estim_qVelEstimFilterK, 54 	; 	// Filter Konstant for Estimated speed in 1.15
	  .equ Estim_qVelEstimStateVar_L, 56 	; 	// State Variable for Estimated speed in 1.31
	  .equ Estim_qVelEstimStateVar_H, 58 	; 	// State Variable for Estimated speed in 1.31
	  .equ Estim_qOmegaMrMin,	60 	;
	  .equ Estim_qVelEstimMech, 62   ;
	  .equ Estim_qInvPol,       64 	;
	  .equ Estim_qLastValpha,	66 	; 
	  .equ Estim_qLastVbeta,	68 	; 


; Motor parameters

;tMotorEstimParm MotorEstimParm;
	.equ	Motor_qRs,			0
	.equ	Motor_qLsDt,		2
	.equ	Motor_qInvPsi,		4
	.equ	Motor_qInvTr,		6
	.equ	Motor_qRrInvTr,		8



	.extern	_EstimParm
	.extern	_MotorEstimParm
	.extern	_StartupParm
