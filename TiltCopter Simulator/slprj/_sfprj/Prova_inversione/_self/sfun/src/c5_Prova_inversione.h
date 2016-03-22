#ifndef __c5_Prova_inversione_h__
#define __c5_Prova_inversione_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc5_Prova_inversioneInstanceStruct
#define typedef_SFc5_Prova_inversioneInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_isStable;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_Prova_inversione;
  real_T c5_Kt;
  real_T c5_Kq;
  real_T c5_b;
  real_T *c5_Fx;
  real_T *c5_Fy;
  real_T *c5_T;
  real_T *c5_L;
  real_T *c5_M;
  real_T *c5_N;
  real_T *c5_alpha_1;
  real_T *c5_omega_hover;
  real_T *c5_alpha_2;
  real_T *c5_omega_1;
  real_T *c5_omega_2;
  real_T *c5_omega_3;
  real_T *c5_omega_4;
} SFc5_Prova_inversioneInstanceStruct;

#endif                                 /*typedef_SFc5_Prova_inversioneInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_Prova_inversione_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c5_Prova_inversione_get_check_sum(mxArray *plhs[]);
extern void c5_Prova_inversione_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
