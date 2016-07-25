/*
 * Mixer.cpp
 *
 * Code generation for model "Mixer".
 *
 * Model version              : 1.19
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C++ source code generated on : Tue Jun 14 15:54:18 2016
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
   *  Inport: '<Root>/Fx'
   *  Inport: '<Root>/Fy'
   *  Inport: '<Root>/L'
   *  Inport: '<Root>/M'
   *  Inport: '<Root>/N'
   *  Inport: '<Root>/T'
   */
  tmp[0] = Mixer_U.Fx;
  tmp[1] = Mixer_U.Fy;
  tmp[2] = Mixer_U.T;
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
    { 4.3183420241075711E-14, 866.71382520247028, 4.3183429600831024E-14,
      -866.71382520247016, 6.1443142946416204E-43, -0.13501562805894779,
      -6.1443142904333463E-43, 0.13501562805894779, 866.71382437415252,
      8.0137842149747794E-7, -866.71382597690967, 8.0137842149748758E-7,
      0.13501562805894779, -2.6498364792209664E-18, -0.13501562805894776,
      -2.6498390063031644E-18, -10154.676913023777, -10154.676913023752,
      -10154.676913023784, -10154.67691302381, 1.6466940957022911E-26,
      -5.7417402550177792E-19, -1.6466940953131017E-26, 5.7417402550177792E-19,
      -3.6796348589891E-12, -73852.195731081971, -3.6796356565255569E-12,
      73852.195731081971, -2.5598365216700743E-37, -2.6163131328367615E-19,
      2.5598365216700743E-37, 2.6163131328367615E-19, 73852.195731081985,
      1.9026185600425553E-12, -73852.195731082014, 1.9026185599327143E-12,
      -1.080129492569245E-17, 5.7965377542367159E-23, 1.0801294918797602E-17,
      -5.7972286648818844E-23, 865274.28573047137, -865274.28573047137,
      865274.2857304716, -865274.2857304716, 3.0499045235986076E-10,
      3.0499045235205383E-10, 3.0499045234424685E-10, 3.0499045235013255E-10 },

    /*  Variable: x1
     * Referenced by:
     *   '<S1>/Bias1'
     *   '<S1>/Gain3'
     */
    { 6.0312, 80.4859 },
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
