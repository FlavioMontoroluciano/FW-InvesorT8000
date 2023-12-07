#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../ACIM.c ../CalcRef.s ../clrkpark.s ../Estim.c ../fdweak.s ../InvClark.s ../InvPark.s ../MeasCurr.s ../openloop.s ../pi.s ../ReadADC0.s ../RTDM.c ../SVGEN.S ../trig.s ../periph.c ../uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/ACIM.o ${OBJECTDIR}/_ext/1472/CalcRef.o ${OBJECTDIR}/_ext/1472/clrkpark.o ${OBJECTDIR}/_ext/1472/Estim.o ${OBJECTDIR}/_ext/1472/fdweak.o ${OBJECTDIR}/_ext/1472/InvClark.o ${OBJECTDIR}/_ext/1472/InvPark.o ${OBJECTDIR}/_ext/1472/MeasCurr.o ${OBJECTDIR}/_ext/1472/openloop.o ${OBJECTDIR}/_ext/1472/pi.o ${OBJECTDIR}/_ext/1472/ReadADC0.o ${OBJECTDIR}/_ext/1472/RTDM.o ${OBJECTDIR}/_ext/1472/SVGEN.o ${OBJECTDIR}/_ext/1472/trig.o ${OBJECTDIR}/_ext/1472/periph.o ${OBJECTDIR}/_ext/1472/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/ACIM.o.d ${OBJECTDIR}/_ext/1472/CalcRef.o.d ${OBJECTDIR}/_ext/1472/clrkpark.o.d ${OBJECTDIR}/_ext/1472/Estim.o.d ${OBJECTDIR}/_ext/1472/fdweak.o.d ${OBJECTDIR}/_ext/1472/InvClark.o.d ${OBJECTDIR}/_ext/1472/InvPark.o.d ${OBJECTDIR}/_ext/1472/MeasCurr.o.d ${OBJECTDIR}/_ext/1472/openloop.o.d ${OBJECTDIR}/_ext/1472/pi.o.d ${OBJECTDIR}/_ext/1472/ReadADC0.o.d ${OBJECTDIR}/_ext/1472/RTDM.o.d ${OBJECTDIR}/_ext/1472/SVGEN.o.d ${OBJECTDIR}/_ext/1472/trig.o.d ${OBJECTDIR}/_ext/1472/periph.o.d ${OBJECTDIR}/_ext/1472/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/ACIM.o ${OBJECTDIR}/_ext/1472/CalcRef.o ${OBJECTDIR}/_ext/1472/clrkpark.o ${OBJECTDIR}/_ext/1472/Estim.o ${OBJECTDIR}/_ext/1472/fdweak.o ${OBJECTDIR}/_ext/1472/InvClark.o ${OBJECTDIR}/_ext/1472/InvPark.o ${OBJECTDIR}/_ext/1472/MeasCurr.o ${OBJECTDIR}/_ext/1472/openloop.o ${OBJECTDIR}/_ext/1472/pi.o ${OBJECTDIR}/_ext/1472/ReadADC0.o ${OBJECTDIR}/_ext/1472/RTDM.o ${OBJECTDIR}/_ext/1472/SVGEN.o ${OBJECTDIR}/_ext/1472/trig.o ${OBJECTDIR}/_ext/1472/periph.o ${OBJECTDIR}/_ext/1472/uart.o

# Source Files
SOURCEFILES=../ACIM.c ../CalcRef.s ../clrkpark.s ../Estim.c ../fdweak.s ../InvClark.s ../InvPark.s ../MeasCurr.s ../openloop.s ../pi.s ../ReadADC0.s ../RTDM.c ../SVGEN.S ../trig.s ../periph.c ../uart.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MC506
MP_LINKER_FILE_OPTION=,--script=p33EP256MC506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/ACIM.o: ../ACIM.c  .generated_files/flags/default/e092d66d0518879fc5457c5bf05572a25617a94e .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ACIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ACIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ACIM.c  -o ${OBJECTDIR}/_ext/1472/ACIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ACIM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Estim.o: ../Estim.c  .generated_files/flags/default/5a63b4bc40203623196b62009a92ffd1c50daedb .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Estim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Estim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Estim.c  -o ${OBJECTDIR}/_ext/1472/Estim.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Estim.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RTDM.o: ../RTDM.c  .generated_files/flags/default/39ea41127b28a54727b877456a05cc78af4fea96 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RTDM.c  -o ${OBJECTDIR}/_ext/1472/RTDM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RTDM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/periph.o: ../periph.c  .generated_files/flags/default/663dd99ecf49d12032e8f78a0bb3b317eb79c5c0 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/periph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/periph.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../periph.c  -o ${OBJECTDIR}/_ext/1472/periph.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/periph.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  .generated_files/flags/default/d0d1c988002a310874b7a55b0c61827013135f2c .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../uart.c  -o ${OBJECTDIR}/_ext/1472/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/ACIM.o: ../ACIM.c  .generated_files/flags/default/ed3a9ded8516e61330d6d4d23c72342073c3cf35 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ACIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ACIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../ACIM.c  -o ${OBJECTDIR}/_ext/1472/ACIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/ACIM.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/Estim.o: ../Estim.c  .generated_files/flags/default/835339a835729d4bdb9b4ea738d71c7cceb10d43 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Estim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Estim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Estim.c  -o ${OBJECTDIR}/_ext/1472/Estim.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/Estim.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/RTDM.o: ../RTDM.c  .generated_files/flags/default/fc70b540da2956707e21f845a9ac48e8759975c3 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTDM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../RTDM.c  -o ${OBJECTDIR}/_ext/1472/RTDM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/RTDM.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/periph.o: ../periph.c  .generated_files/flags/default/820457cdb5fedd102b2aef2f9f2e7cba439a815d .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/periph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/periph.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../periph.c  -o ${OBJECTDIR}/_ext/1472/periph.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/periph.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  .generated_files/flags/default/9446b64a479c18eb990ba60422e32200556fc5a6 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../uart.c  -o ${OBJECTDIR}/_ext/1472/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -I".." -msmart-io=1 -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/CalcRef.o: ../CalcRef.s  .generated_files/flags/default/40a5de2c3545a9bd20abb996c6fa191f94147cdd .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../CalcRef.s  -o ${OBJECTDIR}/_ext/1472/CalcRef.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/CalcRef.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/clrkpark.o: ../clrkpark.s  .generated_files/flags/default/1e265e0b9a22a7ca32d3b7c24eaec64091e62314 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../clrkpark.s  -o ${OBJECTDIR}/_ext/1472/clrkpark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/clrkpark.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/fdweak.o: ../fdweak.s  .generated_files/flags/default/ba6f2991b52959ac0209a1362ced8a986f7c539 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fdweak.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fdweak.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../fdweak.s  -o ${OBJECTDIR}/_ext/1472/fdweak.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/fdweak.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InvClark.o: ../InvClark.s  .generated_files/flags/default/632c846a74323c2faa1882e55dd223bdd3dcd43 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvClark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvClark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvClark.s  -o ${OBJECTDIR}/_ext/1472/InvClark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvClark.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InvPark.o: ../InvPark.s  .generated_files/flags/default/c9004e846ae1819dcc7ee204225d982a4a08daae .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvPark.s  -o ${OBJECTDIR}/_ext/1472/InvPark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvPark.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MeasCurr.o: ../MeasCurr.s  .generated_files/flags/default/5f37de149c7958b915947d13c3a99008ca18f78b .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../MeasCurr.s  -o ${OBJECTDIR}/_ext/1472/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/openloop.o: ../openloop.s  .generated_files/flags/default/f2eca9639432af96c29ae392bfe8489270142f13 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/openloop.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/openloop.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../openloop.s  -o ${OBJECTDIR}/_ext/1472/openloop.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/openloop.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/pi.o: ../pi.s  .generated_files/flags/default/d1f93431f9ccf207bacb9f9cb9640b404e969577 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../pi.s  -o ${OBJECTDIR}/_ext/1472/pi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/pi.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ReadADC0.o: ../ReadADC0.s  .generated_files/flags/default/9eaae8a8258db427ef3d18587f38cf5f422485ad .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../ReadADC0.s  -o ${OBJECTDIR}/_ext/1472/ReadADC0.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/ReadADC0.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/trig.o: ../trig.s  .generated_files/flags/default/98e615eccbbf7d020f34d38591a00905e2cd0d59 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../trig.s  -o ${OBJECTDIR}/_ext/1472/trig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/trig.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/CalcRef.o: ../CalcRef.s  .generated_files/flags/default/5f54117cd834a8a33e3fc07c825b500686ebcf49 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CalcRef.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../CalcRef.s  -o ${OBJECTDIR}/_ext/1472/CalcRef.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/CalcRef.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/clrkpark.o: ../clrkpark.s  .generated_files/flags/default/1b8010a068c1b510d19e2ddce77bdb2f19e282b .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clrkpark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../clrkpark.s  -o ${OBJECTDIR}/_ext/1472/clrkpark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/clrkpark.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/fdweak.o: ../fdweak.s  .generated_files/flags/default/bad556ca104dac4743c95905771ff1e15fdbb7d4 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fdweak.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fdweak.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../fdweak.s  -o ${OBJECTDIR}/_ext/1472/fdweak.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/fdweak.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InvClark.o: ../InvClark.s  .generated_files/flags/default/86290b60f51d7e1526dee26a5e4d238e6ef9d901 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvClark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvClark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvClark.s  -o ${OBJECTDIR}/_ext/1472/InvClark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvClark.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/InvPark.o: ../InvPark.s  .generated_files/flags/default/61421a74f4cb45bbdd0ad183bbdc18c86af00fd7 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/InvPark.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../InvPark.s  -o ${OBJECTDIR}/_ext/1472/InvPark.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/InvPark.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MeasCurr.o: ../MeasCurr.s  .generated_files/flags/default/e8d0d8def7450f6117dbfdc4cef27e9059fb54f4 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MeasCurr.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../MeasCurr.s  -o ${OBJECTDIR}/_ext/1472/MeasCurr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/MeasCurr.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/openloop.o: ../openloop.s  .generated_files/flags/default/51d365fd1c6c3dc7bda0abce808174ed7d1d24fa .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/openloop.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/openloop.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../openloop.s  -o ${OBJECTDIR}/_ext/1472/openloop.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/openloop.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/pi.o: ../pi.s  .generated_files/flags/default/8f5536d27d89d912dd3447596f8b8183e1fb7904 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pi.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../pi.s  -o ${OBJECTDIR}/_ext/1472/pi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/pi.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/ReadADC0.o: ../ReadADC0.s  .generated_files/flags/default/e7557ed0782d03a99ab0b5fc4a49eec153a65d59 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ReadADC0.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../ReadADC0.s  -o ${OBJECTDIR}/_ext/1472/ReadADC0.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/ReadADC0.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/trig.o: ../trig.s  .generated_files/flags/default/d9cc383dcdcb2771cc0951ca651078c1c2795240 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/trig.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../trig.s  -o ${OBJECTDIR}/_ext/1472/trig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/trig.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/SVGEN.o: ../SVGEN.S  .generated_files/flags/default/f906333913ae121ecc7fd96136165e62e0bce642 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SVGEN.S  -o ${OBJECTDIR}/_ext/1472/SVGEN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SVGEN.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/SVGEN.o: ../SVGEN.S  .generated_files/flags/default/954c32a8e3640d43cfba403c91000aa4e00a7043 .generated_files/flags/default/cf746db493ae6e9c8dd43321e46753b1122a0084
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SVGEN.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../SVGEN.S  -o ${OBJECTDIR}/_ext/1472/SVGEN.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SVGEN.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -Wa,-MD,"${OBJECTDIR}/_ext/1472/SVGEN.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=q,--library-path="..",--no-force-link,--smart-io,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library=q,--library-path="..",--no-force-link,--smart-io,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ACIM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
