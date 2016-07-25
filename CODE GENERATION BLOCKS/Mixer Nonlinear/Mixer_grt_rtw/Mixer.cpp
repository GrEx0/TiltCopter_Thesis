/*
 * Mixer.cpp
 *
 * Code generation for model "Mixer".
 *
 * Model version              : 1.19
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C++ source code generated on : Tue Jun 14 14:30:30 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Mixer.h"
#include "Mixer_private.h"

/* Named constants for MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix' */
#define Mixer_Kq                       (2.8892572426134866E-7)

/* Model step function */
void MixerModelClass::step()
{
  real_T alpha_2;
  real_T alpha_1;
  real_T c_alpha1;
  real_T s_alpha1;
  real_T c_alpha2;
  real_T s_alpha2;
  real_T c_alpha3;
  real_T s_alpha3;
  real_T c_alpha4;
  real_T s_alpha4;
  real_T x;
  real_T tmp[16];
  real_T tmp_0[4];
  int32_T i;

  /* MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix' incorporates:
   *  Inport: '<Root>/Fx'
   *  Inport: '<Root>/Fy'
   *  Inport: '<Root>/L'
   *  Inport: '<Root>/M'
   *  Inport: '<Root>/N'
   *  Inport: '<Root>/T'
   */
  /* MATLAB Function 'Inverted NONLINEAR mixer matrix': '<S1>:1' */
  /* '<S1>:1:3' */
  alpha_2 = Mixer_U.Fx / 7.4065500000000011;
  x = asin(alpha_2);
  alpha_2 = -asin(alpha_2);

  /* '<S1>:1:5' */
  alpha_1 = asin(Mixer_U.Fy / 7.4065500000000011);

  /* '<S1>:1:6' */
  /* '<S1>:1:7' */
  /* '<S1>:1:9' */
  c_alpha1 = cos(alpha_1);

  /* '<S1>:1:10' */
  s_alpha1 = sin(alpha_1);

  /* '<S1>:1:11' */
  c_alpha2 = cos(-x);

  /* '<S1>:1:12' */
  s_alpha2 = sin(-x);

  /* '<S1>:1:13' */
  c_alpha3 = cos(-alpha_1);

  /* '<S1>:1:14' */
  s_alpha3 = sin(-alpha_1);

  /* '<S1>:1:15' */
  c_alpha4 = cos(-alpha_2);

  /* '<S1>:1:16' */
  s_alpha4 = sin(-alpha_2);

  /* '<S1>:1:19' */
  /* '<S1>:1:24' */
  /* '<S1>:1:25' */
  tmp[0] = -(((((((((((2.4118963030826135E-20 * c_alpha2 * s_alpha3 * s_alpha4 +
                       2.4118963030826135E-20 * c_alpha4 * s_alpha2 * s_alpha3)
                      + 3.1032715283404387E-16 * c_alpha2 * c_alpha3 * s_alpha4)
                     + 3.1032715283404387E-16 * c_alpha3 * c_alpha4 * s_alpha2)
                    - 5.651698863762534E-19 * c_alpha2 * c_alpha3 * s_alpha4) +
                   1.1303397727525068E-18 * c_alpha2 * c_alpha4 * s_alpha3) -
                  5.651698863762534E-19 * c_alpha3 * c_alpha4 * s_alpha2) -
                 1.1303397727525068E-18 * s_alpha2 * s_alpha3 * s_alpha4) -
                2.6486793819311745E-17 * c_alpha2 * c_alpha3 * c_alpha4) -
               1.3243396909655873E-17 * c_alpha2 * s_alpha3 * s_alpha4) +
              2.6486793819311745E-17 * c_alpha3 * s_alpha2 * s_alpha4) -
             1.3243396909655873E-17 * c_alpha4 * s_alpha2 * s_alpha3) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) *
     4.92383956951629E-5);
  tmp[4] = (((4.583668326353841E-11 * c_alpha2 * c_alpha3 * s_alpha4 -
              4.583668326353841E-11 * c_alpha3 * c_alpha4 * s_alpha2) -
             1.9561078814326244E-12 * c_alpha2 * s_alpha3 * s_alpha4) +
            1.9561078814326244E-12 * c_alpha4 * s_alpha2 * s_alpha3) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[8] = -((((((((1.6695614827988976E-13 * c_alpha2 * c_alpha3 * s_alpha4 +
                    1.6695614827988976E-13 * c_alpha3 * c_alpha4 * s_alpha2) -
                   4.583668326353841E-11 * c_alpha2 * c_alpha3 * s_alpha4) +
                  9.167336652707682E-11 * c_alpha2 * c_alpha4 * s_alpha3) -
                 4.583668326353841E-11 * c_alpha3 * c_alpha4 * s_alpha2) +
                7.8244315257304975E-12 * c_alpha2 * c_alpha3 * c_alpha4) +
               1.9561078814326244E-12 * c_alpha2 * s_alpha3 * s_alpha4) -
              3.9122157628652488E-12 * c_alpha3 * s_alpha2 * s_alpha4) +
             1.9561078814326244E-12 * c_alpha4 * s_alpha2 * s_alpha3) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[12] = (((((8.3478074139944878E-14 * c_alpha2 * s_alpha3 * s_alpha4 +
                 8.3478074139944878E-14 * c_alpha4 * s_alpha2 * s_alpha3) -
                9.167336652707682E-11 * c_alpha2 * c_alpha3 * c_alpha4) -
               1.9561078814326244E-12 * c_alpha2 * c_alpha3 * s_alpha4) +
              3.9122157628652488E-12 * c_alpha2 * c_alpha4 * s_alpha3) -
             1.9561078814326244E-12 * c_alpha3 * c_alpha4 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[1] = -((((((8.3478074139944878E-14 * c_alpha1 * s_alpha3 +
                  8.3478074139944878E-14 * c_alpha3 * s_alpha1) -
                 4.583668326353841E-11 * c_alpha1 * s_alpha3) -
                4.583668326353841E-11 * c_alpha3 * s_alpha1) +
               3.9122157628652488E-12 * s_alpha1 * s_alpha3) -
              3.9122157628652488E-12 * c_alpha1 * c_alpha3) * (Mixer_Kq *
              s_alpha4 + 6.770279408084899E-6 * c_alpha4)) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) *
     4.92383956951629E-5);
  tmp[5] = ((((((((4.583668326353841E-11 * c_alpha1 * c_alpha4 * s_alpha3 -
                   1.6695614827988976E-13 * c_alpha3 * c_alpha4 * s_alpha1) -
                  9.167336652707682E-11 * c_alpha1 * c_alpha3 * s_alpha4) -
                 1.6695614827988976E-13 * c_alpha1 * c_alpha4 * s_alpha3) +
                4.583668326353841E-11 * c_alpha3 * c_alpha4 * s_alpha1) +
               7.8244315257304975E-12 * c_alpha1 * c_alpha3 * c_alpha4) +
              1.9561078814326244E-12 * c_alpha1 * s_alpha3 * s_alpha4) +
             1.9561078814326244E-12 * c_alpha3 * s_alpha1 * s_alpha4) -
            3.9122157628652488E-12 * c_alpha4 * s_alpha1 * s_alpha3) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[9] = (6.770279408084899E-6 * c_alpha1 * s_alpha3 - 6.770279408084899E-6 *
            c_alpha3 * s_alpha1) * (Mixer_Kq * s_alpha4 + 6.770279408084899E-6 *
    c_alpha4) / (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 *
    c_alpha2 * s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 *
    c_alpha4 * s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 *
    c_alpha3 * s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 *
    c_alpha4 * s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 *
    c_alpha2 * c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 *
    c_alpha2 * c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
    c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 * c_alpha2 *
    c_alpha3 * c_alpha4 * s_alpha1) - 5.2973587638623491E-17 * c_alpha1 *
    c_alpha2 * c_alpha3 * c_alpha4) - 1.3243396909655873E-17 * c_alpha1 *
    c_alpha2 * s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
    c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 * c_alpha1 *
    c_alpha4 * s_alpha2 * s_alpha3) - 1.3243396909655873E-17 * c_alpha2 *
    c_alpha3 * s_alpha1 * s_alpha4) + 2.6486793819311745E-17 * c_alpha2 *
    c_alpha4 * s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
    c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 * c_alpha1 *
    c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18 * c_alpha1 *
                        c_alpha2 * c_alpha4 * s_alpha3) - 1.1303397727525068E-18
                       * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
                      1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 *
                      s_alpha1) - 5.651698863762534E-19 * c_alpha1 * s_alpha2 *
                     s_alpha3 * s_alpha4) + 5.651698863762534E-19 * c_alpha2 *
                    s_alpha1 * s_alpha3 * s_alpha4) - 5.651698863762534E-19 *
                   c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
                  5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 *
                  s_alpha3) * 2.0);
  tmp[13] = -(((Mixer_Kq * c_alpha1 * s_alpha3 + Mixer_Kq * c_alpha3 * s_alpha1)
               - 1.3540558816169798E-5 * c_alpha1 * c_alpha3) * (Mixer_Kq *
    s_alpha4 + 6.770279408084899E-6 * c_alpha4)) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[2] = -(((((((((((2.4118963030826135E-20 * c_alpha2 * s_alpha1 * s_alpha4 +
                       2.4118963030826135E-20 * c_alpha4 * s_alpha1 * s_alpha2)
                      + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 * s_alpha4)
                     + 3.1032715283404387E-16 * c_alpha1 * c_alpha4 * s_alpha2)
                    - 5.651698863762534E-19 * c_alpha1 * c_alpha2 * s_alpha4) -
                   5.651698863762534E-19 * c_alpha1 * c_alpha4 * s_alpha2) +
                  1.1303397727525068E-18 * c_alpha2 * c_alpha4 * s_alpha1) -
                 1.1303397727525068E-18 * s_alpha1 * s_alpha2 * s_alpha4) -
                2.6486793819311745E-17 * c_alpha1 * c_alpha2 * c_alpha4) +
               2.6486793819311745E-17 * c_alpha1 * s_alpha2 * s_alpha4) -
              1.3243396909655873E-17 * c_alpha2 * s_alpha1 * s_alpha4) -
             1.3243396909655873E-17 * c_alpha4 * s_alpha1 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) *
     4.92383956951629E-5);
  tmp[6] = (((4.583668326353841E-11 * c_alpha1 * c_alpha2 * s_alpha4 -
              4.583668326353841E-11 * c_alpha1 * c_alpha4 * s_alpha2) -
             1.9561078814326244E-12 * c_alpha2 * s_alpha1 * s_alpha4) +
            1.9561078814326244E-12 * c_alpha4 * s_alpha1 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[10] = ((((((((1.6695614827988976E-13 * c_alpha1 * c_alpha2 * s_alpha4 +
                    1.6695614827988976E-13 * c_alpha1 * c_alpha4 * s_alpha2) -
                   4.583668326353841E-11 * c_alpha1 * c_alpha2 * s_alpha4) -
                  4.583668326353841E-11 * c_alpha1 * c_alpha4 * s_alpha2) +
                 9.167336652707682E-11 * c_alpha2 * c_alpha4 * s_alpha1) +
                7.8244315257304975E-12 * c_alpha1 * c_alpha2 * c_alpha4) -
               3.9122157628652488E-12 * c_alpha1 * s_alpha2 * s_alpha4) +
              1.9561078814326244E-12 * c_alpha2 * s_alpha1 * s_alpha4) +
             1.9561078814326244E-12 * c_alpha4 * s_alpha1 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[14] = (((((8.3478074139944878E-14 * c_alpha2 * s_alpha1 * s_alpha4 +
                 8.3478074139944878E-14 * c_alpha4 * s_alpha1 * s_alpha2) -
                9.167336652707682E-11 * c_alpha1 * c_alpha2 * c_alpha4) -
               1.9561078814326244E-12 * c_alpha1 * c_alpha2 * s_alpha4) -
              1.9561078814326244E-12 * c_alpha1 * c_alpha4 * s_alpha2) +
             3.9122157628652488E-12 * c_alpha2 * c_alpha4 * s_alpha1) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[3] = -(((((((((((2.4118963030826135E-20 * c_alpha1 * s_alpha2 * s_alpha3 +
                       2.4118963030826135E-20 * c_alpha3 * s_alpha1 * s_alpha2)
                      - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 * s_alpha3)
                     - 3.1032715283404387E-16 * c_alpha2 * c_alpha3 * s_alpha1)
                    + 5.651698863762534E-19 * c_alpha1 * c_alpha2 * s_alpha3) -
                   1.1303397727525068E-18 * c_alpha1 * c_alpha3 * s_alpha2) +
                  5.651698863762534E-19 * c_alpha2 * c_alpha3 * s_alpha1) +
                 1.1303397727525068E-18 * s_alpha1 * s_alpha2 * s_alpha3) -
                2.6486793819311745E-17 * c_alpha1 * c_alpha2 * c_alpha3) -
               1.3243396909655873E-17 * c_alpha1 * s_alpha2 * s_alpha3) +
              2.6486793819311745E-17 * c_alpha2 * s_alpha1 * s_alpha3) -
             1.3243396909655873E-17 * c_alpha3 * s_alpha1 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) *
     4.92383956951629E-5);
  tmp[7] = -((((((((4.583668326353841E-11 * c_alpha1 * c_alpha2 * s_alpha3 -
                    1.6695614827988976E-13 * c_alpha2 * c_alpha3 * s_alpha1) -
                   1.6695614827988976E-13 * c_alpha1 * c_alpha2 * s_alpha3) -
                  9.167336652707682E-11 * c_alpha1 * c_alpha3 * s_alpha2) +
                 4.583668326353841E-11 * c_alpha2 * c_alpha3 * s_alpha1) +
                7.8244315257304975E-12 * c_alpha1 * c_alpha2 * c_alpha3) +
               1.9561078814326244E-12 * c_alpha1 * s_alpha2 * s_alpha3) -
              3.9122157628652488E-12 * c_alpha2 * s_alpha1 * s_alpha3) +
             1.9561078814326244E-12 * c_alpha3 * s_alpha1 * s_alpha2) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  tmp[11] = (6.770279408084899E-6 * c_alpha1 * s_alpha3 - 6.770279408084899E-6 *
             c_alpha3 * s_alpha1) * (Mixer_Kq * s_alpha2 + 6.770279408084899E-6 *
    c_alpha2) / (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 *
    c_alpha2 * s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 *
    c_alpha4 * s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 *
    c_alpha3 * s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 *
    c_alpha4 * s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 *
    c_alpha2 * c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 *
    c_alpha2 * c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
    c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 * c_alpha2 *
    c_alpha3 * c_alpha4 * s_alpha1) - 5.2973587638623491E-17 * c_alpha1 *
    c_alpha2 * c_alpha3 * c_alpha4) - 1.3243396909655873E-17 * c_alpha1 *
    c_alpha2 * s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
    c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 * c_alpha1 *
    c_alpha4 * s_alpha2 * s_alpha3) - 1.3243396909655873E-17 * c_alpha2 *
    c_alpha3 * s_alpha1 * s_alpha4) + 2.6486793819311745E-17 * c_alpha2 *
    c_alpha4 * s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
    c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 * c_alpha1 *
    c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18 * c_alpha1 *
                        c_alpha2 * c_alpha4 * s_alpha3) - 1.1303397727525068E-18
                       * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
                      1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 *
                      s_alpha1) - 5.651698863762534E-19 * c_alpha1 * s_alpha2 *
                     s_alpha3 * s_alpha4) + 5.651698863762534E-19 * c_alpha2 *
                    s_alpha1 * s_alpha3 * s_alpha4) - 5.651698863762534E-19 *
                   c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
                  5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 *
                  s_alpha3) * 2.0);
  tmp[15] = -(((Mixer_Kq * c_alpha1 * s_alpha3 + Mixer_Kq * c_alpha3 * s_alpha1)
               - 1.3540558816169798E-5 * c_alpha1 * c_alpha3) * (Mixer_Kq *
    s_alpha2 + 6.770279408084899E-6 * c_alpha2)) /
    (((((((((((((((((((((((2.4118963030826135E-20 * c_alpha1 * c_alpha2 *
    s_alpha3 * s_alpha4 + 2.4118963030826135E-20 * c_alpha1 * c_alpha4 *
    s_alpha2 * s_alpha3) + 2.4118963030826135E-20 * c_alpha2 * c_alpha3 *
    s_alpha1 * s_alpha4) + 2.4118963030826135E-20 * c_alpha3 * c_alpha4 *
    s_alpha1 * s_alpha2) + 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
    c_alpha3 * s_alpha4) - 3.1032715283404387E-16 * c_alpha1 * c_alpha2 *
                       c_alpha4 * s_alpha3) + 3.1032715283404387E-16 * c_alpha1 *
                      c_alpha3 * c_alpha4 * s_alpha2) - 3.1032715283404387E-16 *
                     c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
                    5.2973587638623491E-17 * c_alpha1 * c_alpha2 * c_alpha3 *
                    c_alpha4) - 1.3243396909655873E-17 * c_alpha1 * c_alpha2 *
                   s_alpha3 * s_alpha4) + 2.6486793819311745E-17 * c_alpha1 *
                  c_alpha3 * s_alpha2 * s_alpha4) - 1.3243396909655873E-17 *
                 c_alpha1 * c_alpha4 * s_alpha2 * s_alpha3) -
                1.3243396909655873E-17 * c_alpha2 * c_alpha3 * s_alpha1 *
                s_alpha4) + 2.6486793819311745E-17 * c_alpha2 * c_alpha4 *
               s_alpha1 * s_alpha3) - 1.3243396909655873E-17 * c_alpha3 *
              c_alpha4 * s_alpha1 * s_alpha2) - 1.1303397727525068E-18 *
             c_alpha1 * c_alpha2 * c_alpha3 * s_alpha4) + 1.1303397727525068E-18
            * c_alpha1 * c_alpha2 * c_alpha4 * s_alpha3) -
           1.1303397727525068E-18 * c_alpha1 * c_alpha3 * c_alpha4 * s_alpha2) +
          1.1303397727525068E-18 * c_alpha2 * c_alpha3 * c_alpha4 * s_alpha1) -
         5.651698863762534E-19 * c_alpha1 * s_alpha2 * s_alpha3 * s_alpha4) +
        5.651698863762534E-19 * c_alpha2 * s_alpha1 * s_alpha3 * s_alpha4) -
       5.651698863762534E-19 * c_alpha3 * s_alpha1 * s_alpha2 * s_alpha4) +
      5.651698863762534E-19 * c_alpha4 * s_alpha1 * s_alpha2 * s_alpha3) * 2.0);
  for (i = 0; i < 4; i++) {
    c_alpha1 = tmp[i + 12] * Mixer_U.N + (tmp[i + 8] * Mixer_U.M + (tmp[i + 4] *
      Mixer_U.L + tmp[i] * Mixer_U.T));
    tmp_0[i] = c_alpha1;
  }

  /* Outport: '<Root>/th1' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.th1 = tmp_0[0];

  /* Outport: '<Root>/th2' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.th2 = tmp_0[1];

  /* Outport: '<Root>/th3' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.th3 = tmp_0[2];

  /* Outport: '<Root>/th4 ' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.th4 = tmp_0[3];

  /* Outport: '<Root>/alpha1' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.alpha1 = alpha_1;

  /* Outport: '<Root>/alpha2' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.alpha2 = -x;

  /* Outport: '<Root>/alpha3' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.alpha3 = -alpha_1;

  /* Outport: '<Root>/alpha4' incorporates:
   *  MATLAB Function: '<Root>/Inverted NONLINEAR mixer matrix'
   */
  Mixer_Y.alpha4 = -alpha_2;
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
