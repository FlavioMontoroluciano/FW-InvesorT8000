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



;*******************************************************************
; Routines: OpenLoop
;
;*******************************************************************

; Common to all routines in file

          .include "general.inc"
          .include "openloop.inc"

;*******************************************************************
; OpenLoop
;  
;Description:        
;
;Equations:
;     qDeltaFlux = Kdelta * qVelMech
;     qAngFlux = qAngFlux + Kdelta * qVelMech           ;; rotor flux angle    
;
;     qKdelta = (2^15) * 2 * iPoles * fLoopPeriod * fScaleMechRPS
;       where qVelMech is the mechanical velocity in RPS scaled by fScaleMechRPS
;       and the iPoles is required to get Flux vel from Mech vel
;       and the 2 is to scale +/- 2*pi into +/- pi
;
;Functional prototype:
; 
; void OpenLoop( void )
;
;On Entry:   OpenLoopParm structure must contain 
;
;On Exit:    OpenLoopParm will contain 
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0
;         CORCON.IF    = 0
;
; Support routines required: None
;
; Local Stack usage: 0
;
; Registers modified: ??w4,w5,AccA
;
; Timing: ??8 instruction cycles
;
;*******************************************************************
;
;=================== CODE =====================
          .section  .text

; Register usage for OpenLoop

          .equ Work0W,  w4   ; Working register
          .equ Work1W,  w5   ; Working register

          .global   _OpenLoop
          .global   OpenLoop

_OpenLoop:
OpenLoop:
          mov.w     _OpenLoopParm+OpLoop_qVelMech,Work0W
          mov.w     _OpenLoopParm+OpLoop_qKdelta,Work1W
          mpy       Work0W*Work1W,A
          sac       A,Work0W
          mov.w     Work0W,_OpenLoopParm+OpLoop_qDeltaFlux

     ;; qAngFlux = qAngFlux + qDeltaFlux
          mov.w     _OpenLoopParm+OpLoop_qAngFlux,Work1W
          add.w     Work0W,Work1W,Work0W
          mov.w     Work0W,_OpenLoopParm+OpLoop_qAngFlux
          return


;*******************************************************************
; void InitOpenLoop(void)
;         Initialize private OpenLoop variables.  
;*******************************************************************

; Register usage for InitOpenLoop


;*******************************************************************

          .global   _InitOpenLoop
          .global   InitOpenLoop
_InitOpenLoop:
InitOpenLoop:

          clr.w     _OpenLoopParm+OpLoop_qAngFlux
          clr.w     _OpenLoopParm+OpLoop_qDeltaFlux
          return

          .end
