/*
 * Forces_estimation.h
 *
 * Code generation for model "Forces_estimation".
 *
 * Model version              : 1.20
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C++ source code generated on : Fri Jul 15 19:26:19 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Forces_estimation_h_
#define RTW_HEADER_Forces_estimation_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Forces_estimation_COMMON_INCLUDES_
# define Forces_estimation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Forces_estimation_COMMON_INCLUDES_ */

#include "Forces_estimation_types.h"

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
  real_T u[8];                         /* '<Root>/u' */
} ExtU_Forces_estimation_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Fx_est;                       /* '<Root>/Fx_est' */
  real_T Fy_est;                       /* '<Root>/Fy_est' */
} ExtY_Forces_estimation_T;

/* Parameters (auto storage) */
struct P_Forces_estimation_T_ {
  real_T Kt;                           /* Variable: Kt
                                        * Referenced by:
                                        *   '<S2>/Gain'
                                        *   '<S2>/Gain3'
                                        *   '<S3>/Gain'
                                        *   '<S3>/Gain3'
                                        */
  real_T degtorad;                     /* Variable: degtorad
                                        * Referenced by:
                                        *   '<S2>/Gain4'
                                        *   '<S2>/Gain5'
                                        *   '<S3>/Gain4'
                                        *   '<S3>/Gain5'
                                        */
  real_T x1[2];                        /* Variable: x1
                                        * Referenced by:
                                        *   '<S2>/Bias'
                                        *   '<S2>/Bias1'
                                        *   '<S2>/Gain1'
                                        *   '<S2>/Gain2'
                                        *   '<S3>/Bias'
                                        *   '<S3>/Bias1'
                                        *   '<S3>/Gain1'
                                        *   '<S3>/Gain2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Forces_estimation_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model Forces_estimation */
class Forces_estimationModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_Forces_estimation_T Forces_estimation_U;

  /* External outputs */
  ExtY_Forces_estimation_T Forces_estimation_Y;

  /* Model entry point functions */

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  Forces_estimationModelClass();

  /* Destructor */
  ~Forces_estimationModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Forces_estimation_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_Forces_estimation_T Forces_estimation_P;

  /* Real-Time Model */
  RT_MODEL_Forces_estimation_T Forces_estimation_M;
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
 * '<Root>' : 'Forces_estimation'
 * '<S1>'   : 'Forces_estimation/Force estimation'
 * '<S2>'   : 'Forces_estimation/Force estimation/Subsystem'
 * '<S3>'   : 'Forces_estimation/Force estimation/Subsystem1'
 */
#endif                                 /* RTW_HEADER_Forces_estimation_h_ */
