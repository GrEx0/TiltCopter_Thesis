/*
 * Position_Tilt.cpp
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

#include "Position_Tilt.h"
#include "Position_Tilt_private.h"

/* Model step function */
void Position_TiltModelClass::step()
{
  real_T Sphi;
  real_T Cphi;
  real_T Stheta;
  real_T Ctheta;
  real_T Spsi;
  real_T Cpsi;
  real_T Pos_body[3];
  real_T Cpsi_0[9];
  int32_T i;

  /* MATLAB Function: '<S1>/NED to body' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/IMU_Att'
   *  Inport: '<Root>/PosRef'
   */
  /* MATLAB Function 'Position Controller Tilt/NED to body': '<S2>:1' */
  /* '<S2>:1:3' */
  /* % Rotate Acc_body to Earth frame */
  /* '<S2>:1:8' */
  Sphi = sin(Position_Tilt_U.IMU_Att[0]);

  /* '<S2>:1:9' */
  Cphi = cos(Position_Tilt_U.IMU_Att[0]);

  /* '<S2>:1:10' */
  Stheta = sin(Position_Tilt_U.IMU_Att[1]);

  /* '<S2>:1:11' */
  Ctheta = cos(Position_Tilt_U.IMU_Att[1]);

  /* '<S2>:1:12' */
  Spsi = sin(Position_Tilt_U.IMU_Att[2]);

  /* '<S2>:1:13' */
  Cpsi = cos(Position_Tilt_U.IMU_Att[2]);

  /* '<S2>:1:15' */
  /*  Acc_Earth = zeros(3,1); */
  /* '<S2>:1:25' */
  Cpsi_0[0] = Cpsi * Ctheta;
  Cpsi_0[3] = Ctheta * Spsi;
  Cpsi_0[6] = -Stheta;
  Cpsi_0[1] = Cpsi * Sphi * Stheta - Cphi * Spsi;
  Cpsi_0[4] = Sphi * Spsi * Stheta + Cphi * Cpsi;
  Cpsi_0[7] = Ctheta * Sphi;
  Cpsi_0[2] = Cphi * Cpsi * Stheta + Sphi * Spsi;
  Cpsi_0[5] = Cphi * Spsi * Stheta - Cpsi * Sphi;
  Cpsi_0[8] = Cphi * Ctheta;
  for (i = 0; i < 3; i++) {
    Pos_body[i] = Cpsi_0[i + 6] * Position_Tilt_P.Constant_Value + (Cpsi_0[i + 3]
      * Position_Tilt_U.PosRef[1] + Cpsi_0[i] * Position_Tilt_U.PosRef[0]);
  }

  /* Outport: '<Root>/u_des' incorporates:
   *  MATLAB Function: '<S1>/NED to body'
   */
  /* '<S2>:1:27' */
  /* '<S2>:1:28' */
  /* '<S2>:1:29' */
  Position_Tilt_Y.u_des = Pos_body[0];

  /* Outport: '<Root>/v_des' incorporates:
   *  MATLAB Function: '<S1>/NED to body'
   */
  Position_Tilt_Y.v_des = Pos_body[1];
}

/* Model initialize function */
void Position_TiltModelClass::initialize()
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus((&Position_Tilt_M), (NULL));

  /* external inputs */
  (void) memset((void *)&Position_Tilt_U, 0,
                sizeof(ExtU_Position_Tilt_T));

  /* external outputs */
  (void) memset((void *)&Position_Tilt_Y, 0,
                sizeof(ExtY_Position_Tilt_T));
}

/* Model terminate function */
void Position_TiltModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Position_TiltModelClass::Position_TiltModelClass()
{
  static const P_Position_Tilt_T Position_Tilt_P_temp = {
    0.0                                /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Position_Tilt_P = Position_Tilt_P_temp;
}

/* Destructor */
Position_TiltModelClass::~Position_TiltModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Position_Tilt_T * Position_TiltModelClass::getRTM()
{
  return (&Position_Tilt_M);
}
