/*
 * traslational_controller.cpp
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

#include "traslational_controller.h"
#include "traslational_controller_private.h"

/* Model step function */
void traslational_controllerModelClass::step()
{
  /* Outport: '<Root>/Fx' incorporates:
   *  Gain: '<S2>/Proportional Gain'
   *  Inport: '<Root>/Velocities'
   *  Inport: '<Root>/u_des'
   *  Sum: '<S1>/Sum4'
   */
  traslational_controller_Y.Fx = (traslational_controller_U.u_des -
    traslational_controller_U.Velocities[0]) * traslational_controller_P.Kp_u;

  /* Outport: '<Root>/Fy' incorporates:
   *  Gain: '<S3>/Proportional Gain'
   *  Inport: '<Root>/Velocities'
   *  Inport: '<Root>/v_des'
   *  Sum: '<S1>/Sum1'
   */
  traslational_controller_Y.Fy = (traslational_controller_U.v_des -
    traslational_controller_U.Velocities[1]) * traslational_controller_P.Kp_v;
}

/* Model initialize function */
void traslational_controllerModelClass::initialize()
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus((&traslational_controller_M), (NULL));

  /* external inputs */
  (void) memset((void *)&traslational_controller_U, 0,
                sizeof(ExtU_traslational_controller_T));

  /* external outputs */
  (void) memset((void *)&traslational_controller_Y, 0,
                sizeof(ExtY_traslational_controller_T));
}

/* Model terminate function */
void traslational_controllerModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
traslational_controllerModelClass::traslational_controllerModelClass()
{
  static const P_traslational_controller_T traslational_controller_P_temp = {
    19.0,                              /* Variable: Kp_u
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
    19.0                               /* Variable: Kp_v
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  traslational_controller_P = traslational_controller_P_temp;
}

/* Destructor */
traslational_controllerModelClass::~traslational_controllerModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_traslational_control_T * traslational_controllerModelClass::getRTM()
{
  return (&traslational_controller_M);
}
