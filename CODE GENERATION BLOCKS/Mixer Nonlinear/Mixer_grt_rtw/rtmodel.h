/*
 *  rtmodel.h:
 *
 * Code generation for model "Mixer".
 *
 * Model version              : 1.19
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C++ source code generated on : Tue Jun 14 14:30:30 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rtmodel_h_
#define RTW_HEADER_rtmodel_h_

/*
 *  Includes the appropriate headers when we are using rtModel
 */
#include "Mixer.h"
#define GRTINTERFACE                   0

/*
 * ROOT_IO_FORMAT: 0 (Individual arguments)
 * ROOT_IO_FORMAT: 1 (Structure reference)
 * ROOT_IO_FORMAT: 2 (Part of model data structure)
 */
# define ROOT_IO_FORMAT                2

/* Macros generated for backwards compatibility  */
#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#define MODEL_CLASSNAME                MixerModelClass
#define MODEL_STEPNAME                 step
#endif                                 /* RTW_HEADER_rtmodel_h_ */
