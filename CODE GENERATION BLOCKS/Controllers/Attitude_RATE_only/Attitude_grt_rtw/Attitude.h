/*
 * Attitude.h
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

#ifndef RTW_HEADER_Attitude_h_
#define RTW_HEADER_Attitude_h_
#include <string.h>
#ifndef Attitude_COMMON_INCLUDES_
# define Attitude_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Attitude_COMMON_INCLUDES_ */

#include "Attitude_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->ModelData.periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->ModelData.periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->ModelData.periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->ModelData.periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T FilterCoefficient;            /* '<S2>/Filter Coefficient' */
  real_T FilterCoefficient_b;          /* '<S3>/Filter Coefficient' */
  real_T FilterCoefficient_o;          /* '<S4>/Filter Coefficient' */
  real_T SumI1;                        /* '<S2>/SumI1' */
  real_T SumI1_e;                      /* '<S3>/SumI1' */
  real_T SumI1_k;                      /* '<S4>/SumI1' */
} B_Attitude_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
  real_T Filter_CSTATE;                /* '<S2>/Filter' */
  real_T Integrator_CSTATE_f;          /* '<S3>/Integrator' */
  real_T Filter_CSTATE_e;              /* '<S3>/Filter' */
  real_T Integrator_CSTATE_h;          /* '<S4>/Integrator' */
  real_T Filter_CSTATE_g;              /* '<S4>/Filter' */
} X_Attitude_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
  real_T Filter_CSTATE;                /* '<S2>/Filter' */
  real_T Integrator_CSTATE_f;          /* '<S3>/Integrator' */
  real_T Filter_CSTATE_e;              /* '<S3>/Filter' */
  real_T Integrator_CSTATE_h;          /* '<S4>/Integrator' */
  real_T Filter_CSTATE_g;              /* '<S4>/Filter' */
} XDot_Attitude_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S2>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S2>/Filter' */
  boolean_T Integrator_CSTATE_f;       /* '<S3>/Integrator' */
  boolean_T Filter_CSTATE_e;           /* '<S3>/Filter' */
  boolean_T Integrator_CSTATE_h;       /* '<S4>/Integrator' */
  boolean_T Filter_CSTATE_g;           /* '<S4>/Filter' */
} XDis_Attitude_T;

#ifndef ODE2_INTG
#define ODE2_INTG

/* ODE2 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[2];                        /* derivatives */
} ODE2_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T Stick[4];                     /* '<Root>/Stick' */
  real_T IMU_Attitude[3];              /* '<Root>/IMU_Attitude' */
  real_T IMU_Rates[3];                 /* '<Root>/IMU_Rates' */
  real_T Selector;                     /* '<Root>/Selector' */
} ExtU_Attitude_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Moments[3];                   /* '<Root>/Moments' */
} ExtY_Attitude_T;

/* Parameters (auto storage) */
struct P_Attitude_T_ {
  real_T Kbp;                          /* Variable: Kbp
                                        * Referenced by: '<S2>/Kb'
                                        */
  real_T Kbq;                          /* Variable: Kbq
                                        * Referenced by: '<S3>/Kb'
                                        */
  real_T Kbr;                          /* Variable: Kbr
                                        * Referenced by: '<S4>/Kb'
                                        */
  real_T Kdp;                          /* Variable: Kdp
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
  real_T Kdq;                          /* Variable: Kdq
                                        * Referenced by: '<S3>/Derivative Gain'
                                        */
  real_T Kdr;                          /* Variable: Kdr
                                        * Referenced by: '<S4>/Derivative Gain'
                                        */
  real_T Kip;                          /* Variable: Kip
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
  real_T Kiq;                          /* Variable: Kiq
                                        * Referenced by: '<S3>/Integral Gain'
                                        */
  real_T Kir;                          /* Variable: Kir
                                        * Referenced by: '<S4>/Integral Gain'
                                        */
  real_T Kpp;                          /* Variable: Kpp
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */
  real_T Kpq;                          /* Variable: Kpq
                                        * Referenced by: '<S3>/Proportional Gain'
                                        */
  real_T Kpr;                          /* Variable: Kpr
                                        * Referenced by: '<S4>/Proportional Gain'
                                        */
  real_T N;                            /* Variable: N
                                        * Referenced by:
                                        *   '<S2>/Filter Coefficient'
                                        *   '<S3>/Filter Coefficient'
                                        *   '<S4>/Filter Coefficient'
                                        */
  real_T satp;                         /* Variable: satp
                                        * Referenced by: '<S2>/Saturate'
                                        */
  real_T satq;                         /* Variable: satq
                                        * Referenced by: '<S3>/Saturate'
                                        */
  real_T satr;                         /* Variable: satr
                                        * Referenced by: '<S4>/Saturate'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -1
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -1
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real_T Integrator_IC_l;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T Filter_IC_f;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S3>/Filter'
                                        */
  real_T Saturation2_UpperSat;         /* Expression: 1
                                        * Referenced by: '<S1>/Saturation2'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: -1
                                        * Referenced by: '<S1>/Saturation2'
                                        */
  real_T Integrator_IC_k;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T Filter_IC_a;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S4>/Filter'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Attitude_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_Attitude_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[6];
    real_T odeF[2][6];
    ODE2_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

/* Class declaration for model Attitude */
class AttitudeModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_Attitude_T Attitude_U;

  /* External outputs */
  ExtY_Attitude_T Attitude_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  AttitudeModelClass();

  /* Destructor */
  ~AttitudeModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Attitude_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_Attitude_T Attitude_P;

  /* Block signals */
  B_Attitude_T Attitude_B;
  X_Attitude_T Attitude_X;             /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_Attitude_T Attitude_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Attitude_derivatives();
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Attitude'
 * '<S1>'   : 'Attitude/Attitude Controller'
 * '<S2>'   : 'Attitude/Attitude Controller/PID p'
 * '<S3>'   : 'Attitude/Attitude Controller/PID q'
 * '<S4>'   : 'Attitude/Attitude Controller/PID r'
 */
#endif                                 /* RTW_HEADER_Attitude_h_ */
