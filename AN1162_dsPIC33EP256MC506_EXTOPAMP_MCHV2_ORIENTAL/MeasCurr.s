; ******************************************************************************
; © 2012 Microchip Technology Inc.
; 
; SOFTWARE LICENSE AGREEMENT:
; Microchip Technology Incorporated ("Microchip") retains all ownership and 
; intellectual property rights in the code accompanying this message and in all 
; derivatives hereto.  You may use this code, and any derivatives created by 
; any person or entity by or on your behalf, exclusively with Microchip's
; proprietary products.  Your acceptance and/or use of this code constitutes 
; agreement to the terms and conditions of this notice.
;
; CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
; WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
; TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
; PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
; PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
;
; YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
; IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
; STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
; PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
; ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
; ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
; ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
; THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
; HAVE THIS CODE DEVELOPED.
;
; You agree that you are solely responsible for testing the code and 
; determining its suitability.  Microchip has no obligation to modify, test, 
; certify, or support the code.
;
; ******************************************************************************
;*******************************************************************
; MeasCompCurr
;  
;Description:        
;  Read Channels 1 & 2 of ADC, scale them as signed fractional values 
;  using qKa, qKb and put the results qIa and qIb of ParkParm. 
;  Running average value of ADC-Ave is maintained and subtracted from 
;  ADC value before scaling.
;
;  Specifically the offset is accumulated as a 32 bit signed integer       
;         iOffset += (ADC-Offset)
;  and is used to correct the raw ADC by
;         CorrADC = ADCBUFn - iOffset/2^16
;  which gives an offset time constant of ~ MeasurementPeriod*2^16
;
;  Do not call this routine until conversion is completed.
;
;  Scaling constant, qKa and qKb, must be set elsewhere such that
;         qIa = 2 * qKa * CorrADC1
;         qIb = 2 * qKb * CorrADC2
;  The factor of 2 is designed to allow qKa & qKb to be given in 1.15.
;
;
;Functional prototypes:  
;         void MeasCompCurr( void );
;         void InitMeasCompCurr( short iOffset_a, short iOffset_b );
;
;On Start:   Must call InitMeasCompCurr.
;
;On Entry:   MeasCurrParm structure must contain qKa & qKb. ADC channels 1 & 2
;            must contain signed fractional value.
;
;On Exit:    ParkParm will contain qIa & qIb.
;
;Parameters: 
; Input arguments: None
;
; Return:
;   Void
;
; SFR Settings required:
;         CORCON.SATA  = 0
;     If there is any chance that Accumulator will overflow must set
;         CORCON.SATDW = 1  
;
; Support routines required: None
;
; Local Stack usage: None
;
; Registers modified: w0,w1,w4,w5
;
; Timing: 29 cycles
;
;*******************************************************************

          .include "general.inc"

; External references
          .include "MeasCurr.inc"
          .include "Park.inc"

; Register usage
          .equ Work0W,   w4
          .equ Work1W,   w5
          .equ OffsetHW, w3
	
          .global   _MeasCompCurr
          .global   MeasCompCurr

_MeasCompCurr:
MeasCompCurr:

     ;; CorrADC1 = ADCBUF2 - iOffsetHa/2^16
     ;; qIa = 2 * qKa * CorrADC1
          mov.w     _MeasCurrParm+ADC_iOffsetHa,w0
          sub.w     _ADC1BUF2,WREG               ; w0 = ADC - Offset
          clr.w     w1
          btsc      w0,#15
          setm      w1
          mov.w     w0,w5
          mov.w     _MeasCurrParm+ADC_qKa,w4
          mpy       w4*w5,A
          sac       A,#-1,w4
          mov.w     w4,_ParkParm+Park_qIa

     ;; iOffset += (ADC-Offset)
          add       _MeasCurrParm+ADC_iOffsetLa    
          mov.w     w1,w0
          addc      _MeasCurrParm+ADC_iOffsetHa    

     ;; CorrADC2 = ADCBUF1 - iOffsetHb/2^16
     ;; qIb = 2 * qKb * CorrADC2
          mov.w     _MeasCurrParm+ADC_iOffsetHb,w0
          sub.w     _ADC1BUF1,WREG               ; w0 = ADC - Offset
          clr.w     w1
          btsc      w0,#15
          setm      w1
          mov.w     w0,w5
          mov.w     _MeasCurrParm+ADC_qKb,w4
          mpy       w4*w5,A
          sac       A,#-1,w4
          mov.w     w4,_ParkParm+Park_qIb

     ;; iOffset += (ADC-Offset)
          add       _MeasCurrParm+ADC_iOffsetLb    
          mov.w     w1,w0
          addc      _MeasCurrParm+ADC_iOffsetHb    

          return

          .global   _MeasCompCurr2
          .global   MeasCompCurr2

_MeasCompCurr2:
MeasCompCurr2:

     ;; CorrADC1 = ADCBUF2 - iOffsetHa/2^16
     ;; qIa = 2 * qKa * CorrADC1
          mov.w     _MeasCurrParm+ADC_iOffsetHa,w0
          sub.w     _ADC1BUF2,WREG               ; w0 = ADC - Offset
          clr.w     w1
          btsc      w0,#15
          setm      w1
          mov.w     w0,w5
          mov.w     _MeasCurrParm+ADC_qKa,w4
          mpy       w4*w5,A
          sac       A,#-1,w4
          mov.w     w4,_ParkParm+Park_qIa

     ;; CorrADC2 = ADCBUF1 - iOffsetHb/2^16
     ;; qIb = 2 * qKb * CorrADC2
          mov.w     _MeasCurrParm+ADC_iOffsetHb,w0
          sub.w     _ADC1BUF1,WREG               ; w0 = ADC - Offset
          clr.w     w1
          btsc      w0,#15
          setm      w1
          mov.w     w0,w5
          mov.w     _MeasCurrParm+ADC_qKb,w4
          mpy       w4*w5,A
          sac       A,#-1,w4
          mov.w     w4,_ParkParm+Park_qIb

          return



          .global   _InitMeasCompCurr
          .global   InitMeasCompCurr

_InitMeasCompCurr:
InitMeasCompCurr:

          clr.w     _MeasCurrParm+ADC_iOffsetLa    
          mov.w     w0,_MeasCurrParm+ADC_iOffsetHa    
          clr.w     _MeasCurrParm+ADC_iOffsetLb    
          mov.w     w1,_MeasCurrParm+ADC_iOffsetHb    
          return

          .end
