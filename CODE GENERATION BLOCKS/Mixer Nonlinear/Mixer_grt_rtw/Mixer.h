/*
 * Mixer.h
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

#ifndef RTW_HEADER_Mixer_h_
#define RTW_HEADER_Mixer_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Mixer_COMMON_INCLUDES_
# define Mixer_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Mixer_COMMON_INCLUDES_ */

#include "Mixer_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Fx;                           /* '<Root>/Fx' */
  real_T Fy;                           /* '<Root>/Fy' */
  real_T T;                            /* '<Root>/T' */
  real_T L;                            /* '<Root>/L' */
  real_T M;                            /* '<Root>/M' */
  real_T N;                            /* '<Root>/N' */
} ExtU_Mixer_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T th1;                          /* '<Root>/th1' */
  real_T th2;                          /* '<Root>/th2' */
  real_T th3;                          /* '<Root>/th3' */
  real_T th4;                          /* '<Root>/th4 ' */
  real_T alpha1;                       /* '<Root>/alpha1' */
  real_T alpha2;                       /* '<Root>/alpha2' */
  real_T alpha3;                       /* '<Root>/alpha3' */
  real_T alpha4;                       /* '<Root>/alpha4' */
} ExtY_Mixer_T;

/* Real-time Model Data Structure */
struct tag_RTM_Mixer_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model Mixer */
class MixerModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_Mixer_T Mixer_U;

  /* External outputs */
  ExtY_Mixer_T Mixer_Y;

  /* Model entry point functions */

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  MixerModelClass();

  /* Destructor */
  ~MixerModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Mixer_T * getRTM();

  /* private data and function members */
 private:
  /* Real-Time Model */
  RT_MODEL_Mixer_T Mixer_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Mixer'
 * '<S1>'   : 'Mixer/Inverted NONLINEAR mixer matrix'
 */
#endif                                 /* RTW_HEADER_Mixer_h_ */
