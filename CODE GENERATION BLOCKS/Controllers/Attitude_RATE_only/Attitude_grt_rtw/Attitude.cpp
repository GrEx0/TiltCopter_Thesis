/*
 * Attitude.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Attitude".
 *
 * Model version              : 1.96
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Mon Aug 22 16:24:09 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Attitude.h"
#include "Attitude_private.h"

/*
 * This function updates continuous states using the ODE2 fixed-step
 * solver algorithm
 */
void AttitudeModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Attitude_derivatives();

  /* f1 = f(t + h, y + h*f0) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f0[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f1);
  this->step();
  Attitude_derivatives();

  /* tnew = t + h
     ynew = y + (h/2)*(f0 + f1) */
  temp = 0.5*h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + f1[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void AttitudeModelClass::step()
{
  real_T rtb_Sum4;
  real_T rtb_Saturate;
  real_T rtb_Sum;
  real_T rtb_Sum5;
  real_T rtb_Saturate_e;
  real_T rtb_Sum_f;
  real_T rtb_Sum6;
  real_T rtb_Saturate_j0;
  real_T rtb_Sum_a;
  if (rtmIsMajorTimeStep((&Attitude_M))) {
    /* set solver stop time */
    if (!((&Attitude_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Attitude_M)->solverInfo, (((&Attitude_M)
        ->Timing.clockTickH0 + 1) * (&Attitude_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Attitude_M)->solverInfo, (((&Attitude_M)
        ->Timing.clockTick0 + 1) * (&Attitude_M)->Timing.stepSize0 +
        (&Attitude_M)->Timing.clockTickH0 * (&Attitude_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Attitude_M))) {
    (&Attitude_M)->Timing.t[0] = rtsiGetT(&(&Attitude_M)->solverInfo);
  }

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Inport: '<Root>/Stick'
   */
  if (Attitude_U.Stick[0] > Attitude_P.Saturation_UpperSat) {
    rtb_Sum6 = Attitude_P.Saturation_UpperSat;
  } else if (Attitude_U.Stick[0] < Attitude_P.Saturation_LowerSat) {
    rtb_Sum6 = Attitude_P.Saturation_LowerSat;
  } else {
    rtb_Sum6 = Attitude_U.Stick[0];
  }

  /* Sum: '<S1>/Sum4' incorporates:
   *  Inport: '<Root>/IMU_Rates'
   *  Saturate: '<S1>/Saturation'
   */
  rtb_Sum4 = rtb_Sum6 - Attitude_U.IMU_Rates[0];

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  Gain: '<S2>/Derivative Gain'
   *  Integrator: '<S2>/Filter'
   *  Sum: '<S2>/SumD'
   */
  Attitude_B.FilterCoefficient = (Attitude_P.Kdp * rtb_Sum4 -
    Attitude_X.Filter_CSTATE) * Attitude_P.N;

  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<S2>/Proportional Gain'
   *  Integrator: '<S2>/Integrator'
   */
  rtb_Sum = (Attitude_P.Kpp * rtb_Sum4 + Attitude_X.Integrator_CSTATE) +
    Attitude_B.FilterCoefficient;

  /* Saturate: '<S2>/Saturate' */
  if (rtb_Sum > Attitude_P.satp) {
    rtb_Saturate = Attitude_P.satp;
  } else if (rtb_Sum < -Attitude_P.satp) {
    rtb_Saturate = -Attitude_P.satp;
  } else {
    rtb_Saturate = rtb_Sum;
  }

  /* End of Saturate: '<S2>/Saturate' */

  /* Saturate: '<S1>/Saturation1' incorporates:
   *  Inport: '<Root>/Stick'
   */
  if (Attitude_U.Stick[1] > Attitude_P.Saturation1_UpperSat) {
    rtb_Sum6 = Attitude_P.Saturation1_UpperSat;
  } else if (Attitude_U.Stick[1] < Attitude_P.Saturation1_LowerSat) {
    rtb_Sum6 = Attitude_P.Saturation1_LowerSat;
  } else {
    rtb_Sum6 = Attitude_U.Stick[1];
  }

  /* Sum: '<S1>/Sum5' incorporates:
   *  Inport: '<Root>/IMU_Rates'
   *  Saturate: '<S1>/Saturation1'
   */
  rtb_Sum5 = rtb_Sum6 - Attitude_U.IMU_Rates[1];

  /* Gain: '<S3>/Filter Coefficient' incorporates:
   *  Gain: '<S3>/Derivative Gain'
   *  Integrator: '<S3>/Filter'
   *  Sum: '<S3>/SumD'
   */
  Attitude_B.FilterCoefficient_b = (Attitude_P.Kdq * rtb_Sum5 -
    Attitude_X.Filter_CSTATE_e) * Attitude_P.N;

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S3>/Proportional Gain'
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Sum_f = (Attitude_P.Kpq * rtb_Sum5 + Attitude_X.Integrator_CSTATE_f) +
    Attitude_B.FilterCoefficient_b;

  /* Saturate: '<S3>/Saturate' */
  if (rtb_Sum_f > Attitude_P.satq) {
    rtb_Saturate_e = Attitude_P.satq;
  } else if (rtb_Sum_f < -Attitude_P.satq) {
    rtb_Saturate_e = -Attitude_P.satq;
  } else {
    rtb_Saturate_e = rtb_Sum_f;
  }

  /* End of Saturate: '<S3>/Saturate' */

  /* Saturate: '<S1>/Saturation2' incorporates:
   *  Inport: '<Root>/Stick'
   */
  if (Attitude_U.Stick[2] > Attitude_P.Saturation2_UpperSat) {
    rtb_Sum6 = Attitude_P.Saturation2_UpperSat;
  } else if (Attitude_U.Stick[2] < Attitude_P.Saturation2_LowerSat) {
    rtb_Sum6 = Attitude_P.Saturation2_LowerSat;
  } else {
    rtb_Sum6 = Attitude_U.Stick[2];
  }

  /* Sum: '<S1>/Sum6' incorporates:
   *  Inport: '<Root>/IMU_Rates'
   *  Saturate: '<S1>/Saturation2'
   */
  rtb_Sum6 -= Attitude_U.IMU_Rates[2];

  /* Gain: '<S4>/Filter Coefficient' incorporates:
   *  Gain: '<S4>/Derivative Gain'
   *  Integrator: '<S4>/Filter'
   *  Sum: '<S4>/SumD'
   */
  Attitude_B.FilterCoefficient_o = (Attitude_P.Kdr * rtb_Sum6 -
    Attitude_X.Filter_CSTATE_g) * Attitude_P.N;

  /* Sum: '<S4>/Sum' incorporates:
   *  Gain: '<S4>/Proportional Gain'
   *  Integrator: '<S4>/Integrator'
   */
  rtb_Sum_a = (Attitude_P.Kpr * rtb_Sum6 + Attitude_X.Integrator_CSTATE_h) +
    Attitude_B.FilterCoefficient_o;

  /* Saturate: '<S4>/Saturate' */
  if (rtb_Sum_a > Attitude_P.satr) {
    rtb_Saturate_j0 = Attitude_P.satr;
  } else if (rtb_Sum_a < -Attitude_P.satr) {
    rtb_Saturate_j0 = -Attitude_P.satr;
  } else {
    rtb_Saturate_j0 = rtb_Sum_a;
  }

  /* End of Saturate: '<S4>/Saturate' */

  /* Outport: '<Root>/Moments' */
  Attitude_Y.Moments[0] = rtb_Saturate;
  Attitude_Y.Moments[1] = rtb_Saturate_e;
  Attitude_Y.Moments[2] = rtb_Saturate_j0;

  /* Sum: '<S2>/SumI1' incorporates:
   *  Gain: '<S2>/Integral Gain'
   *  Gain: '<S2>/Kb'
   *  Sum: '<S2>/SumI2'
   */
  Attitude_B.SumI1 = (rtb_Saturate - rtb_Sum) * Attitude_P.Kbp + Attitude_P.Kip *
    rtb_Sum4;

  /* Sum: '<S3>/SumI1' incorporates:
   *  Gain: '<S3>/Integral Gain'
   *  Gain: '<S3>/Kb'
   *  Sum: '<S3>/SumI2'
   */
  Attitude_B.SumI1_e = (rtb_Saturate_e - rtb_Sum_f) * Attitude_P.Kbq +
    Attitude_P.Kiq * rtb_Sum5;

  /* Sum: '<S4>/SumI1' incorporates:
   *  Gain: '<S4>/Integral Gain'
   *  Gain: '<S4>/Kb'
   *  Sum: '<S4>/SumI2'
   */
  Attitude_B.SumI1_k = (rtb_Saturate_j0 - rtb_Sum_a) * Attitude_P.Kbr +
    Attitude_P.Kir * rtb_Sum6;
  if (rtmIsMajorTimeStep((&Attitude_M))) {
    rt_ertODEUpdateContinuousStates(&(&Attitude_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Attitude_M)->Timing.clockTick0)) {
      ++(&Attitude_M)->Timing.clockTickH0;
    }

    (&Attitude_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Attitude_M)
      ->solverInfo);

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
      (&Attitude_M)->Timing.clockTick1++;
      if (!(&Attitude_M)->Timing.clockTick1) {
        (&Attitude_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void AttitudeModelClass::Attitude_derivatives()
{
  XDot_Attitude_T *_rtXdot;
  _rtXdot = ((XDot_Attitude_T *) (&Attitude_M)->ModelData.derivs);

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE = Attitude_B.SumI1;

  /* Derivatives for Integrator: '<S2>/Filter' */
  _rtXdot->Filter_CSTATE = Attitude_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE_f = Attitude_B.SumI1_e;

  /* Derivatives for Integrator: '<S3>/Filter' */
  _rtXdot->Filter_CSTATE_e = Attitude_B.FilterCoefficient_b;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE_h = Attitude_B.SumI1_k;

  /* Derivatives for Integrator: '<S4>/Filter' */
  _rtXdot->Filter_CSTATE_g = Attitude_B.FilterCoefficient_o;
}

/* Model initialize function */
void AttitudeModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&Attitude_M), 0,
                sizeof(RT_MODEL_Attitude_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Attitude_M)->solverInfo, &rtmGetTPtr((&Attitude_M)));
    rtsiSetStepSizePtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)->ModelData.derivs);
    rtsiSetContStatesPtr(&(&Attitude_M)->solverInfo, (real_T **) &(&Attitude_M
                         )->ModelData.contStates);
    rtsiSetNumContStatesPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M)
      ->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Attitude_M)->solverInfo, &(&Attitude_M
      )->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Attitude_M)->solverInfo, (&rtmGetErrorStatus
      ((&Attitude_M))));
    rtsiSetRTModelPtr(&(&Attitude_M)->solverInfo, (&Attitude_M));
  }

  rtsiSetSimTimeStep(&(&Attitude_M)->solverInfo, MAJOR_TIME_STEP);
  (&Attitude_M)->ModelData.intgData.y = (&Attitude_M)->ModelData.odeY;
  (&Attitude_M)->ModelData.intgData.f[0] = (&Attitude_M)->ModelData.odeF[0];
  (&Attitude_M)->ModelData.intgData.f[1] = (&Attitude_M)->ModelData.odeF[1];
  (&Attitude_M)->ModelData.contStates = ((X_Attitude_T *) &Attitude_X);
  rtsiSetSolverData(&(&Attitude_M)->solverInfo, (void *)&(&Attitude_M)
                    ->ModelData.intgData);
  rtsiSetSolverName(&(&Attitude_M)->solverInfo,"ode2");
  rtmSetTPtr((&Attitude_M), &(&Attitude_M)->Timing.tArray[0]);
  (&Attitude_M)->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &Attitude_B), 0,
                sizeof(B_Attitude_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Attitude_X, 0,
                  sizeof(X_Attitude_T));
  }

  /* external inputs */
  (void) memset((void *)&Attitude_U, 0,
                sizeof(ExtU_Attitude_T));

  /* external outputs */
  (void) memset(&Attitude_Y.Moments[0], 0,
                3U*sizeof(real_T));

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  Attitude_X.Integrator_CSTATE = Attitude_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S2>/Filter' */
  Attitude_X.Filter_CSTATE = Attitude_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  Attitude_X.Integrator_CSTATE_f = Attitude_P.Integrator_IC_l;

  /* InitializeConditions for Integrator: '<S3>/Filter' */
  Attitude_X.Filter_CSTATE_e = Attitude_P.Filter_IC_f;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  Attitude_X.Integrator_CSTATE_h = Attitude_P.Integrator_IC_k;

  /* InitializeConditions for Integrator: '<S4>/Filter' */
  Attitude_X.Filter_CSTATE_g = Attitude_P.Filter_IC_a;
}

/* Model terminate function */
void AttitudeModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
AttitudeModelClass::AttitudeModelClass()
{
  static const P_Attitude_T Attitude_P_temp = {
    0.35355339059327379,               /* Variable: Kbp
                                        * Referenced by: '<S2>/Kb'
                                        */
    0.35355339059327379,               /* Variable: Kbq
                                        * Referenced by: '<S3>/Kb'
                                        */
    0.34985711369071804,               /* Variable: Kbr
                                        * Referenced by: '<S4>/Kb'
                                        */
    0.1,                               /* Variable: Kdp
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
    0.1,                               /* Variable: Kdq
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
    0.0153,                            /* Variable: Kdr
                                        * Referenced by: '<S4>/Derivative Gain'
                                        */
    0.8,                               /* Variable: Kip
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
    0.8,                               /* Variable: Kiq
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
    0.125,                             /* Variable: Kir
                                        * Referenced by: '<S4>/Integral Gain'
                                        */
    0.6,                               /* Variable: Kpp
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
    0.6,                               /* Variable: Kpq
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
    0.135,                             /* Variable: Kpr
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
    100.0,                             /* Variable: N
                                        * Referenced by:
                                        *   '<S2>/Filter Coefficient'
                                        *   '<S3>/Filter Coefficient'
                                        *   '<S4>/Filter Coefficient'
                                        */
    1.5,                               /* Variable: satp
                                        * Referenced by: '<S2>/Saturate'
                                        */
    1.5,                               /* Variable: satq
                                        * Referenced by: '<S3>/Saturate'
                                        */
    1.0,                               /* Variable: satr
                                        * Referenced by: '<S4>/Saturate'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation'
                                        */
    0.0,                               /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    0.0,                               /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
    0.0,                               /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
    1.0,                               /* Expression: 1
                                        * Referenced by: '<S1>/Saturation2'
                                        */
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Saturation2'
                                        */
    0.0,                               /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S4>/Integrator'
                                        */
    0.0                                /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S4>/Filter'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Attitude_P = Attitude_P_temp;
}

/* Destructor */
AttitudeModelClass::~AttitudeModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Attitude_T * AttitudeModelClass::getRTM()
{
  return (&Attitude_M);
}
