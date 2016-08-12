/*
 * Traslational_controller.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Traslational_controller".
 *
 * Model version              : 1.127
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Mon Aug 08 17:49:40 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Traslational_controller.h"
#include "Traslational_controller_private.h"

/*
 * This function updates continuous states using the ODE2 fixed-step
 * solver algorithm
 */
void Traslational_controllerModelClass::rt_ertODEUpdateContinuousStates
  (RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE2_IntgData *id = (ODE2_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Traslational_controller_derivatives();

  /* f1 = f(t + h, y + h*f0) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f0[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f1);
  this->step();
  Traslational_controller_derivatives();

  /* tnew = t + h
     ynew = y + (h/2)*(f0 + f1) */
  temp = 0.5*h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + f1[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Traslational_controllerModelClass::step()
{
  real_T rtb_Filter;
  if (rtmIsMajorTimeStep((&Traslational_controller_M))) {
    /* set solver stop time */
    if (!((&Traslational_controller_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Traslational_controller_M)->solverInfo,
                            (((&Traslational_controller_M)->Timing.clockTickH0 +
        1) * (&Traslational_controller_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Traslational_controller_M)->solverInfo,
                            (((&Traslational_controller_M)->Timing.clockTick0 +
        1) * (&Traslational_controller_M)->Timing.stepSize0 +
        (&Traslational_controller_M)->Timing.clockTickH0 *
        (&Traslational_controller_M)->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Traslational_controller_M))) {
    (&Traslational_controller_M)->Timing.t[0] = rtsiGetT
      (&(&Traslational_controller_M)->solverInfo);
  }

  /* Gain: '<S1>/Gain2' incorporates:
   *  Inport: '<Root>/v_des'
   */
  rtb_Filter = Traslational_controller_P.Gain2_Gain *
    Traslational_controller_U.v_des;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Filter > Traslational_controller_P.Saturation_UpperSat) {
    rtb_Filter = Traslational_controller_P.Saturation_UpperSat;
  } else {
    if (rtb_Filter < Traslational_controller_P.Saturation_LowerSat) {
      rtb_Filter = Traslational_controller_P.Saturation_LowerSat;
    }
  }

  /* Sum: '<S1>/Sum4' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/Velocities'
   *  Saturate: '<S1>/Saturation'
   */
  rtb_Filter = Traslational_controller_P.Gain_Gain * rtb_Filter -
    Traslational_controller_U.Velocities[0];

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  Gain: '<S2>/Derivative Gain'
   *  Integrator: '<S2>/Filter'
   *  Sum: '<S2>/SumD'
   */
  Traslational_controller_B.FilterCoefficient = (Traslational_controller_P.Kd_u *
    rtb_Filter - Traslational_controller_X.Filter_CSTATE) *
    Traslational_controller_P.N_tras;

  /* Outport: '<Root>/Fx' incorporates:
   *  Gain: '<S2>/Proportional Gain'
   *  Sum: '<S2>/Sum'
   */
  Traslational_controller_Y.Fx = Traslational_controller_P.Kp_u * rtb_Filter +
    Traslational_controller_B.FilterCoefficient;

  /* Gain: '<S1>/Gain3' incorporates:
   *  Inport: '<Root>/u_des'
   */
  rtb_Filter = Traslational_controller_P.Gain3_Gain *
    Traslational_controller_U.u_des;

  /* Saturate: '<S1>/Saturation1' */
  if (rtb_Filter > Traslational_controller_P.Saturation1_UpperSat) {
    rtb_Filter = Traslational_controller_P.Saturation1_UpperSat;
  } else {
    if (rtb_Filter < Traslational_controller_P.Saturation1_LowerSat) {
      rtb_Filter = Traslational_controller_P.Saturation1_LowerSat;
    }
  }

  /* Sum: '<S1>/Sum1' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/Velocities'
   *  Saturate: '<S1>/Saturation1'
   */
  rtb_Filter = Traslational_controller_P.Gain1_Gain * rtb_Filter -
    Traslational_controller_U.Velocities[1];

  /* Gain: '<S3>/Filter Coefficient' incorporates:
   *  Gain: '<S3>/Derivative Gain'
   *  Integrator: '<S3>/Filter'
   *  Sum: '<S3>/SumD'
   */
  Traslational_controller_B.FilterCoefficient_m =
    (Traslational_controller_P.Kd_v * rtb_Filter -
     Traslational_controller_X.Filter_CSTATE_j) *
    Traslational_controller_P.N_tras;

  /* Outport: '<Root>/Fy' incorporates:
   *  Gain: '<S3>/Proportional Gain'
   *  Sum: '<S3>/Sum'
   */
  Traslational_controller_Y.Fy = Traslational_controller_P.Kp_v * rtb_Filter +
    Traslational_controller_B.FilterCoefficient_m;
  if (rtmIsMajorTimeStep((&Traslational_controller_M))) {
    rt_ertODEUpdateContinuousStates(&(&Traslational_controller_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Traslational_controller_M)->Timing.clockTick0)) {
      ++(&Traslational_controller_M)->Timing.clockTickH0;
    }

    (&Traslational_controller_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&Traslational_controller_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&Traslational_controller_M)->Timing.clockTick1++;
      if (!(&Traslational_controller_M)->Timing.clockTick1) {
        (&Traslational_controller_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Traslational_controllerModelClass::Traslational_controller_derivatives()
{
  XDot_Traslational_controller_T *_rtXdot;
  _rtXdot = ((XDot_Traslational_controller_T *) (&Traslational_controller_M)
             ->ModelData.derivs);

  /* Derivatives for Integrator: '<S2>/Filter' */
  _rtXdot->Filter_CSTATE = Traslational_controller_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S3>/Filter' */
  _rtXdot->Filter_CSTATE_j = Traslational_controller_B.FilterCoefficient_m;
}

/* Model initialize function */
void Traslational_controllerModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&Traslational_controller_M), 0,
                sizeof(RT_MODEL_Traslational_control_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Traslational_controller_M)->solverInfo,
                          &(&Traslational_controller_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&Traslational_controller_M)->solverInfo, &rtmGetTPtr
                ((&Traslational_controller_M)));
    rtsiSetStepSizePtr(&(&Traslational_controller_M)->solverInfo,
                       &(&Traslational_controller_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&Traslational_controller_M)->solverInfo,
                 &(&Traslational_controller_M)->ModelData.derivs);
    rtsiSetContStatesPtr(&(&Traslational_controller_M)->solverInfo, (real_T **)
                         &(&Traslational_controller_M)->ModelData.contStates);
    rtsiSetNumContStatesPtr(&(&Traslational_controller_M)->solverInfo,
      &(&Traslational_controller_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Traslational_controller_M)->solverInfo,
      &(&Traslational_controller_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Traslational_controller_M)->solverInfo,
      &(&Traslational_controller_M)->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Traslational_controller_M)->solverInfo,
      &(&Traslational_controller_M)->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Traslational_controller_M)->solverInfo,
                          (&rtmGetErrorStatus((&Traslational_controller_M))));
    rtsiSetRTModelPtr(&(&Traslational_controller_M)->solverInfo,
                      (&Traslational_controller_M));
  }

  rtsiSetSimTimeStep(&(&Traslational_controller_M)->solverInfo, MAJOR_TIME_STEP);
  (&Traslational_controller_M)->ModelData.intgData.y =
    (&Traslational_controller_M)->ModelData.odeY;
  (&Traslational_controller_M)->ModelData.intgData.f[0] =
    (&Traslational_controller_M)->ModelData.odeF[0];
  (&Traslational_controller_M)->ModelData.intgData.f[1] =
    (&Traslational_controller_M)->ModelData.odeF[1];
  (&Traslational_controller_M)->ModelData.contStates =
    ((X_Traslational_controller_T *) &Traslational_controller_X);
  rtsiSetSolverData(&(&Traslational_controller_M)->solverInfo, (void *)
                    &(&Traslational_controller_M)->ModelData.intgData);
  rtsiSetSolverName(&(&Traslational_controller_M)->solverInfo,"ode2");
  rtmSetTPtr((&Traslational_controller_M), &(&Traslational_controller_M)
             ->Timing.tArray[0]);
  (&Traslational_controller_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &Traslational_controller_B), 0,
                sizeof(B_Traslational_controller_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Traslational_controller_X, 0,
                  sizeof(X_Traslational_controller_T));
  }

  /* external inputs */
  (void) memset((void *)&Traslational_controller_U, 0,
                sizeof(ExtU_Traslational_controller_T));

  /* external outputs */
  (void) memset((void *)&Traslational_controller_Y, 0,
                sizeof(ExtY_Traslational_controller_T));

  /* InitializeConditions for Integrator: '<S2>/Filter' */
  Traslational_controller_X.Filter_CSTATE = Traslational_controller_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S3>/Filter' */
  Traslational_controller_X.Filter_CSTATE_j =
    Traslational_controller_P.Filter_IC_f;
}

/* Model terminate function */
void Traslational_controllerModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Traslational_controllerModelClass::Traslational_controllerModelClass()
{
  static const P_Traslational_controller_T Traslational_controller_P_temp = {
    0.1,                               /* Variable: Kd_u
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
    0.1,                               /* Variable: Kd_v
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
    6.0,                               /* Variable: Kp_u
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
    6.0,                               /* Variable: Kp_v
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
    150.0,                             /* Variable: N_tras
                                        * Referenced by:
                                        *   '<S2>/Filter Coefficient'
                                        *   '<S3>/Filter Coefficient'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Gain2'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    0.5,                               /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Gain3'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    0.5,                               /* Expression: 0.5
                                        * Referenced by: '<S1>/Gain1'
                                        */
    0.0                                /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Traslational_controller_P = Traslational_controller_P_temp;
}

/* Destructor */
Traslational_controllerModelClass::~Traslational_controllerModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Traslational_control_T * Traslational_controllerModelClass::getRTM()
{
  return (&Traslational_controller_M);
}
