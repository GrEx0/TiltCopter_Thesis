/*
 * Mixer.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Mixer".
 *
 * Model version              : 1.20
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Tue Aug 23 10:33:57 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Mixer.h"
#include "Mixer_private.h"

/* Model step function */
void MixerModelClass::step()
{
  real_T rtb_Gain2[8];
  real_T tmp[6];
  int32_T i;
  int32_T i_0;
  real_T rtb_rad2deg_idx_0;
  real_T rtb_rad2deg_idx_1;
  real_T rtb_rad2deg_idx_2;
  real_T rtb_rad2deg_idx_3;
  real_T rtb_Gain2_0;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtGain2Inport1' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/Fx'
   *  Inport: '<Root>/Fy'
   *  Inport: '<Root>/L'
   *  Inport: '<Root>/M'
   *  Inport: '<Root>/N'
   *  Inport: '<Root>/T'
   */
  tmp[0] = Mixer_U.Fx;
  tmp[1] = Mixer_U.Fy;
  tmp[2] = Mixer_P.Gain_Gain * Mixer_U.T;
  tmp[3] = Mixer_U.L;
  tmp[4] = Mixer_U.M;
  tmp[5] = Mixer_U.N;

  /* Gain: '<S1>/Gain2' */
  for (i = 0; i < 8; i++) {
    rtb_Gain2[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Gain2[i] += Mixer_P.Kinv[(i_0 << 3) + i] * tmp[i_0];
    }
  }

  /* End of Gain: '<S1>/Gain2' */

  /* Gain: '<S1>/Gain3' */
  rtb_rad2deg_idx_3 = 1.0 / Mixer_P.x1[0];

  /* Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  if (rtb_Gain2[0] < 0.0) {
    rtb_Gain2_0 = -sqrt(fabs(rtb_Gain2[0]));
  } else {
    rtb_Gain2_0 = sqrt(rtb_Gain2[0]);
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Bias: '<S1>/Bias1'
   *  Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  rtb_rad2deg_idx_0 = (rtb_Gain2_0 + -Mixer_P.x1[1]) * rtb_rad2deg_idx_3;

  /* Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  if (rtb_Gain2[1] < 0.0) {
    rtb_Gain2_0 = -sqrt(fabs(rtb_Gain2[1]));
  } else {
    rtb_Gain2_0 = sqrt(rtb_Gain2[1]);
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Bias: '<S1>/Bias1'
   *  Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  rtb_rad2deg_idx_1 = (rtb_Gain2_0 + -Mixer_P.x1[1]) * rtb_rad2deg_idx_3;

  /* Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  if (rtb_Gain2[2] < 0.0) {
    rtb_Gain2_0 = -sqrt(fabs(rtb_Gain2[2]));
  } else {
    rtb_Gain2_0 = sqrt(rtb_Gain2[2]);
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Bias: '<S1>/Bias1'
   *  Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  rtb_rad2deg_idx_2 = (rtb_Gain2_0 + -Mixer_P.x1[1]) * rtb_rad2deg_idx_3;

  /* Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  if (rtb_Gain2[3] < 0.0) {
    rtb_Gain2_0 = -sqrt(fabs(rtb_Gain2[3]));
  } else {
    rtb_Gain2_0 = sqrt(rtb_Gain2[3]);
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Bias: '<S1>/Bias1'
   *  Sqrt: '<S1>/Sqrt1'
   *
   * About '<S1>/Sqrt1':
   *  Operator: signedSqrt
   */
  rtb_rad2deg_idx_3 *= rtb_Gain2_0 + -Mixer_P.x1[1];

  /* Saturate: '<S1>/Saturation1' */
  if (rtb_rad2deg_idx_0 > Mixer_P.Saturation1_UpperSat) {
    /* Outport: '<Root>/th1' */
    Mixer_Y.th1 = Mixer_P.Saturation1_UpperSat;
  } else if (rtb_rad2deg_idx_0 < Mixer_P.Saturation1_LowerSat) {
    /* Outport: '<Root>/th1' */
    Mixer_Y.th1 = Mixer_P.Saturation1_LowerSat;
  } else {
    /* Outport: '<Root>/th1' */
    Mixer_Y.th1 = rtb_rad2deg_idx_0;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Saturate: '<S1>/Saturation2' */
  if (rtb_rad2deg_idx_1 > Mixer_P.Saturation2_UpperSat) {
    /* Outport: '<Root>/th2' */
    Mixer_Y.th2 = Mixer_P.Saturation2_UpperSat;
  } else if (rtb_rad2deg_idx_1 < Mixer_P.Saturation2_LowerSat) {
    /* Outport: '<Root>/th2' */
    Mixer_Y.th2 = Mixer_P.Saturation2_LowerSat;
  } else {
    /* Outport: '<Root>/th2' */
    Mixer_Y.th2 = rtb_rad2deg_idx_1;
  }

  /* End of Saturate: '<S1>/Saturation2' */

  /* Saturate: '<S1>/Saturation3' */
  if (rtb_rad2deg_idx_2 > Mixer_P.Saturation3_UpperSat) {
    /* Outport: '<Root>/th3' */
    Mixer_Y.th3 = Mixer_P.Saturation3_UpperSat;
  } else if (rtb_rad2deg_idx_2 < Mixer_P.Saturation3_LowerSat) {
    /* Outport: '<Root>/th3' */
    Mixer_Y.th3 = Mixer_P.Saturation3_LowerSat;
  } else {
    /* Outport: '<Root>/th3' */
    Mixer_Y.th3 = rtb_rad2deg_idx_2;
  }

  /* End of Saturate: '<S1>/Saturation3' */

  /* Saturate: '<S1>/Saturation8' */
  if (rtb_rad2deg_idx_3 > Mixer_P.Saturation8_UpperSat) {
    /* Outport: '<Root>/th4 ' */
    Mixer_Y.th4 = Mixer_P.Saturation8_UpperSat;
  } else if (rtb_rad2deg_idx_3 < Mixer_P.Saturation8_LowerSat) {
    /* Outport: '<Root>/th4 ' */
    Mixer_Y.th4 = Mixer_P.Saturation8_LowerSat;
  } else {
    /* Outport: '<Root>/th4 ' */
    Mixer_Y.th4 = rtb_rad2deg_idx_3;
  }

  /* End of Saturate: '<S1>/Saturation8' */

  /* Gain: '<S1>/rad2deg' */
  rtb_rad2deg_idx_0 = Mixer_P.rad2deg_Gain * rtb_Gain2[4];
  rtb_rad2deg_idx_1 = Mixer_P.rad2deg_Gain * rtb_Gain2[5];
  rtb_rad2deg_idx_2 = Mixer_P.rad2deg_Gain * rtb_Gain2[6];
  rtb_rad2deg_idx_3 = Mixer_P.rad2deg_Gain * rtb_Gain2[7];

  /* Saturate: '<S1>/Saturation4' */
  if (rtb_rad2deg_idx_0 > Mixer_P.Saturation4_UpperSat) {
    /* Outport: '<Root>/alpha1' */
    Mixer_Y.alpha1 = Mixer_P.Saturation4_UpperSat;
  } else if (rtb_rad2deg_idx_0 < Mixer_P.Saturation4_LowerSat) {
    /* Outport: '<Root>/alpha1' */
    Mixer_Y.alpha1 = Mixer_P.Saturation4_LowerSat;
  } else {
    /* Outport: '<Root>/alpha1' */
    Mixer_Y.alpha1 = rtb_rad2deg_idx_0;
  }

  /* End of Saturate: '<S1>/Saturation4' */

  /* Saturate: '<S1>/Saturation5' */
  if (rtb_rad2deg_idx_1 > Mixer_P.Saturation5_UpperSat) {
    /* Outport: '<Root>/alpha2' */
    Mixer_Y.alpha2 = Mixer_P.Saturation5_UpperSat;
  } else if (rtb_rad2deg_idx_1 < Mixer_P.Saturation5_LowerSat) {
    /* Outport: '<Root>/alpha2' */
    Mixer_Y.alpha2 = Mixer_P.Saturation5_LowerSat;
  } else {
    /* Outport: '<Root>/alpha2' */
    Mixer_Y.alpha2 = rtb_rad2deg_idx_1;
  }

  /* End of Saturate: '<S1>/Saturation5' */

  /* Saturate: '<S1>/Saturation6' */
  if (rtb_rad2deg_idx_2 > Mixer_P.Saturation6_UpperSat) {
    /* Outport: '<Root>/alpha3' */
    Mixer_Y.alpha3 = Mixer_P.Saturation6_UpperSat;
  } else if (rtb_rad2deg_idx_2 < Mixer_P.Saturation6_LowerSat) {
    /* Outport: '<Root>/alpha3' */
    Mixer_Y.alpha3 = Mixer_P.Saturation6_LowerSat;
  } else {
    /* Outport: '<Root>/alpha3' */
    Mixer_Y.alpha3 = rtb_rad2deg_idx_2;
  }

  /* End of Saturate: '<S1>/Saturation6' */

  /* Saturate: '<S1>/Saturation7' */
  if (rtb_rad2deg_idx_3 > Mixer_P.Saturation7_UpperSat) {
    /* Outport: '<Root>/alpha4' */
    Mixer_Y.alpha4 = Mixer_P.Saturation7_UpperSat;
  } else if (rtb_rad2deg_idx_3 < Mixer_P.Saturation7_LowerSat) {
    /* Outport: '<Root>/alpha4' */
    Mixer_Y.alpha4 = Mixer_P.Saturation7_LowerSat;
  } else {
    /* Outport: '<Root>/alpha4' */
    Mixer_Y.alpha4 = rtb_rad2deg_idx_3;
  }

  /* End of Saturate: '<S1>/Saturation7' */
}

/* Model initialize function */
void MixerModelClass::initialize()
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus((&Mixer_M), (NULL));

  /* external inputs */
  (void) memset((void *)&Mixer_U, 0,
                sizeof(ExtU_Mixer_T));

  /* external outputs */
  (void) memset((void *)&Mixer_Y, 0,
                sizeof(ExtY_Mixer_T));
}

/* Model terminate function */
void MixerModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
MixerModelClass::MixerModelClass()
{
  static const P_Mixer_T Mixer_P_temp = {
    /*  Variable: Kinv
     * Referenced by: '<S1>/Gain2'
     */
    { -4.3183434280708623E-14, -866.71382520247016, -4.3183415561198055E-14,
      866.71382520247016, -1.3855831797716327E-42, -0.10730189387842692,
      1.3855831797733843E-42, 0.10730189387842692, -866.71382515981259,
      -1.3331234092952364E-12, 866.71382515981509, -1.3331233905757263E-12,
      0.10730189387842695, -5.4627536149490614E-22, -0.10730189387842692,
      -5.4426699616933376E-22, -10154.676913023772, -10154.676913023746,
      -10154.67691302377, -10154.676913023803, -5.3128257148555141E-25,
      4.5629701806175144E-19, 5.3128257148555123E-25, -4.5629701806175144E-19,
      -3.6796332907164983E-12, -73852.195731081956, -3.6796344602208693E-12,
      73852.195731081971, -6.4419727042845414E-37, -6.9317977837476526E-21,
      6.4419727042845414E-37, 6.9317977837476526E-21, 73852.195731082,
      3.2205931573820389E-13, -73852.195731082014, 3.2205931595789224E-13,
      -6.8940819640529957E-18, 1.1594117652808642E-22, 6.8940819640445255E-18,
      -1.1594117652748007E-22, -865274.28510344832, 865274.2851034482,
      -865274.28510344843, 865274.28510344843, 3.8376282055947247E-10,
      3.8376282055849862E-10, 3.8376282056344061E-10, 3.8376282056041996E-10 },

    /*  Variable: x1
     * Referenced by:
     *   '<S1>/Bias1'
     *   '<S1>/Gain3'
     */
    { 6.0312, 80.4859 },
    -1.0,                              /* Expression: -1
                                        * Referenced by: '<S1>/Gain'
                                        */
    100.0,                             /* Expression: 100
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S1>/Saturation1'
                                        */
    100.0,                             /* Expression: 100
                                        * Referenced by: '<S1>/Saturation2'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S1>/Saturation2'
                                        */
    100.0,                             /* Expression: 100
                                        * Referenced by: '<S1>/Saturation3'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S1>/Saturation3'
                                        */
    100.0,                             /* Expression: 100
                                        * Referenced by: '<S1>/Saturation8'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S1>/Saturation8'
                                        */
    57.295779513082323,                /* Expression: 180/pi
                                        * Referenced by: '<S1>/rad2deg'
                                        */
    45.0,                              /* Expression: 45
                                        * Referenced by: '<S1>/Saturation4'
                                        */
    -45.0,                             /* Expression: -45
                                        * Referenced by: '<S1>/Saturation4'
                                        */
    45.0,                              /* Expression: 45
                                        * Referenced by: '<S1>/Saturation5'
                                        */
    -45.0,                             /* Expression: -45
                                        * Referenced by: '<S1>/Saturation5'
                                        */
    45.0,                              /* Expression: 45
                                        * Referenced by: '<S1>/Saturation6'
                                        */
    -45.0,                             /* Expression: -45
                                        * Referenced by: '<S1>/Saturation6'
                                        */
    45.0,                              /* Expression: 45
                                        * Referenced by: '<S1>/Saturation7'
                                        */
    -45.0                              /* Expression: -45
                                        * Referenced by: '<S1>/Saturation7'
                                        */
  };                                   /* Modifiable parameters */

  /* Initialize tunable parameters */
  Mixer_P = Mixer_P_temp;
}

/* Destructor */
MixerModelClass::~MixerModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Mixer_T * MixerModelClass::getRTM()
{
  return (&Mixer_M);
}
