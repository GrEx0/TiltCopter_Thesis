/*
 * Position_Tilt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Position_Tilt".
 *
 * Model version              : 1.116
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Thu Jul 28 11:58:29 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Position_Tilt_h_
#define RTW_HEADER_Position_Tilt_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef Position_Tilt_COMMON_INCLUDES_
# define Position_Tilt_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Position_Tilt_COMMON_INCLUDES_ */

#include "Position_Tilt_types.h"

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
  real_T PosRef[2];                    /* '<Root>/PosRef' */
  real_T Pos[2];                       /* '<Root>/Pos' */
  real_T IMU_Att[3];                   /* '<Root>/IMU_Att' */
} ExtU_Position_Tilt_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T u_des;                        /* '<Root>/u_des' */
  real_T v_des;                        /* '<Root>/v_des' */
} ExtY_Position_Tilt_T;

/* Parameters (auto storage) */
struct P_Position_Tilt_T_ {
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Position_Tilt_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model Position_Tilt */
class Position_TiltModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_Position_Tilt_T Position_Tilt_U;

  /* External outputs */
  ExtY_Position_Tilt_T Position_Tilt_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  Position_TiltModelClass();

  /* Destructor */
  ~Position_TiltModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Position_Tilt_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_Position_Tilt_T Position_Tilt_P;

  /* Real-Time Model */
  RT_MODEL_Position_Tilt_T Position_Tilt_M;
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
 * '<Root>' : 'Position_Tilt'
 * '<S1>'   : 'Position_Tilt/Position Controller Tilt'
 * '<S2>'   : 'Position_Tilt/Position Controller Tilt/NED to body'
 */
#endif                                 /* RTW_HEADER_Position_Tilt_h_ */
