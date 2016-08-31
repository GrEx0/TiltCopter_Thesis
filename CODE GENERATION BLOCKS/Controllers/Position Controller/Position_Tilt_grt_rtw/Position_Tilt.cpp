/*
 * Position_Tilt.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Position_Tilt".
 *
 * Model version              : 1.120
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Tue Aug 30 18:08:24 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Position_Tilt.h"
#include "Position_Tilt_private.h"

/*
 * This function updates continuous states using the ODE2 fixed-step
 * solver algorithm
 */
void Position_TiltModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  Position_Tilt_derivatives();

  /* f1 = f(t + h, y + h*f0) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f0[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f1);
  this->step();
  Position_Tilt_derivatives();

  /* tnew = t + h
     ynew = y + (h/2)*(f0 + f1) */
  temp = 0.5*h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + f1[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Position_TiltModelClass::step()
{
  real_T rtb_Filter;
  if (rtmIsMajorTimeStep((&Position_Tilt_M))) {
    /* set solver stop time */
    if (!((&Position_Tilt_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Position_Tilt_M)->solverInfo, (((&Position_Tilt_M)
        ->Timing.clockTickH0 + 1) * (&Position_Tilt_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Position_Tilt_M)->solverInfo, (((&Position_Tilt_M)
        ->Timing.clockTick0 + 1) * (&Position_Tilt_M)->Timing.stepSize0 +
        (&Position_Tilt_M)->Timing.clockTickH0 * (&Position_Tilt_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Position_Tilt_M))) {
    (&Position_Tilt_M)->Timing.t[0] = rtsiGetT(&(&Position_Tilt_M)->solverInfo);
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  Inport: '<Root>/Pos'
   *  Inport: '<Root>/PosRef'
   */
  rtb_Filter = Position_Tilt_U.PosRef[0] - Position_Tilt_U.Pos[0];

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  Gain: '<S2>/Derivative Gain'
   *  Integrator: '<S2>/Filter'
   *  Sum: '<S2>/SumD'
   */
  Position_Tilt_B.FilterCoefficient = (Position_Tilt_P.Kd_N * rtb_Filter -
    Position_Tilt_X.Filter_CSTATE) * Position_Tilt_P.PIDController_N;

  /* Outport: '<Root>/u_des' incorporates:
   *  Gain: '<S2>/Proportional Gain'
   *  Sum: '<S2>/Sum'
   */
  Position_Tilt_Y.u_des = Position_Tilt_P.Kp_N * rtb_Filter +
    Position_Tilt_B.FilterCoefficient;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/Pos'
   *  Inport: '<Root>/PosRef'
   */
  rtb_Filter = Position_Tilt_U.PosRef[1] - Position_Tilt_U.Pos[1];

  /* Gain: '<S3>/Filter Coefficient' incorporates:
   *  Gain: '<S3>/Derivative Gain'
   *  Integrator: '<S3>/Filter'
   *  Sum: '<S3>/SumD'
   */
  Position_Tilt_B.FilterCoefficient_f = (Position_Tilt_P.Kd_E * rtb_Filter -
    Position_Tilt_X.Filter_CSTATE_b) * Position_Tilt_P.PIDController1_N;

  /* Outport: '<Root>/v_des' incorporates:
   *  Gain: '<S3>/Proportional Gain'
   *  Sum: '<S3>/Sum'
   */
  Position_Tilt_Y.v_des = Position_Tilt_P.Kp_E * rtb_Filter +
    Position_Tilt_B.FilterCoefficient_f;
  if (rtmIsMajorTimeStep((&Position_Tilt_M))) {
    rt_ertODEUpdateContinuousStates(&(&Position_Tilt_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Position_Tilt_M)->Timing.clockTick0)) {
      ++(&Position_Tilt_M)->Timing.clockTickH0;
    }

    (&Position_Tilt_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Position_Tilt_M
      )->solverInfo);

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
      (&Position_Tilt_M)->Timing.clockTick1++;
      if (!(&Position_Tilt_M)->Timing.clockTick1) {
        (&Position_Tilt_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Position_TiltModelClass::Position_Tilt_derivatives()
{
  XDot_Position_Tilt_T *_rtXdot;
  _rtXdot = ((XDot_Position_Tilt_T *) (&Position_Tilt_M)->ModelData.derivs);

  /* Derivatives for Integrator: '<S2>/Filter' */
  _rtXdot->Filter_CSTATE = Position_Tilt_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S3>/Filter' */
  _rtXdot->Filter_CSTATE_b = Position_Tilt_B.FilterCoefficient_f;
}

/* Model initialize function */
void Position_TiltModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&Position_Tilt_M), 0,
                sizeof(RT_MODEL_Position_Tilt_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Position_Tilt_M)->solverInfo, &(&Position_Tilt_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Position_Tilt_M)->solverInfo, &rtmGetTPtr((&Position_Tilt_M)));
    rtsiSetStepSizePtr(&(&Position_Tilt_M)->solverInfo, &(&Position_Tilt_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Position_Tilt_M)->solverInfo, &(&Position_Tilt_M)
                 ->ModelData.derivs);
    rtsiSetContStatesPtr(&(&Position_Tilt_M)->solverInfo, (real_T **)
                         &(&Position_Tilt_M)->ModelData.contStates);
    rtsiSetNumContStatesPtr(&(&Position_Tilt_M)->solverInfo, &(&Position_Tilt_M
      )->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Position_Tilt_M)->solverInfo,
      &(&Position_Tilt_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Position_Tilt_M)->solverInfo,
      &(&Position_Tilt_M)->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Position_Tilt_M)->solverInfo,
      &(&Position_Tilt_M)->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Position_Tilt_M)->solverInfo, (&rtmGetErrorStatus((
      &Position_Tilt_M))));
    rtsiSetRTModelPtr(&(&Position_Tilt_M)->solverInfo, (&Position_Tilt_M));
  }

  rtsiSetSimTimeStep(&(&Position_Tilt_M)->solverInfo, MAJOR_TIME_STEP);
  (&Position_Tilt_M)->ModelData.intgData.y = (&Position_Tilt_M)->ModelData.odeY;
  (&Position_Tilt_M)->ModelData.intgData.f[0] = (&Position_Tilt_M)
    ->ModelData.odeF[0];
  (&Position_Tilt_M)->ModelData.intgData.f[1] = (&Position_Tilt_M)
    ->ModelData.odeF[1];
  (&Position_Tilt_M)->ModelData.contStates = ((X_Position_Tilt_T *)
    &Position_Tilt_X);
  rtsiSetSolverData(&(&Position_Tilt_M)->solverInfo, (void *)&(&Position_Tilt_M
                    )->ModelData.intgData);
  rtsiSetSolverName(&(&Position_Tilt_M)->solverInfo,"ode2");
  rtmSetTPtr((&Position_Tilt_M), &(&Position_Tilt_M)->Timing.tArray[0]);
  (&Position_Tilt_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &Position_Tilt_B), 0,
                sizeof(B_Position_Tilt_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Position_Tilt_X, 0,
                  sizeof(X_Position_Tilt_T));
  }

  /* external inputs */
  (void) memset((void *)&Position_Tilt_U, 0,
                sizeof(ExtU_Position_Tilt_T));

  /* external outputs */
  (void) memset((void *)&Position_Tilt_Y, 0,
                sizeof(ExtY_Position_Tilt_T));

  /* InitializeConditions for Integrator: '<S2>/Filter' */
  Position_Tilt_X.Filter_CSTATE = Position_Tilt_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S3>/Filter' */
  Position_Tilt_X.Filter_CSTATE_b = Position_Tilt_P.Filter_IC_d;
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
    0.01,                              /* Variable: Kd_E
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
    0.01,                              /* Variable: Kd_N
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
    0.15,                              /* Variable: Kp_E
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
    0.15,                              /* Variable: Kp_N
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
    100.0,                             /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
    100.0,                             /* Mask Parameter: PIDController1_N
                                        * Referenced by: '<S3>/Filter Coefficient'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
    0.0                                /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
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
