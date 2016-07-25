/*
 * traslational_controller.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "traslational_controller".
 *
 * Model version              : 1.115
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Mon Jul 25 09:41:14 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_traslational_controller_h_
#define RTW_HEADER_traslational_controller_h_
#include <stddef.h>
#include <string.h>
#ifndef traslational_controller_COMMON_INCLUDES_
# define traslational_controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* traslational_controller_COMMON_INCLUDES_ */

#include "traslational_controller_types.h"

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
  real_T Velocities[2];                /* '<Root>/Velocities' */
  real_T u_des;                        /* '<Root>/u_des' */
  real_T v_des;                        /* '<Root>/v_des' */
} ExtU_traslational_controller_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Fx;                           /* '<Root>/Fx' */
  real_T Fy;                           /* '<Root>/Fy' */
} ExtY_traslational_controller_T;

/* Parameters (auto storage) */
struct P_traslational_controller_T_ {
  real_T Kp_u;                         /* Variable: Kp_u
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  real_T Kp_v;                         /* Variable: Kp_v
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_traslational_controll_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model traslational_controller */
class traslational_controllerModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_traslational_controller_T traslational_controller_U;

  /* External outputs */
  ExtY_traslational_controller_T traslational_controller_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  traslational_controllerModelClass();

  /* Destructor */
  ~traslational_controllerModelClass();

  /* Real-Time Model get method */
  RT_MODEL_traslational_control_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_traslational_controller_T traslational_controller_P;

  /* Real-Time Model */
  RT_MODEL_traslational_control_T traslational_controller_M;
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
 * '<Root>' : 'traslational_controller'
 * '<S1>'   : 'traslational_controller/Traslational controller'
 * '<S2>'   : 'traslational_controller/Traslational controller/u controller'
 * '<S3>'   : 'traslational_controller/Traslational controller/v controller'
 */
#endif                                 /* RTW_HEADER_traslational_controller_h_ */
