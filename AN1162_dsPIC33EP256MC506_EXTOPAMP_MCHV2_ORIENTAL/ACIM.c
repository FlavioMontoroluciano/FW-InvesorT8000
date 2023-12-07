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
#define INITIALIZE
#include "RTDM.h"
#include "general.h"   /* includes types definitions used */
#include "Parms.h"
#include "svgen.h"
#include "ReadADC.h"
#include "MeasCurr.h"
#include "FdWeak.h"
#include "Control.h"
#include "PI.h"
#include "Park.h"
#include "OpenLoop.h"
#include "UserParms.h"
#include "periph.h"
#include "Estim.h"

/******************************************************/

#define MINIMUM_SPEED_CONTROL MINIMUM_SPEED_CONTROL_RPM*NOPOLESPAIRS


// Pushbutton pin connections for the motor control PCB.
#define pinButton1S3         !PORTBbits.RB8   // Updated to MCHV

#ifdef RTDM_DEMO

int RecorderBuffer1[DATA_BUFFER_SIZE]; //Buffer to store the data samples for the DMCI data viewer Graph1
int RecorderBuffer2[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph2
int RecorderBuffer3[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph3
int RecorderBuffer4[DATA_BUFFER_SIZE];	//Buffer to store the data samples for the DMCI data viewer Graph4

int * PtrRecBuffer1 = &RecorderBuffer1[0];	//Tail pointer for the DMCI Graph1
int * PtrRecBuffer2 = &RecorderBuffer2[0];	//Tail pointer for the DMCI Graph2
int * PtrRecBuffer3 = &RecorderBuffer3[0];	//Tail pointer for the DMCI Graph3
int * PtrRecBuffer4 = &RecorderBuffer4[0];	//Tail pointer for the DMCI Graph4
int * RecBuffUpperLimit = RecorderBuffer4 + DATA_BUFFER_SIZE -1;	//Buffer Recorder Upper Limit
typedef struct DMCIFlags{
		    unsigned Recorder : 1;	// Flag needs to be set to start buffering data
			unsigned unused : 15;  
} DMCIFLAGS;
DMCIFLAGS DMCIFlags;
int	SnapCount = 0;

int SnapShotDelayCnt = 0;
int SnapShotDelay = SNAPDELAY;

#endif // End of #ifdef RTDM

unsigned short uWork;
short iCntsPerRev;
short iDeltaPos;
unsigned int test;
int speed_loop_cnt = 0;
int count_ramp=0;


union   {
        struct
            {
            unsigned OpenLoop           :1;
            unsigned RunMotor           :1;
            unsigned ChangeMode         :1;
            unsigned ChangeSpeed        :1;
            unsigned                    :12;

            }bit;
        int Word;
        } uGF;        // general flags

  

tPIParm     PIParmQ;
tPIParm     PIParmQref;
tPIParm     PIParmD;

tReadADCParm ReadADCParm;
tFdWeakParm FdWeakParm;
tMotorParm MotorParm;
tCtrlParm CtrlParm;
tMeasCurrParm MeasCurrParm;
tOpenLoopParm OpenLoopParm;
tSVGenParm SVGenParm;
tParkParm       ParkParm;
tSincosParm     SincosParm;

extern  tEstimParm              EstimParm;


/******************************************************/
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void);
void SetupBoard( void );
void InitUserParms(void);
void DoControl( void );
void InitEstimParm(void);
void DebounceDelay(void);

/************* START OF MAIN FUNCTION ***************/

int main ( void )
{
    /* inti dsPIC */
    InitPeriph();
    
    // init user parameters
    InitUserParms();
    
    // init estimator parameters
    InitEstimParm();

#ifdef RTDM_DEMO
    RTDM_Start();  // Configure the UART module used by RTDM
				   // it also initializes the RTDM variables
#endif

    while(1)
        {
        uGF.Word = 0;                   // clear flags
        
        // init Mode
        uGF.bit.OpenLoop = 1;           // start in openloop

    	// Disable ADC interrupt
    	IEC0bits.AD1IE = 0;
                
        // zero out i sums 
        PIParmD.qdSum = 0;
        PIParmQ.qdSum = 0;
        PIParmQref.qdSum = 0;
     
         // Enable ADC interrupt and begin main loop timing
        IFS0bits.AD1IF = 0; 
        IEC0bits.AD1IE = 1;
  
        while(!pinButton1S3)                  //wait here until button 1 is pressed 
        {
	        #ifdef RTDM_DEMO
	        	RTDM_ProcessMsgs();			//RTDM process incoming and outgoing messages
			#endif	
			
	        ClrWdt();               
            // Start offset accumulation    //and accumulate current offset while waiting
            MeasCompCurr();
         }
         while(pinButton1S3);                  //when button 1 is released 
         DebounceDelay();
         uGF.bit.RunMotor = 1;               //then start motor

        // Run the motor
        uGF.bit.ChangeMode = 1;
        uGF.bit.OpenLoop = 1;
        while(1)
        {
	           while(!pinButton1S3)                  //wait here until button 1 is pressed 
	           {
		           	#ifdef RTDM_DEMO
	        		RTDM_ProcessMsgs();			//RTDM process incoming and outgoing messages
					#endif	
		        } 
               while(pinButton1S3);                  //when button 1 is released
               DebounceDelay();
	           // Switch between open and closed loop
               uGF.bit.ChangeMode = 1;
               uGF.bit.OpenLoop = ! uGF.bit.OpenLoop;
         }   // End of Run Motor loop
        
     } // End of Main loop
}

//---------------------------------------------------------------------
// Executes one PI itteration for each of the three loops Id,Iq,Speed
void DoControl( void )
{
short i;

    // Assume ADC channel 0 has raw A/D value in signed fractional form from
    // speed pot
    ReadSignedADC0( &ReadADCParm );

    // reference speed is read by ADC (max=0x7FC0/8=4088)
    CtrlParm.qVelRef = ReadADCParm.qADValue>>3;

    if( uGF.bit.OpenLoop )
        {
        // OPENLOOP:  force rotating angle,Vd,Vq

        if( uGF.bit.ChangeMode )
            {
            // just changed to openloop
            uGF.bit.ChangeMode = 0;

            // VqRef & VdRef not used
            CtrlParm.qVqRef = 0;
            CtrlParm.qVdRef = 0;
            }

        OpenLoopParm.qVelMech = CtrlParm.qVelRef;

        // calc rotational angle of rotor flux in 1.15 format
 
        ParkParm.qVq = 0;

        if( OpenLoopParm.qVelMech >= 0 )
            i = OpenLoopParm.qVelMech;  
        else
            i = -OpenLoopParm.qVelMech;

        uWork = i <<3;
        
        /* limit high the voltage, for deadtime counteract */
        if( uWork > 0x5a82 )
            uWork = 0x5a82;
        /* limit low the voltage, for compensate stator voltage drop */
        if( uWork < 0x1000 )
            uWork = 0x1000;

        ParkParm.qVd = uWork;
        
        /* generate the angle */
        OpenLoop();
        ParkParm.qAngle = OpenLoopParm.qAngFlux; 
    }			// end open loop
    else		// Closed Loop Vector Control
    {

        if( uGF.bit.ChangeMode )
        {
            // just changed from openloop
            uGF.bit.ChangeMode = 0;
        }

        // Calculate qVdRef from field weakening
        FdWeakening();
               
                
        // Check to see if new velocity information is available by comparing
        // the number of interrupts per velocity calculation against the
        // number of velocity count samples taken.  If new velocity info
        // is available, calculate the new velocity value and execute
        // the speed control loop.
        if(speed_loop_cnt > SPEED_LOOP_CNT) 
        {
			speed_loop_cnt = 0;

#ifndef TORQUE_MODE
            PIParmQref.qInRef  = CtrlParm.qVelRef;
			PIParmQref.qInMeas = EstimParm.qVelEstim;
            CalcPI(&PIParmQref);
            CtrlParm.qVqRef    = PIParmQref.qOut;
#endif
        }
        else 
        {
            speed_loop_cnt ++;
		}
       
        // If the application is running in torque mode, the velocity
        // control loop is bypassed.  The velocity reference value, read
        // from the potentiometer, is used directly as the torque 
        // reference, VqRef.

#ifdef	TORQUE_MODE
       	CtrlParm.qVqRef = CtrlParm.qVelRef * 4;
#endif

        
        // PI control for Q
        PIParmQ.qInMeas = ParkParm.qIq;
        PIParmQ.qInRef  = CtrlParm.qVqRef;
        CalcPI(&PIParmQ);
        ParkParm.qVq    = PIParmQ.qOut;
       

        // PI control for D
        PIParmD.qInMeas = ParkParm.qId;
        PIParmD.qInRef  = CtrlParm.qVdRef;
        CalcPI(&PIParmD);
        ParkParm.qVd    = PIParmD.qOut;

        }


}

//---------------------------------------------------------------------
// The ADC ISR does speed calculation and executes the vector update loop.
// The ADC sample and conversion is triggered by the PWM period.
// The speed calculation assumes a fixed time interval between calculations.
//---------------------------------------------------------------------
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void)
{
    // Clear Interrupt Flag
    IFS0bits.AD1IF = 0;
        
        if( uGF.bit.RunMotor )
                {
                /* get the current from ADC bufs */
                MeasCompCurr2();
                
                /* Clarke and Park */                                        
                ClarkePark();
                
                /* estimate speed & angle */
                Estim();
                               
                // Calculate control values
                DoControl();

                if (!uGF.bit.OpenLoop)
                {
                        SincosParm.qAngle=EstimParm.qRho;
                } else
                {
                        SincosParm.qAngle=ParkParm.qAngle;
                }

                SinCos();

                ParkParm.qSin=SincosParm.qSin;
                ParkParm.qCos=SincosParm.qCos;

                InvPark();    

                // Calculate Vr1,Vr2,Vr3 from qValpha, qVbeta 
                CalcRefVec();

                // Calculate and set PWM duty cycles from Vr1,Vr2,Vr3
                CalcSVGen();
              }    
	#ifdef RTDM_DEMO
    /********************* DMCI Dynamic Data Views  ***************************/
	/********************** RECORDING MOTOR PHASE VALUES ***************/
	if(DMCIFlags.Recorder)
	{
		if(SnapShotDelayCnt++ == SnapShotDelay)
		{
			SnapShotDelayCnt = 0;
			*PtrRecBuffer1++ 	= SNAP1;
			*PtrRecBuffer2++	= SNAP2;
			*PtrRecBuffer3++	= SNAP3;
			*PtrRecBuffer4++	= SNAP4;
			
			if(PtrRecBuffer4 > RecBuffUpperLimit)
			{
				PtrRecBuffer1 = RecorderBuffer1;
				PtrRecBuffer2 = RecorderBuffer2;
		        PtrRecBuffer3 = RecorderBuffer3;
		        PtrRecBuffer4 = RecorderBuffer4;
		        DMCIFlags.Recorder = 0;
		    }   
		}
	}
	#endif              
      
}

void InitUserParms(void)
{

    // Turn saturation on to insure that overflows will be handled smoothly.
    CORCONbits.SATA  = 0;

    // Setup required parameters

    // Pick scaling values to be 8 times nominal for speed and current
        
    // Use 8 times nominal mechanical speed of motor (in RPM) for scaling
    MotorParm.iScaleMechRPM  = NOMINAL_SPEED_RPM*8;
    
    // Number of pole pairs
    MotorParm.iPoles = NOPOLESPAIRS;

    // Basic loop period (in sec).  (PWM interrupt period)
    MotorParm.fLoopPeriod = LOOPTIME_TCY * TCY_SEC;  //Loop period in cycles * sec/cycle

    // Scale mechanical speed of motor (in rev/sec)
    MotorParm.fScaleMechRPS = MotorParm.iScaleMechRPM/60.0;


    // ============= Open Loop ======================
        
    OpenLoopParm.qKdelta = 32767.0 * 2 * MotorParm.iPoles * MotorParm.fLoopPeriod * MotorParm.fScaleMechRPS;
        
    InitOpenLoop();
                
    // ============= Field Weakening ===============
    // Field Weakening constant for constant torque range
    FdWeakParm.qImr = MAGNETIZING_CURRENT;       // Flux reference value
        
    // ============= PI D Term ===============      
    PIParmD.qKp = dDqKp;       
    PIParmD.qKi = dDqKi;              
    PIParmD.qKc = dDqKc;       
    PIParmD.qOutMax = dDqOutMax;
    PIParmD.qOutMin = -PIParmD.qOutMax;

    InitPI(&PIParmD);

    // ============= PI Q Term ===============
    PIParmQ.qKp = dQqKp;    
    PIParmQ.qKi = dQqKi;
    PIParmQ.qKc = dQqKc;
    PIParmQ.qOutMax = dQqOutMax;
    PIParmQ.qOutMin = -PIParmQ.qOutMax;
        
    InitPI(&PIParmQ);
        
    // ============= PI Qref Term ===============
    PIParmQref.qKp = dQrefqKp;       
    PIParmQref.qKi = dQrefqKi;       
    PIParmQref.qKc = dQrefqKc;       
    PIParmQref.qOutMax = dQrefqOutMax;   
    PIParmQref.qOutMin = -PIParmQref.qOutMax;

    InitPI(&PIParmQref);
    
    // ============= ADC - Measure Current & Pot ======================

    // Scaling constants: Determined by calibration or hardware design.
    ReadADCParm.qK      = dqK;    

    MeasCurrParm.qKa    = dqKa;    
    MeasCurrParm.qKb    = dqKb;  
    
    // Speed reference value
    CtrlParm.qVelRef=0; 
               
    SVGenParm.iPWMPeriod = LOOPTIME_TCY;

    /* Inital offsets for current measurment */
    InitMeasCompCurr( ADC1BUF2, ADC1BUF1);
        
}

void DebounceDelay(void)
{
	long i;
	for (i = 0;i < 100000;i++);
	return;
}



