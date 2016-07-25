/*
 * Forces_estimation.cpp
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

#include "Forces_estimation.h"
#include "Forces_estimation_private.h"

/* Model step function */
void Forces_estimationModelClass::step()
{
  real_T rtb_Bias1;
  real_T rtb_Product1;

  /* Bias: '<S2>/Bias' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Inport: '<Root>/u'
   */
  rtb_Bias1 = Forces_estimation_P.x1[0] * Forces_estimation_U.u[1] +
    Forces_estimation_P.x1[1];

  /* Product: '<S2>/Product1' */
  rtb_Product1 = rtb_Bias1 * rtb_Bias1;

  /* Bias: '<S2>/Bias1' incorporates:
   *  Gain: '<S2>/Gain2'
   *  Inport: '<Root>/u'
   */
  rtb_Bias1 = Forces_estimation_P.x1[0] * Forces_estimation_U.u[3] +
    Forces_estimation_P.x1[1];

  /* Outport: '<Root>/Fx_est' incorporates:
   *  Gain: '<S2>/Gain'
   *  Gain: '<S2>/Gain3'
   *  Gain: '<S2>/Gain4'
   *  Gain: '<S2>/Gain5'
   *  Inport: '<Root>/u'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product2'
   *  Product: '<S2>/Product3'
   *  Sum: '<S2>/Sum'
   *  Trigonometry: '<S2>/Trigonometric Function'
   *  Trigonometry: '<S2>/Trigonometric Function1'
   */
  Forces_estimation_Y.Fx_est = sin(Forces_estimation_P.degtorad *
    Forces_estimation_U.u[5]) * rtb_Product1 * -Forces_estimation_P.Kt + sin
    (Forces_estimation_P.degtorad * Forces_estimation_U.u[7]) * (rtb_Bias1 *
    rtb_Bias1) * Forces_estimation_P.Kt;

  /* Bias: '<S3>/Bias' incorporates:
   *  Gain: '<S3>/Gain1'
   *  Inport: '<Root>/u'
   */
  rtb_Bias1 = Forces_estimation_P.x1[0] * Forces_estimation_U.u[0] +
    Forces_estimation_P.x1[1];

  /* Product: '<S3>/Product1' */
  rtb_Product1 = rtb_Bias1 * rtb_Bias1;

  /* Bias: '<S3>/Bias1' incorporates:
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/u'
   */
  rtb_Bias1 = Forces_estimation_P.x1[0] * Forces_estimation_U.u[2] +
    Forces_estimation_P.x1[1];

  /* Outport: '<Root>/Fy_est' incorporates:
   *  Gain: '<S3>/Gain'
   *  Gain: '<S3>/Gain3'
   *  Gain: '<S3>/Gain4'
   *  Gain: '<S3>/Gain5'
   *  Inport: '<Root>/u'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product2'
   *  Product: '<S3>/Product3'
   *  Sum: '<S3>/Sum'
   *  Trigonometry: '<S3>/Trigonometric Function'
   *  Trigonometry: '<S3>/Trigonometric Function1'
   */
  Forces_estimation_Y.Fy_est = sin(Forces_estimation_P.degtorad *
    Forces_estimation_U.u[4]) * rtb_Product1 * Forces_estimation_P.Kt + sin
    (Forces_estimation_P.degtorad * Forces_estimation_U.u[6]) * (rtb_Bias1 *
    rtb_Bias1) * -Forces_estimation_P.Kt;
}

/* Model initialize function */
void Forces_estimationModelClass::initialize()
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus((&Forces_estimation_M), (NULL));

  /* external inputs */
  (void) memset(Forces_estimation_U.u, 0,
                8U*sizeof(real_T));

  /* external outputs */
  (void) memset((void *)&Forces_estimation_Y, 0,
                sizeof(ExtY_Forces_estimation_T));
}

/* Model terminate function */
void Forces_estimationModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Forces_estimationModelClass::Forces_estimationModelClass()
{
  static const P_Forces_estimation_T Forces_estimation_P_temp = {
    2.461919784758145E-5,              /* Variable: Kt
                                        * Referenced by:
                                        *   '<S2>/Gain'
                                        *   '<S2>/Gain3'
                                        *   '<S3>/Gain'
                                        *   '<S3>/Gain3'
                                        */
    0.017453292519943295,              /* Variable: degtorad
                                        * Referenced by:
                                        *   '<S2>/Gain4'
                                        *   '<S2>/Gain5'
                                        *   '<S3>/Gain4'
                                        *   '<S3>/Gain5'
                                        */

    /*  Variable: x1
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
    { 6.0312, 80.4859 }
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Forces_estimation_P = Forces_estimation_P_temp;
}

/* Destructor */
Forces_estimationModelClass::~Forces_estimationModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Forces_estimation_T * Forces_estimationModelClass::getRTM()
{
  return (&Forces_estimation_M);
}
