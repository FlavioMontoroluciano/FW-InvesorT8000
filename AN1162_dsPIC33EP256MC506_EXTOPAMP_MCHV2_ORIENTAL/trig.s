;/**********************************************************************
;* � 2012 Microchip Technology Inc.
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
; Trig
;  
;Description:        
;  Calculate Sine and Cosine for specified angle using linear interpolation
;  on a table of 128 words.
;
;  The table is stored in program memory space and accessed using 
;  program space visibility (PSV).  CORCON and PSVPAG are preserved
;  during the routine to avoid compiler conflicts.
;
;  This routine works the same for both integer scaling and 1.15 scaling.
;
;  For integer scaling the Angle is scaled such that 0 <= Angle < 2*pi 
;         corresponds to 0 <= Ang < 0xFFFF. The resulting Sin and Cos
;         values are returned scaled to -32769 -> 32767 i.e. (0x8000 -> 0x7FFF).
;
;  For 1.15 scaling the Angle is scaled such that -pi <= Angle < pi 
;         corresponds to -1 -> 0.9999 i.e. (0x8000 <= Ang < 0x7FFF). The 
;         resulting Sin and Cos values are returned scaled to -1 -> 0.9999
;         i.e. (0x8000 -> 0x7FFF).
;
;Functional prototype:
;  void SinCos( void )
;
;On Entry:   SincosParm structure must contain qAngle
;On Exit:    SincosParm will contain qSin, qCos.  qAngle is unchanged.     
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.IF    = 0
;         CORCON.PSV   = 1
;
;
; Support routines required: None
;
; Local Stack usage: 0
;
; Registers modified: w0-w7
;
; Timing:
;  About 41 instruction cycles
;
;*******************************************************************
;
          .include "general.inc"

; External references
          .include "park.inc"

; Constants
          .equ TableSize,128

; Local register usage
          .equ Work0W, w0        ; Working register
          .equ Work1W, w1        ; Working register

          .equ RemainderW, w2    ; Fraction for interpolation: 0->0xFFFF
          .equ IndexW, w3        ; Index into table

          .equ pTabPtrW, w4      ; Pointer into table 
          .equ pTabBaseW,w5      ; Pointer into table base

          .equ Y0W,w6            ; Y0 = SinTable[Index]
          .equ SincosParmW,w7      ; Base of SincosParm structure

      ;; Note: RemainderW and Work0W must be even registers


;=================== LOCAL DATA =====================

          .section .eps
         
          .align	256
SinTable: 
  .word 0,1608,3212,4808,6393,7962,9512,11039
  .word 12540,14010,15446,16846,18205,19520,20787,22005
  .word 23170,24279,25330,26319,27245,28106,28898,29621
  .word 30273,30852,31357,31785,32138,32413,32610,32728
  .word 32767,32728,32610,32413,32138,31785,31357,30852
  .word 30273,29621,28898,28106,27245,26319,25330,24279
  .word 23170,22005,20787,19520,18205,16846,15446,14010
  .word 12540,11039,9512,7962,6393,4808,3212,1608
  .word 0,-1608,-3212,-4808,-6393,-7962,-9512,-11039
  .word -12540,-14010,-15446,-16846,-18205,-19520,-20787,-22005
  .word -23170,-24279,-25330,-26319,-27245,-28106,-28898,-29621
  .word -30273,-30852,-31357,-31785,-32138,-32413,-32610,-32728
  .word -32767,-32728,-32610,-32413,-32138,-31785,-31357,-30852
  .word -30273,-29621,-28898,-28106,-27245,-26319,-25330,-24279
  .word -23170,-22005,-20787,-19520,-18205,-16846,-15446,-14010
  .word -12540,-11039,-9512,-7962,-6393,-4808,-3212,-1608

;=================== CODE =====================

          .section  .text
          .global   _SinCos
          .global   SinCos

_SinCos:
SinCos:

	 ;; Save the current CORCON and PSVPAG register
	 	  mov		CORCON,w0
	 	  push.d	w0
		
     ;; Base of qAngle, qSin, qCos group in SincosParm structure
          mov.w     #_SincosParm+Sincos_qAngle,SincosParmW     

     ;; Calculate Index and Remainder for fetching and interpolating Sin
          mov.w     #TableSize,Work0W
          mov.w     [SincosParmW++],Work1W        ; load qAngle & inc ptr to qCos
          mul.uu    Work0W,Work1W,RemainderW   ; high word in IndexW

     ;; Double Index since offsets are in bytes not words
          add.w     IndexW,IndexW,IndexW

     ;; Note at this point the IndexW register has a value 0x00nn where nn
     ;; is the offset in bytes from the TabBase.  If below we always
     ;; use BYTE operations on the IndexW register it will automatically
     ;; wrap properly for a TableSize of 128.
  
          mov.w     #SinTable,pTabBaseW     ; Pointer into table base

     ;; Check for zero remainder
          cp0.w     RemainderW
          bra       nz,jInterpolate

     ;; Zero remainder allows us to skip the interpolation and use the 
     ;; table value directly

          add.w     IndexW,pTabBaseW,pTabPtrW
          mov.w    [pTabPtrW],[SincosParmW++]    ; write qSin & inc pt to qCos

     ;; Add 0x40 to Sin index to get Cos index.  This may go off end of
     ;; table but if we use only BYTE operations the wrap is automatic.
          add.b     #0x40,IndexW
          add.w     IndexW,pTabBaseW,pTabPtrW

          mov.w     [pTabPtrW],[SincosParmW]      ; write qCos

     ;; Restore PSVPAG and CORCON to original states
          pop.d		w0
          mov		w0,CORCON
          return

jInterpolate:

     ;; Get Y1-Y0 = SinTable[Index+1] - SinTable[Index]  

          add.w     IndexW,pTabBaseW,pTabPtrW
          mov.w     [pTabPtrW],Y0W              ; Y0

          inc2.b    IndexW,IndexW               ; (Index += 2)&0xFF
          add.w     IndexW,pTabBaseW,pTabPtrW

          subr.w    Y0W,[pTabPtrW],Work0W      ; Y1 - Y0
  
     ;; Calcuate Delta = (Remainder*(Y1-Y0)) >> 16

          mul.us    RemainderW,Work0W,Work0W

     ;; Work1W contains upper word of (Remainder*(Y1-Y0)) 
     ;; *pSin = Y0 + Delta

          add.w     Work1W,Y0W,[SincosParmW++]   ; write qSin & inc pt to qCos

     ;; ================= COS =========================

     ;; Add 0x40 to Sin index to get Cos index.  This may go off end of
     ;; table but if we use only BYTE operations the wrap is automatic.
     ;; Actualy only add 0x3E since Index increment by two above
          add.b     #0x3E,IndexW
          add.w     IndexW,pTabBaseW,pTabPtrW

     ;; Get Y1-Y0 = SinTable[Index+1] - SinTable[Index]  

          add.w     IndexW,pTabBaseW,pTabPtrW
          mov.w     [pTabPtrW],Y0W              ; Y0

          inc2.b    IndexW,IndexW               ; (Index += 2)&0xFF
          add.w     IndexW,pTabBaseW,pTabPtrW

          subr.w    Y0W,[pTabPtrW],Work0W      ; Y1 - Y0
  
     ;; Calcuate Delta = (Remainder*(Y1-Y0)) >> 16

          mul.us    RemainderW,Work0W,Work0W

     ;; Work1W contains upper word of (Remainder*(Y1-Y0)) 
     ;; *pCos = Y0 + Delta

          add.w     Work1W,Y0W,[SincosParmW]     ; write qCos
          
     ;; Restore PSVPAG and CORCON to original states
          pop.d		w0
          mov		w0,CORCON
          return

          .end
