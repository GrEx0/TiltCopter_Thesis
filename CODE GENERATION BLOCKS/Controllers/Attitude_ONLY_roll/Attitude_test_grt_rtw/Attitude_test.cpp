/*
 * Attitude_test.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Attitude_test".
 *
 * Model version              : 1.98
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Sat Sep 03 15:04:34 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Attitude_test.h"
#include "Attitude_test_private.h"

/*
 * This function updates continuous states using the ODE2 fixed-step
 * solver algorithm
 */
void Attitude_testModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Attitude_test_derivatives();

  /* f1 = f(t + h, y + h*f0) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f0[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f1);
  this->step();
  Attitude_test_derivatives();

  /* tnew = t + h
     ynew = y + (h/2)*(f0 + f1) */
  temp = 0.5*h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + f1[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Attitude_testModelClass::step()
{
  real_T rtb_Sum4;
  real_T rtb_Saturate;
  real_T rtb_Sum_o;
  if (rtmIsMajorTimeStep((&Attitude_test_M))) {
    /* set solver stop time */
    if (!((&Attitude_test_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Attitude_test_M)->solverInfo, (((&Attitude_test_M)
        ->Timing.clockTickH0 + 1) * (&Attitude_test_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Attitude_test_M)->solverInfo, (((&Attitude_test_M)
        ->Timing.clockTick0 + 1) * (&Attitude_test_M)->Timing.stepSize0 +
        (&Attitude_test_M)->Timing.clockTickH0 * (&Attitude_test_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Attitude_test_M))) {
    (&Attitude_test_M)->Timing.t[0] = rtsiGetT(&(&Attitude_test_M)->solverInfo);
  }

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Inport: '<Root>/Stick'
   */
  if (Attitude_test_U.Stick[0] > Attitude_test_P.Saturation_UpperSat) {
    rtb_Sum4 = Attitude_test_P.Saturation_UpperSat;
  } else if (Attitude_test_U.Stick[0] < Attitude_test_P.Saturation_LowerSat) {
    rtb_Sum4 = Attitude_test_P.Saturation_LowerSat;
  } else {
    rtb_Sum4 = Attitude_test_U.Stick[0];
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Yaw-rate1'
   *  Inport: '<Root>/IMU_Attitude'
   *  Saturate: '<S1>/Saturation'
   */
  rtb_Sum4 = Attitude_test_P.rollMax * rtb_Sum4 - Attitude_test_U.IMU_Attitude[0];

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  Gain: '<S2>/Derivative Gain'
   *  Integrator: '<S2>/Filter'
   *  Sum: '<S2>/SumD'
   */
  Attitude_test_B.FilterCoefficient = (Attitude_test_P.KRD * rtb_Sum4 -
    Attitude_test_X.Filter_CSTATE) * Attitude_test_P.N;

  /* Sum: '<S1>/Sum4' incorporates:
   *  Gain: '<S2>/Proportional Gain'
   *  Inport: '<Root>/IMU_Rates'
   *  Sum: '<S2>/Sum'
   */
  rtb_Sum4 = (Attitude_test_P.KRP * rtb_Sum4 + Attitude_test_B.FilterCoefficient)
    - Attitude_test_U.IMU_Rates[0];

  /* Gain: '<S3>/Filter Coefficient' incorporates:
   *  Gain: '<S3>/Derivative Gain'
   *  Integrator: '<S3>/Filter'
   *  Sum: '<S3>/SumD'
   */
  Attitude_test_B.FilterCoefficient_o = (Attitude_test_P.Kdp * rtb_Sum4 -
    Attitude_test_X.Filter_CSTATE_k) * Attitude_test_P.N;

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S3>/Proportional Gain'
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Sum_o = (Attitude_test_P.Kpp * rtb_Sum4 +
               Attitude_test_X.Integrator_CSTATE) +
    Attitude_test_B.FilterCoefficient_o;

  /* Saturate: '<S3>/Saturate' */
  if (rtb_Sum_o > Attitude_test_P.satp) {
    rtb_Saturate = Attitude_test_P.satp;
  } else if (rtb_Sum_o < -Attitude_test_P.satp) {
    rtb_Saturate = -Attitude_test_P.satp;
  } else {
    rtb_Saturate = rtb_Sum_o;
  }

  /* End of Saturate: '<S3>/Saturate' */

  /* Outport: '<Root>/Moments' incorporates:
   *  Constant: '<S1>/Constant1'
   */
  Attitude_test_Y.Moments[0] = rtb_Saturate;
  Attitude_test_Y.Moments[1] = Attitude_test_P.Constant1_Value;
  Attitude_test_Y.Moments[2] = Attitude_test_P.Constant1_Value;

  /* Sum: '<S3>/SumI1' incorporates:
   *  Gain: '<S3>/Integral Gain'
   *  Gain: '<S3>/Kb'
   *  Sum: '<S3>/SumI2'
   */
  Attitude_test_B.SumI1 = (rtb_Saturate - rtb_Sum_o) * Attitude_test_P.Kbp +
    Attitude_test_P.Kip * rtb_Sum4;
  if (rtmIsMajorTimeStep((&Attitude_test_M))) {
    rt_ertODEUpdateContinuousStates(&(&Attitude_test_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Attitude_test_M)->Timing.clockTick0)) {
      ++(&Attitude_test_M)->Timing.clockTickH0;
    }

    (&Attitude_test_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Attitude_test_M
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
      (&Attitude_test_M)->Timing.clockTick1++;
      if (!(&Attitude_test_M)->Timing.clockTick1) {
        (&Attitude_test_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Attitude_testModelClass::Attitude_test_derivatives()
{
  XDot_Attitude_test_T *_rtXdot;
  _rtXdot = ((XDot_Attitude_test_T *) (&Attitude_test_M)->ModelData.derivs);

  /* Derivatives for Integrator: '<S2>/Filter' */
  _rtXdot->Filter_CSTATE = Attitude_test_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = Attitude_test_B.SumI1;

  /* Derivatives for Integrator: '<S3>/Filter' */
  _rtXdot->Filter_CSTATE_k = Attitude_test_B.FilterCoefficient_o;
}

/* Model initialize function */
void Attitude_testModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&Attitude_test_M), 0,
                sizeof(RT_MODEL_Attitude_test_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Attitude_test_M)->solverInfo, &(&Attitude_test_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Attitude_test_M)->solverInfo, &rtmGetTPtr((&Attitude_test_M)));
    rtsiSetStepSizePtr(&(&Attitude_test_M)->solverInfo, &(&Attitude_test_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Attitude_test_M)->solverInfo, &(&Attitude_test_M)
                 ->ModelData.derivs);
    rtsiSetContStatesPtr(&(&Attitude_test_M)->solverInfo, (real_T **)
                         &(&Attitude_test_M)->ModelData.contStates);
    rtsiSetNumContStatesPtr(&(&Attitude_test_M)->solverInfo, &(&Attitude_test_M
      )->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Attitude_test_M)->solverInfo,
      &(&Attitude_test_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Attitude_test_M)->solverInfo,
      &(&Attitude_test_M)->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Attitude_test_M)->solverInfo,
      &(&Attitude_test_M)->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Attitude_test_M)->solverInfo, (&rtmGetErrorStatus((
      &Attitude_test_M))));
    rtsiSetRTModelPtr(&(&Attitude_test_M)->solverInfo, (&Attitude_test_M));
  }

  rtsiSetSimTimeStep(&(&Attitude_test_M)->solverInfo, MAJOR_TIME_STEP);
  (&Attitude_test_M)->ModelData.intgData.y = (&Attitude_test_M)->ModelData.odeY;
  (&Attitude_test_M)->ModelData.intgData.f[0] = (&Attitude_test_M)
    ->ModelData.odeF[0];
  (&Attitude_test_M)->ModelData.intgData.f[1] = (&Attitude_test_M)
    ->ModelData.odeF[1];
  (&Attitude_test_M)->ModelData.contStates = ((X_Attitude_test_T *)
    &Attitude_test_X);
  rtsiSetSolverData(&(&Attitude_test_M)->solverInfo, (void *)&(&Attitude_test_M
                    )->ModelData.intgData);
  rtsiSetSolverName(&(&Attitude_test_M)->solverInfo,"ode2");
  rtmSetTPtr((&Attitude_test_M), &(&Attitude_test_M)->Timing.tArray[0]);
  (&Attitude_test_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &Attitude_test_B), 0,
                sizeof(B_Attitude_test_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Attitude_test_X, 0,
                  sizeof(X_Attitude_test_T));
  }

  /* external inputs */
  (void) memset((void *)&Attitude_test_U, 0,
                sizeof(ExtU_Attitude_test_T));

  /* external outputs */
  (void) memset(&Attitude_test_Y.Moments[0], 0,
                3U*sizeof(real_T));

  /* InitializeConditions for Integrator: '<S2>/Filter' */
  Attitude_test_X.Filter_CSTATE = Attitude_test_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  Attitude_test_X.Integrator_CSTATE = Attitude_test_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S3>/Filter' */
  Attitude_test_X.Filter_CSTATE_k = Attitude_test_P.Filter_IC_c;
}

/* Model terminate function */
void Attitude_testModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Attitude_testModelClass::Attitude_testModelClass()
{
  static const P_Attitude_test_T Attitude_test_P_temp = {
    0.0584,                            /* Variable: KRD
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
    1.61,                              /* Variable: KRP
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
    0.091287092917527679,              /* Variable: Kbp
                                        * Referenced by: '<S3>/Kb'
                                        */
    0.006,                             /* Variable: Kdp
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
    0.72,                              /* Variable: Kip
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
    0.3,                               /* Variable: Kpp
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
    100.0,                             /* Variable: N
                                        * Referenced by:
                                        *   '<S2>/Filter Coefficient'
                                        *   '<S3>/Filter Coefficient'
                                        */
    0.52359877559829882,               /* Variable: rollMax
                                        * Referenced by: '<S1>/Yaw-rate1'
                                        */
    1.5,                               /* Variable: satp
                                        * Referenced by: '<S3>/Saturate'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
    0.0,                               /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
    0.0                                /* Expression: 0
                                        * Referenced by: '<S1>/Constant1'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Attitude_test_P = Attitude_test_P_temp;
}

/* Destructor */
Attitude_testModelClass::~Attitude_testModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Attitude_test_T * Attitude_testModelClass::getRTM()
{
  return (&Attitude_test_M);
}
