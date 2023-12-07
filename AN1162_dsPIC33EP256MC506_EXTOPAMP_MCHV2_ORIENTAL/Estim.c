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


#include "Estim.h"
#include "EstimDef.h"
#include "park.h"
#include "control.h"
#include "UserParms.h"
#include <libq.h> /* q15 abs function use */
      
extern   tParkParm              ParkParm;
extern   tSincosParm    		SincosParm;
extern   tCtrlParm              CtrlParm;


void Estim(void)
{
    long temp_int;

    //*******************************
    // dIalpha = Ialpha-oldIalpha,  dIbeta  = Ibeta-oldIbeta
    // for lower speed the granularity of differnce is higher - the 
    // difference is made between 2 sampled values @ 8 ADC ISR cycles
    if (_Q15abs(EstimParm.qVelEstim)<NOMINAL_SPEED_RPM*NOPOLESPAIRS)
    {
    
    	EstimParm.qDIalpha	=	(ParkParm.qIalpha-EstimParm.qLastIalphaHS[(EstimParm.qDiCounter-7)&0x0007]);
    	/* the current difference can exceed the maximum value per 8 ADC ISR cycle */
    	/* the following limitation assures a limitation per low speed - up to the nominal speed */
    	if (EstimParm.qDIalpha>EstimParm.qDIlimitLS) EstimParm.qDIalpha=EstimParm.qDIlimitLS;
    	if (EstimParm.qDIalpha<-EstimParm.qDIlimitLS) EstimParm.qDIalpha=-EstimParm.qDIlimitLS;
    	EstimParm.qVIndalpha = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIalpha)>>10);
     
    	EstimParm.qDIbeta	=	(ParkParm.qIbeta-EstimParm.qLastIbetaHS[(EstimParm.qDiCounter-7)&0x0007]);
    	/* the current difference can exceed the maximum value per 8 ADC ISR cycle */
    	/* the following limitation assures a limitation per low speed - up to the nominal speed */
    	if (EstimParm.qDIbeta>EstimParm.qDIlimitLS) EstimParm.qDIbeta=EstimParm.qDIlimitLS;
    	if (EstimParm.qDIbeta<-EstimParm.qDIlimitLS) EstimParm.qDIbeta=-EstimParm.qDIlimitLS;
    	EstimParm.qVIndbeta = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIbeta)>>10);
    
    }
     else
    {
    
    	EstimParm.qDIalpha	=	(ParkParm.qIalpha-EstimParm.qLastIalphaHS[(EstimParm.qDiCounter)]);
    	/* the current difference can exceed the maximum value per 1 ADC ISR cycle */
    	/* the following limitation assures a limitation per high speed - up to the maximum speed */
    	if (EstimParm.qDIalpha>EstimParm.qDIlimitHS) EstimParm.qDIalpha=EstimParm.qDIlimitHS;
    	if (EstimParm.qDIalpha<-EstimParm.qDIlimitHS) EstimParm.qDIalpha=-EstimParm.qDIlimitHS;
    	EstimParm.qVIndalpha = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIalpha)>>7);
    
    	EstimParm.qDIbeta	=	(ParkParm.qIbeta-EstimParm.qLastIbetaHS[(EstimParm.qDiCounter)]);
    	/* the current difference can exceed the maximum value per 1 ADC ISR cycle */
    	/* the following limitation assures a limitation per high speed - up to the maximum speed */
    	if (EstimParm.qDIbeta>EstimParm.qDIlimitHS) EstimParm.qDIbeta=EstimParm.qDIlimitHS;
    	if (EstimParm.qDIbeta<-EstimParm.qDIlimitHS) EstimParm.qDIbeta=-EstimParm.qDIlimitHS;
    	EstimParm.qVIndbeta= (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIbeta)>>7);
    
    }


    //*******************************
    // update  LastIalpha and LastIbeta
    EstimParm.qDiCounter=(EstimParm.qDiCounter+1) & 0x0007;
    EstimParm.qLastIalphaHS[EstimParm.qDiCounter]	=	ParkParm.qIalpha;
    EstimParm.qLastIbetaHS[EstimParm.qDiCounter] 	=	ParkParm.qIbeta;
    
    //*******************************
    // Stator voltage eqations
    // Ualpha = Rs * Ialpha + Ls dIalpha/dt + BEMF
    // BEMF = Ualpha - Rs Ialpha - Ls dIalpha/dt   
    
	EstimParm.qEsa		= 	EstimParm.qLastValpha -
							(int)(__builtin_mulss( MotorEstimParm.qRs, ParkParm.qIalpha)	>>11)
							- EstimParm.qVIndalpha;
    /* the multiplication between the Rs and Ialpha was shifted by 11 instead of 15 */
    /* because the Rs value normalized exceeded Q15 range, so it was divided by 16 */
    /* immediatelky after the normalization - in userparms.h */

    // Ubeta = Rs * Ibeta + Ls dIbeta/dt + BEMF
    // BEMF = Ubeta - Rs Ibeta - Ls dIbeta/dt   
	EstimParm.qEsb		= 	EstimParm.qLastVbeta -
							(int)(__builtin_mulss( MotorEstimParm.qRs, ParkParm.qIbeta )	>>11)
							- EstimParm.qVIndbeta;
							
    /* the multiplication between the Rs and Ibeta was shifted by 11 instead of 15 */
    /* because the Rs value normalized exceeded Q15 range, so it was divided by 16 */
    /* immediatelky after the normalization - in userparms.h */
    
    //*******************************
    // update  LastValpha and LastVbeta
	EstimParm.qLastValpha = ParkParm.qValpha;
	EstimParm.qLastVbeta = ParkParm.qVbeta;
	

    // Calculate Sin(Rho) and Cos(Rho)
    SincosParm.qAngle  = EstimParm.qRho;
    SinCos();

    //*******************************
    //    Esd =  Esa*cos(Angle) + Esb*sin(Rho)
	EstimParm.qEsd		=	(int)((__builtin_mulss(EstimParm.qEsa, SincosParm.qCos)>>15)
							+
							(__builtin_mulss(EstimParm.qEsb, SincosParm.qSin)>>15));
    //*******************************
    //   Esq = -Esa*sin(Angle) + Esb*cos(Rho)
	EstimParm.qEsq		=	(int)((__builtin_mulss(EstimParm.qEsb, SincosParm.qCos)>>15)
							-
							(__builtin_mulss(EstimParm.qEsa, SincosParm.qSin)>>15));


    //*******************************
    //*******************************
    // Filter first order for Esd and Esq
    // EsdFilter = 1/TFilterd * Intergal{ (Esd-EsdFilter).dt }
 
	temp_int = (int)(EstimParm.qEsd - EstimParm.qEsdf);
	EstimParm.qEsdStateVar			+= __builtin_mulss(temp_int, EstimParm.qKfilterdq);
	EstimParm.qEsdf					= (int)(EstimParm.qEsdStateVar>>15);

	temp_int = (int)(EstimParm.qEsq - EstimParm.qEsqf);
	EstimParm.qEsqStateVar			+= __builtin_mulss(temp_int,EstimParm.qKfilterdq);
	EstimParm.qEsqf					= (int)(EstimParm.qEsqStateVar>>15);

    // OmegaMr= (1+SigmaR)/PsiMr * Esq -sgn(Uhqf) * Uhdf
     if (_Q15abs(EstimParm.qVelEstim)>(NOMINAL_SPEED_RPM*NOPOLESPAIRS/10))
    {
    	if(EstimParm.qEsqf>0)
    	{
    		temp_int = (int)(EstimParm.qEsqf- EstimParm.qEsdf);
    		EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi, temp_int)>>15);
    	} else
    	{
    		temp_int = (int)(EstimParm.qEsqf+ EstimParm.qEsdf);
    		EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi, temp_int)>>15);
    	}
    } else // if est speed<10% => condition VelRef<>0
    {
    	if(EstimParm.qVelEstim>0)
    	{
    		temp_int = (int)(EstimParm.qEsqf - EstimParm.qEsdf);
        	EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi,temp_int)>>15);
    	} else
    	{
    		temp_int = (int)(EstimParm.qEsqf + EstimParm.qEsdf);
        	EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi,temp_int)>>15);
    
    	}
    }
    
    //	EstimParm.qOmegaMr=EstimParm.qOmegaMr<<1;

    /* the integral of the angle is the estimated angle */
	EstimParm.qRhoStateVar	+= __builtin_mulss(EstimParm.qOmegaMr, EstimParm.qDeltaT);
	EstimParm.qRho 		= 	(int) (EstimParm.qRhoStateVar>>15);

#ifdef USEIMRREF	
        // Omeg2Estim=Iq/Imr/Tr when Reference Value of magnatising current is used
		EstimParm.qOmeg2Estim= (int)(__builtin_mulss(ParkParm.qIq, MotorEstimParm.qRrInvTr)>>15);
#else

//*******************************
// Current Model
// Imr = 1/Tr * Intergal{ (Id-Imr).dt } when real value of magnetising current is used

        temp_int = (int)(ParkParm.qId - EstimParm.qImr);
		EstimParm.qImrStateVar += __builtin_mulss(temp_int,MotorEstimParm.qInvTr) ;
		EstimParm.qImr      	= (int)(EstimParm.qImrStateVar>>15);

		EstimParm.qIqInvTr2=__builtin_mulss(ParkParm.qIq, MotorEstimParm.qInvTr2);

		/* limit the magnetizing current to guarantee stability */
		if (EstimParm.qImr<2000)
        {
			EstimParm.qImr=2000;
		}

		EstimParm.qOmeg2Estim = EstimParm.qIqInvTr2/EstimParm.qImr;

#endif

    /* the estiamted speed is a filter value of the above calculated OmegaMr. The filter implementation */
    /* is the same as for BEMF d-q components filtering */
    temp_int = (int)(EstimParm.qOmegaMr-EstimParm.qOmeg2Estim-EstimParm.qVelEstim);
	EstimParm.qVelEstimStateVar+=__builtin_mulss(temp_int, EstimParm.qVelEstimFilterK);
	EstimParm.qVelEstim=	(int)(EstimParm.qVelEstimStateVar>>15);
    // Mechanical speed

	EstimParm.qVelEstimMech= (int)(__builtin_mulss(EstimParm.qVelEstim, EstimParm.qInvPol)>>15);
}   // End of Estim()


void    InitEstimParm(void)
{
            // Constants are defined in "EstimParameter_Oriental.xls" 
                
                EstimParm.qRhoStateVar=0;
                EstimParm.qOmegaMr=0;
                EstimParm.qDiCounter=0;
                EstimParm.qEsdStateVar=0;
                EstimParm.qEsqStateVar=0;
                
                EstimParm.qDIlimitLS = D_ILIMIT_LS;
                EstimParm.qDIlimitHS = D_ILIMIT_HS;
                EstimParm.qDeltaT=NORM_DELTAT;
                EstimParm.qKfilterdq=KFILTER_ESDQ;
                EstimParm.qInvPol=0x7FFF / NOPOLESPAIRS;
                EstimParm.qVelEstimFilterK=KFILTER_VELESTIM;

                MotorEstimParm.qInvTr=NORM_INVTR;
                MotorEstimParm.qRrInvTr=NORM_RRINVTR;
                MotorEstimParm.qInvTr2=NORM_INVTR2;


                MotorEstimParm.qLsDt=NORM_LSDT;
                MotorEstimParm.qInvPsi=NORM_INVPSI;
                MotorEstimParm.qRs=NORM_RS;

}

