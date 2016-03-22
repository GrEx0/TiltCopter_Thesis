/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Prova_inversione_sfun.h"
#include "c5_Prova_inversione.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Prova_inversione_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_const_Kt                    (2.461919784758145E-5)
#define c5_const_Kq                    (2.8892572426134866E-7)
#define c5_const_b                     (0.275)
#define c5_b_Kt                        (2.461919784758145E-5)
#define c5_b_Kq                        (2.8892572426134866E-7)
#define c5_b_b                         (0.275)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[23] = { "alpha_3", "alpha_4", "K_mix",
  "Omega_result", "y", "Kt", "Kq", "b", "nargin", "nargout", "Fx", "Fy", "T",
  "L", "M", "N", "omega_hover", "alpha_1", "alpha_2", "omega_1", "omega_2",
  "omega_3", "omega_4" };

/* Function Declarations */
static void initialize_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void initialize_params_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void enable_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void disable_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void c5_update_debugger_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void set_sim_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance, const mxArray *c5_st);
static void finalize_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void sf_gateway_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void mdl_start_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void initSimStructsc5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_b_omega_4, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_c_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[8]);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_d_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[4]);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_e_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[16]);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static real_T c5_mpower(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_a);
static void c5_eml_scalar_eg(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void c5_dimagree(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static real_T c5_rdivide(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_x, real_T c5_y);
static void c5_eml_error(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void c5_inv(SFc5_Prova_inversioneInstanceStruct *chartInstance, real_T
                   c5_x[16], real_T c5_y[16]);
static void c5_realmin(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void c5_eps(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void c5_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void c5_eml_matlab_zgetrf(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, real_T c5_A[16], real_T c5_b_A[16], int32_T c5_ipiv[4],
  int32_T *c5_info);
static int32_T c5_eml_ixamax(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_n, real_T c5_x[16], int32_T c5_ix0);
static void c5_check_forloop_overflow_error(SFc5_Prova_inversioneInstanceStruct *
  chartInstance, boolean_T c5_overflow);
static void c5_b_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void c5_eml_xgeru(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_m, int32_T c5_n, real_T c5_alpha1, int32_T c5_ix0, int32_T c5_iy0,
  real_T c5_A[16], int32_T c5_ia0, real_T c5_b_A[16]);
static void c5_eml_ipiv2perm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_ipiv[4], int32_T c5_perm[4]);
static void c5_eml_xtrsm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[16], real_T c5_b_B[16]);
static void c5_c_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static real_T c5_norm(SFc5_Prova_inversioneInstanceStruct *chartInstance, real_T
                      c5_x[16]);
static void c5_eml_warning(SFc5_Prova_inversioneInstanceStruct *chartInstance);
static void c5_b_eml_warning(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  char_T c5_varargin_2[14]);
static void c5_b_eml_scalar_eg(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void c5_eml_xgemm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[4], real_T c5_C[4], real_T c5_b_C[4]);
static void c5_f_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_sprintf, const char_T *c5_identifier, char_T
  c5_y[14]);
static void c5_g_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  char_T c5_y[14]);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_h_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_i_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_Prova_inversione, const
  char_T *c5_identifier);
static uint8_T c5_j_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_eml_matlab_zgetrf(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, real_T c5_A[16], int32_T c5_ipiv[4], int32_T *c5_info);
static void c5_b_eml_xgeru(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_m, int32_T c5_n, real_T c5_alpha1, int32_T c5_ix0, int32_T c5_iy0,
  real_T c5_A[16], int32_T c5_ia0);
static void c5_b_eml_xtrsm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[16]);
static void c5_b_eml_xgemm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[4], real_T c5_C[4]);
static void init_dsm_address_info(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc5_Prova_inversioneInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc5_Prova_inversione(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_is_active_c5_Prova_inversione = 0U;
}

static void initialize_params_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  real_T c5_d0;
  real_T c5_d1;
  real_T c5_d2;
  sf_mex_import_named("Kt", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c5_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_Kt = c5_d0;
  sf_mex_import_named("Kq", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c5_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_Kq = c5_d1;
  sf_mex_import_named("b", sf_mex_get_sfun_param(chartInstance->S, 2, 0), &c5_d2,
                      0, 0, 0U, 0, 0U, 0);
  chartInstance->c5_b = c5_d2;
}

static void enable_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_c_hoistedGlobal;
  real_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_d_hoistedGlobal;
  real_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  real_T c5_e_hoistedGlobal;
  real_T c5_e_u;
  const mxArray *c5_f_y = NULL;
  real_T c5_f_hoistedGlobal;
  real_T c5_f_u;
  const mxArray *c5_g_y = NULL;
  uint8_T c5_g_hoistedGlobal;
  uint8_T c5_g_u;
  const mxArray *c5_h_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(7, 1), false);
  c5_hoistedGlobal = *chartInstance->c5_alpha_1;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *chartInstance->c5_alpha_2;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = *chartInstance->c5_omega_1;
  c5_c_u = c5_c_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = *chartInstance->c5_omega_2;
  c5_d_u = c5_d_hoistedGlobal;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = *chartInstance->c5_omega_3;
  c5_e_u = c5_e_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 4, c5_f_y);
  c5_f_hoistedGlobal = *chartInstance->c5_omega_4;
  c5_f_u = c5_f_hoistedGlobal;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_g_hoistedGlobal = chartInstance->c5_is_active_c5_Prova_inversione;
  c5_g_u = c5_g_hoistedGlobal;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_alpha_1 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("alpha_1", c5_u, 0)), "alpha_1");
  *chartInstance->c5_alpha_2 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("alpha_2", c5_u, 1)), "alpha_2");
  *chartInstance->c5_omega_1 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("omega_1", c5_u, 2)), "omega_1");
  *chartInstance->c5_omega_2 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("omega_2", c5_u, 3)), "omega_2");
  *chartInstance->c5_omega_3 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("omega_3", c5_u, 4)), "omega_3");
  *chartInstance->c5_omega_4 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("omega_4", c5_u, 5)), "omega_4");
  chartInstance->c5_is_active_c5_Prova_inversione = c5_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c5_Prova_inversione",
       c5_u, 6)), "is_active_c5_Prova_inversione");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_Prova_inversione(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  real_T c5_c_hoistedGlobal;
  real_T c5_d_hoistedGlobal;
  real_T c5_e_hoistedGlobal;
  real_T c5_f_hoistedGlobal;
  real_T c5_g_hoistedGlobal;
  real_T c5_b_Fx;
  real_T c5_b_Fy;
  real_T c5_b_T;
  real_T c5_b_L;
  real_T c5_b_M;
  real_T c5_b_N;
  real_T c5_b_omega_hover;
  uint32_T c5_debug_family_var_map[23];
  real_T c5_alpha_3;
  real_T c5_alpha_4;
  real_T c5_K_mix[16];
  real_T c5_Omega_result[4];
  real_T c5_y[8];
  real_T c5_c_Kt;
  real_T c5_c_Kq;
  real_T c5_c_b;
  real_T c5_nargin = 10.0;
  real_T c5_nargout = 6.0;
  real_T c5_b_alpha_1;
  real_T c5_b_alpha_2;
  real_T c5_b_omega_1;
  real_T c5_b_omega_2;
  real_T c5_b_omega_3;
  real_T c5_b_omega_4;
  real_T c5_A;
  real_T c5_B;
  real_T c5_b_y;
  real_T c5_x;
  real_T c5_b_x;
  real_T c5_b_A;
  real_T c5_b_B;
  real_T c5_c_y;
  real_T c5_c_x;
  real_T c5_d_x;
  real_T c5_e_x;
  real_T c5_f_x;
  real_T c5_g_x;
  real_T c5_h_x;
  real_T c5_i_x;
  real_T c5_j_x;
  real_T c5_k_x;
  real_T c5_l_x;
  real_T c5_m_x;
  real_T c5_n_x;
  real_T c5_o_x;
  real_T c5_p_x;
  real_T c5_q_x;
  real_T c5_r_x;
  real_T c5_s_x;
  real_T c5_t_x;
  real_T c5_u_x;
  real_T c5_v_x;
  real_T c5_w_x;
  real_T c5_x_x;
  real_T c5_y_x;
  real_T c5_ab_x;
  real_T c5_bb_x;
  real_T c5_cb_x;
  real_T c5_db_x;
  real_T c5_eb_x;
  real_T c5_fb_x;
  real_T c5_gb_x;
  real_T c5_hb_x;
  real_T c5_ib_x;
  real_T c5_jb_x;
  real_T c5_kb_x;
  real_T c5_lb_x;
  real_T c5_mb_x;
  real_T c5_nb_x;
  real_T c5_ob_x;
  real_T c5_pb_x;
  real_T c5_qb_x;
  real_T c5_rb_x;
  real_T c5_sb_x;
  int32_T c5_i0;
  real_T c5_u[16];
  const mxArray *c5_d_y = NULL;
  int32_T c5_i1;
  real_T c5_b_K_mix[16];
  real_T c5_d_b[4];
  int32_T c5_i2;
  int32_T c5_i3;
  real_T c5_dv0[4];
  int32_T c5_i4;
  real_T c5_b_u[16];
  int32_T c5_i5;
  real_T c5_e_b[4];
  int32_T c5_i6;
  int32_T c5_i7;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_b, 15U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_Kq, 13U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_Kt, 14U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_omega_hover, 6U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_N, 5U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_M, 4U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_L, 3U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_T, 2U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_Fy, 1U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_Fx, 0U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *chartInstance->c5_Fx;
  c5_b_hoistedGlobal = *chartInstance->c5_Fy;
  c5_c_hoistedGlobal = *chartInstance->c5_T;
  c5_d_hoistedGlobal = *chartInstance->c5_L;
  c5_e_hoistedGlobal = *chartInstance->c5_M;
  c5_f_hoistedGlobal = *chartInstance->c5_N;
  c5_g_hoistedGlobal = *chartInstance->c5_omega_hover;
  c5_b_Fx = c5_hoistedGlobal;
  c5_b_Fy = c5_b_hoistedGlobal;
  c5_b_T = c5_c_hoistedGlobal;
  c5_b_L = c5_d_hoistedGlobal;
  c5_b_M = c5_e_hoistedGlobal;
  c5_b_N = c5_f_hoistedGlobal;
  c5_b_omega_hover = c5_g_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_3, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_4, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_K_mix, 2U, c5_d_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_Omega_result, 3U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_y, 4U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_Kt, 5U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_Kq, 6U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_c_b, 7U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 8U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 9U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_Fx, 10U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_Fy, 11U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_T, 12U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_L, 13U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_M, 14U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_N, 15U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_b_omega_hover, 16U, c5_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_alpha_1, 17U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_alpha_2, 18U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_omega_1, 19U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_omega_2, 20U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_omega_3, 21U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_omega_4, 22U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  c5_c_Kt = c5_b_Kt;
  c5_c_Kq = c5_b_Kq;
  c5_c_b = c5_b_b;
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  c5_b_omega_1 = c5_b_omega_hover;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  c5_b_omega_2 = c5_b_omega_hover;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 6);
  c5_b_omega_3 = c5_b_omega_hover;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  c5_b_omega_4 = c5_b_omega_hover;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 11);
  c5_A = c5_b_Fx;
  c5_B = c5_b_Kt * (c5_mpower(chartInstance, c5_b_omega_2) + c5_mpower
                    (chartInstance, c5_b_omega_4));
  c5_b_y = c5_rdivide(chartInstance, c5_A, c5_B);
  c5_x = c5_b_y;
  c5_b_x = c5_x;
  guard2 = false;
  if (c5_b_x < -1.0) {
    guard2 = true;
  } else {
    if (1.0 < c5_b_x) {
      guard2 = true;
    }
  }

  if (guard2 == true) {
    c5_eml_error(chartInstance);
  }

  c5_b_x = muDoubleScalarAsin(c5_b_x);
  c5_b_alpha_2 = -c5_b_x;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
  c5_b_A = c5_b_Fy;
  c5_b_B = c5_b_Kt * (c5_mpower(chartInstance, c5_b_omega_1) + c5_mpower
                      (chartInstance, c5_b_omega_3));
  c5_c_y = c5_rdivide(chartInstance, c5_b_A, c5_b_B);
  c5_c_x = c5_c_y;
  c5_b_alpha_1 = c5_c_x;
  guard1 = false;
  if (c5_b_alpha_1 < -1.0) {
    guard1 = true;
  } else {
    if (1.0 < c5_b_alpha_1) {
      guard1 = true;
    }
  }

  if (guard1 == true) {
    c5_eml_error(chartInstance);
  }

  c5_d_x = c5_b_alpha_1;
  c5_b_alpha_1 = c5_d_x;
  c5_b_alpha_1 = muDoubleScalarAsin(c5_b_alpha_1);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
  c5_alpha_3 = -c5_b_alpha_1;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
  c5_alpha_4 = -c5_b_alpha_2;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 19);
  c5_e_x = c5_b_alpha_1;
  c5_f_x = c5_e_x;
  c5_f_x = muDoubleScalarCos(c5_f_x);
  c5_g_x = c5_b_alpha_2;
  c5_h_x = c5_g_x;
  c5_h_x = muDoubleScalarCos(c5_h_x);
  c5_i_x = c5_alpha_3;
  c5_j_x = c5_i_x;
  c5_j_x = muDoubleScalarCos(c5_j_x);
  c5_k_x = c5_alpha_4;
  c5_l_x = c5_k_x;
  c5_l_x = muDoubleScalarCos(c5_l_x);
  c5_m_x = c5_b_alpha_2;
  c5_n_x = c5_m_x;
  c5_n_x = muDoubleScalarSin(c5_n_x);
  c5_o_x = c5_b_alpha_2;
  c5_p_x = c5_o_x;
  c5_p_x = muDoubleScalarCos(c5_p_x);
  c5_q_x = c5_alpha_4;
  c5_r_x = c5_q_x;
  c5_r_x = muDoubleScalarSin(c5_r_x);
  c5_s_x = c5_alpha_4;
  c5_t_x = c5_s_x;
  c5_t_x = muDoubleScalarCos(c5_t_x);
  c5_u_x = c5_b_alpha_1;
  c5_v_x = c5_u_x;
  c5_v_x = muDoubleScalarCos(c5_v_x);
  c5_w_x = c5_b_alpha_1;
  c5_x_x = c5_w_x;
  c5_x_x = muDoubleScalarSin(c5_x_x);
  c5_y_x = c5_alpha_3;
  c5_ab_x = c5_y_x;
  c5_ab_x = muDoubleScalarSin(c5_ab_x);
  c5_bb_x = c5_alpha_3;
  c5_cb_x = c5_bb_x;
  c5_cb_x = muDoubleScalarCos(c5_cb_x);
  c5_db_x = c5_b_alpha_1;
  c5_eb_x = c5_db_x;
  c5_eb_x = muDoubleScalarCos(c5_eb_x);
  c5_fb_x = c5_b_alpha_1;
  c5_gb_x = c5_fb_x;
  c5_gb_x = muDoubleScalarSin(c5_gb_x);
  c5_hb_x = c5_b_alpha_2;
  c5_ib_x = c5_hb_x;
  c5_ib_x = muDoubleScalarSin(c5_ib_x);
  c5_jb_x = c5_b_alpha_2;
  c5_kb_x = c5_jb_x;
  c5_kb_x = muDoubleScalarCos(c5_kb_x);
  c5_lb_x = c5_alpha_3;
  c5_mb_x = c5_lb_x;
  c5_mb_x = muDoubleScalarCos(c5_mb_x);
  c5_nb_x = c5_alpha_3;
  c5_ob_x = c5_nb_x;
  c5_ob_x = muDoubleScalarSin(c5_ob_x);
  c5_pb_x = c5_alpha_4;
  c5_qb_x = c5_pb_x;
  c5_qb_x = muDoubleScalarSin(c5_qb_x);
  c5_rb_x = c5_alpha_4;
  c5_sb_x = c5_rb_x;
  c5_sb_x = muDoubleScalarCos(c5_sb_x);
  c5_K_mix[0] = -2.461919784758145E-5 * c5_f_x;
  c5_K_mix[4] = -2.461919784758145E-5 * c5_h_x;
  c5_K_mix[8] = -2.461919784758145E-5 * c5_j_x;
  c5_K_mix[12] = -2.461919784758145E-5 * c5_l_x;
  c5_K_mix[1] = 0.0;
  c5_K_mix[5] = -2.8892572426134866E-7 * c5_n_x - 6.770279408084899E-6 * c5_p_x;
  c5_K_mix[9] = 0.0;
  c5_K_mix[13] = c5_b_Kq * c5_r_x + 6.770279408084899E-6 * c5_t_x;
  c5_K_mix[2] = 6.770279408084899E-6 * c5_v_x - c5_b_Kq * c5_x_x;
  c5_K_mix[6] = 0.0;
  c5_K_mix[10] = c5_b_Kq * c5_ab_x - 6.770279408084899E-6 * c5_cb_x;
  c5_K_mix[14] = 0.0;
  c5_K_mix[3] = c5_b_Kq * c5_eb_x + 6.770279408084899E-6 * c5_gb_x;
  c5_K_mix[7] = 6.770279408084899E-6 * c5_ib_x - c5_b_Kq * c5_kb_x;
  c5_K_mix[11] = c5_b_Kq * c5_mb_x + 6.770279408084899E-6 * c5_ob_x;
  c5_K_mix[15] = 6.770279408084899E-6 * c5_qb_x - c5_b_Kq * c5_sb_x;
  sf_mex_printf("%s =\\n", "K_mix");
  for (c5_i0 = 0; c5_i0 < 16; c5_i0++) {
    c5_u[c5_i0] = c5_K_mix[c5_i0];
  }

  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c5_d_y);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
  for (c5_i1 = 0; c5_i1 < 16; c5_i1++) {
    c5_b_K_mix[c5_i1] = c5_K_mix[c5_i1];
  }

  c5_inv(chartInstance, c5_b_K_mix, c5_u);
  c5_d_b[0] = c5_b_T;
  c5_d_b[1] = c5_b_L;
  c5_d_b[2] = c5_b_M;
  c5_d_b[3] = c5_b_N;
  c5_b_eml_scalar_eg(chartInstance);
  c5_b_eml_scalar_eg(chartInstance);
  for (c5_i2 = 0; c5_i2 < 4; c5_i2++) {
    c5_Omega_result[c5_i2] = 0.0;
  }

  for (c5_i3 = 0; c5_i3 < 4; c5_i3++) {
    c5_dv0[c5_i3] = 0.0;
  }

  for (c5_i4 = 0; c5_i4 < 16; c5_i4++) {
    c5_b_u[c5_i4] = c5_u[c5_i4];
  }

  for (c5_i5 = 0; c5_i5 < 4; c5_i5++) {
    c5_e_b[c5_i5] = c5_d_b[c5_i5];
  }

  c5_b_eml_xgemm(chartInstance, c5_b_u, c5_e_b, c5_dv0);
  for (c5_i6 = 0; c5_i6 < 4; c5_i6++) {
    c5_Omega_result[c5_i6] = c5_dv0[c5_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  c5_y[0] = c5_b_alpha_1;
  c5_y[1] = c5_b_alpha_2;
  c5_y[2] = c5_alpha_3;
  c5_y[3] = c5_alpha_4;
  for (c5_i7 = 0; c5_i7 < 4; c5_i7++) {
    c5_y[c5_i7 + 4] = c5_Omega_result[c5_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -26);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c5_alpha_1 = c5_b_alpha_1;
  *chartInstance->c5_alpha_2 = c5_b_alpha_2;
  *chartInstance->c5_omega_1 = c5_b_omega_1;
  *chartInstance->c5_omega_2 = c5_b_omega_2;
  *chartInstance->c5_omega_3 = c5_b_omega_3;
  *chartInstance->c5_omega_4 = c5_b_omega_4;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Prova_inversioneMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_alpha_1, 7U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_alpha_2, 8U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_omega_1, 9U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_omega_2, 10U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_omega_3, 11U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_omega_4, 12U, 1U, 0U,
                        chartInstance->c5_sfEvent, false);
}

static void mdl_start_c5_Prova_inversione(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc5_Prova_inversione
  (SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_b_omega_4, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_omega_4),
    &c5_thisId);
  sf_mex_destroy(&c5_b_omega_4);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d3;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d3, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d3;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_omega_4;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_b_omega_4 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_omega_4),
    &c5_thisId);
  sf_mex_destroy(&c5_b_omega_4);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i8;
  real_T c5_u[8];
  const mxArray *c5_y = NULL;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i8 = 0; c5_i8 < 8; c5_i8++) {
    c5_u[c5_i8] = (*(real_T (*)[8])c5_inData)[c5_i8];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 8), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_c_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[8])
{
  real_T c5_dv1[8];
  int32_T c5_i9;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv1, 1, 0, 0U, 1, 0U, 1, 8);
  for (c5_i9 = 0; c5_i9 < 8; c5_i9++) {
    c5_y[c5_i9] = c5_dv1[c5_i9];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_y;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_b_y[8];
  int32_T c5_i10;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_y = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_y), &c5_thisId, c5_b_y);
  sf_mex_destroy(&c5_y);
  for (c5_i10 = 0; c5_i10 < 8; c5_i10++) {
    (*(real_T (*)[8])c5_outData)[c5_i10] = c5_b_y[c5_i10];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i11;
  real_T c5_u[4];
  const mxArray *c5_y = NULL;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i11 = 0; c5_i11 < 4; c5_i11++) {
    c5_u[c5_i11] = (*(real_T (*)[4])c5_inData)[c5_i11];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_d_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[4])
{
  real_T c5_dv2[4];
  int32_T c5_i12;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv2, 1, 0, 0U, 1, 0U, 1, 4);
  for (c5_i12 = 0; c5_i12 < 4; c5_i12++) {
    c5_y[c5_i12] = c5_dv2[c5_i12];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_Omega_result;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[4];
  int32_T c5_i13;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_Omega_result = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_Omega_result), &c5_thisId,
                        c5_y);
  sf_mex_destroy(&c5_Omega_result);
  for (c5_i13 = 0; c5_i13 < 4; c5_i13++) {
    (*(real_T (*)[4])c5_outData)[c5_i13] = c5_y[c5_i13];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i14;
  int32_T c5_i15;
  int32_T c5_i16;
  real_T c5_u[16];
  const mxArray *c5_y = NULL;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_i14 = 0;
  for (c5_i15 = 0; c5_i15 < 4; c5_i15++) {
    for (c5_i16 = 0; c5_i16 < 4; c5_i16++) {
      c5_u[c5_i16 + c5_i14] = (*(real_T (*)[16])c5_inData)[c5_i16 + c5_i14];
    }

    c5_i14 += 4;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_e_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[16])
{
  real_T c5_dv3[16];
  int32_T c5_i17;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv3, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c5_i17 = 0; c5_i17 < 16; c5_i17++) {
    c5_y[c5_i17] = c5_dv3[c5_i17];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_K_mix;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[16];
  int32_T c5_i18;
  int32_T c5_i19;
  int32_T c5_i20;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_K_mix = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_K_mix), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_K_mix);
  c5_i18 = 0;
  for (c5_i19 = 0; c5_i19 < 4; c5_i19++) {
    for (c5_i20 = 0; c5_i20 < 4; c5_i20++) {
      (*(real_T (*)[16])c5_outData)[c5_i20 + c5_i18] = c5_y[c5_i20 + c5_i18];
    }

    c5_i18 += 4;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_Prova_inversione_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static real_T c5_mpower(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_a)
{
  real_T c5_b_a;
  real_T c5_c_a;
  real_T c5_ak;
  real_T c5_d_a;
  c5_b_a = c5_a;
  c5_c_a = c5_b_a;
  c5_eml_scalar_eg(chartInstance);
  c5_dimagree(chartInstance);
  c5_ak = c5_c_a;
  c5_d_a = c5_ak;
  c5_eml_scalar_eg(chartInstance);
  return c5_d_a * c5_d_a;
}

static void c5_eml_scalar_eg(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_dimagree(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c5_rdivide(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_x, real_T c5_y)
{
  real_T c5_b_x;
  real_T c5_b_y;
  real_T c5_c_x;
  real_T c5_c_y;
  (void)chartInstance;
  c5_b_x = c5_x;
  c5_b_y = c5_y;
  c5_c_x = c5_b_x;
  c5_c_y = c5_b_y;
  return c5_c_x / c5_c_y;
}

static void c5_eml_error(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  const mxArray *c5_y = NULL;
  static char_T c5_u[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  const mxArray *c5_b_y = NULL;
  static char_T c5_b_u[4] = { 'a', 's', 'i', 'n' };

  (void)chartInstance;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c5_y, 14, c5_b_y));
}

static void c5_inv(SFc5_Prova_inversioneInstanceStruct *chartInstance, real_T
                   c5_x[16], real_T c5_y[16])
{
  int32_T c5_i21;
  real_T c5_b_x[16];
  int32_T c5_i22;
  int32_T c5_info;
  int32_T c5_ipiv[4];
  int32_T c5_i23;
  int32_T c5_b_ipiv[4];
  int32_T c5_p[4];
  int32_T c5_k;
  int32_T c5_b_k;
  int32_T c5_c;
  int32_T c5_c_k;
  int32_T c5_a;
  int32_T c5_b_a;
  boolean_T c5_overflow;
  int32_T c5_j;
  int32_T c5_b_j;
  int32_T c5_c_a;
  int32_T c5_d_a;
  int32_T c5_i24;
  int32_T c5_e_a;
  int32_T c5_f_a;
  boolean_T c5_b_overflow;
  int32_T c5_i;
  int32_T c5_b_i;
  int32_T c5_i25;
  real_T c5_c_x[16];
  int32_T c5_i26;
  real_T c5_d_x[16];
  real_T c5_n1x;
  int32_T c5_i27;
  real_T c5_b_y[16];
  real_T c5_n1xinv;
  real_T c5_rc;
  real_T c5_e_x;
  boolean_T c5_c_b;
  real_T c5_f_x;
  const mxArray *c5_c_y = NULL;
  static char_T c5_u[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  real_T c5_b_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_c_u;
  const mxArray *c5_e_y = NULL;
  real_T c5_d_u;
  const mxArray *c5_f_y = NULL;
  char_T c5_str[14];
  int32_T c5_i28;
  char_T c5_b_str[14];
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  for (c5_i21 = 0; c5_i21 < 16; c5_i21++) {
    c5_b_x[c5_i21] = c5_x[c5_i21];
  }

  for (c5_i22 = 0; c5_i22 < 16; c5_i22++) {
    c5_y[c5_i22] = 0.0;
  }

  c5_b_eml_matlab_zgetrf(chartInstance, c5_b_x, c5_ipiv, &c5_info);
  for (c5_i23 = 0; c5_i23 < 4; c5_i23++) {
    c5_b_ipiv[c5_i23] = c5_ipiv[c5_i23];
  }

  c5_eml_ipiv2perm(chartInstance, c5_b_ipiv, c5_p);
  c5_eml_switch_helper(chartInstance);
  for (c5_k = 1; c5_k < 5; c5_k++) {
    c5_b_k = c5_k;
    c5_c = c5_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c5_b_k), 1, 4, 1, 0) - 1];
    c5_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_b_k), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_c), 1, 4, 2, 0) - 1) <<
           2)) - 1] = 1.0;
    c5_c_k = c5_b_k;
    c5_a = c5_c_k;
    c5_b_a = c5_a;
    if (c5_b_a > 4) {
      c5_overflow = false;
    } else {
      c5_eml_switch_helper(chartInstance);
      c5_eml_switch_helper(chartInstance);
      c5_overflow = false;
    }

    if (c5_overflow) {
      c5_check_forloop_overflow_error(chartInstance, c5_overflow);
    }

    for (c5_j = c5_c_k; c5_j < 5; c5_j++) {
      c5_b_j = c5_j;
      if (c5_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c5_b_j), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_c), 1, 4, 2, 0) - 1) <<
            2)) - 1] != 0.0) {
        c5_c_a = c5_b_j;
        c5_d_a = c5_c_a + 1;
        c5_i24 = c5_d_a;
        c5_e_a = c5_i24;
        c5_f_a = c5_e_a;
        if (c5_f_a > 4) {
          c5_b_overflow = false;
        } else {
          c5_eml_switch_helper(chartInstance);
          c5_eml_switch_helper(chartInstance);
          c5_b_overflow = false;
        }

        if (c5_b_overflow) {
          c5_check_forloop_overflow_error(chartInstance, c5_b_overflow);
        }

        for (c5_i = c5_i24; c5_i < 5; c5_i++) {
          c5_b_i = c5_i;
          c5_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c5_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK(
                   "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_c), 1, 4, 2, 0)
                  - 1) << 2)) - 1] = c5_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_b_i), 1, 4, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_c), 1, 4, 2, 0) - 1) << 2)) - 1] - c5_y
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c5_b_j), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
                 (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_c), 1, 4, 2, 0) - 1)
               << 2)) - 1] * c5_b_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c5_b_i), 1, 4, 1, 0) +
            ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_b_j), 1, 4, 2, 0) - 1) << 2)) - 1];
        }
      }
    }
  }

  for (c5_i25 = 0; c5_i25 < 16; c5_i25++) {
    c5_c_x[c5_i25] = c5_b_x[c5_i25];
  }

  c5_b_eml_xtrsm(chartInstance, c5_c_x, c5_y);
  for (c5_i26 = 0; c5_i26 < 16; c5_i26++) {
    c5_d_x[c5_i26] = c5_x[c5_i26];
  }

  c5_n1x = c5_norm(chartInstance, c5_d_x);
  for (c5_i27 = 0; c5_i27 < 16; c5_i27++) {
    c5_b_y[c5_i27] = c5_y[c5_i27];
  }

  c5_n1xinv = c5_norm(chartInstance, c5_b_y);
  c5_rc = 1.0 / (c5_n1x * c5_n1xinv);
  guard1 = false;
  guard2 = false;
  if (c5_n1x == 0.0) {
    guard2 = true;
  } else if (c5_n1xinv == 0.0) {
    guard2 = true;
  } else if (c5_rc == 0.0) {
    guard1 = true;
  } else {
    c5_e_x = c5_rc;
    c5_c_b = muDoubleScalarIsNaN(c5_e_x);
    guard3 = false;
    if (c5_c_b) {
      guard3 = true;
    } else {
      c5_eps(chartInstance);
      if (c5_rc < 2.2204460492503131E-16) {
        guard3 = true;
      }
    }

    if (guard3 == true) {
      c5_f_x = c5_rc;
      c5_c_y = NULL;
      sf_mex_assign(&c5_c_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    false);
      c5_b_u = 14.0;
      c5_d_y = NULL;
      sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0),
                    false);
      c5_c_u = 6.0;
      c5_e_y = NULL;
      sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0),
                    false);
      c5_d_u = c5_f_x;
      c5_f_y = NULL;
      sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0),
                    false);
      c5_f_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                            (sfGlobalDebugInstanceStruct, "sprintf", 1U, 2U, 14,
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "sprintf", 1U, 3U, 14,
                          c5_c_y, 14, c5_d_y, 14, c5_e_y), 14, c5_f_y),
                            "sprintf", c5_str);
      for (c5_i28 = 0; c5_i28 < 14; c5_i28++) {
        c5_b_str[c5_i28] = c5_str[c5_i28];
      }

      c5_b_eml_warning(chartInstance, c5_b_str);
    }
  }

  if (guard2 == true) {
    guard1 = true;
  }

  if (guard1 == true) {
    c5_eml_warning(chartInstance);
  }
}

static void c5_realmin(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_eps(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_matlab_zgetrf(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, real_T c5_A[16], real_T c5_b_A[16], int32_T c5_ipiv[4],
  int32_T *c5_info)
{
  int32_T c5_i29;
  for (c5_i29 = 0; c5_i29 < 16; c5_i29++) {
    c5_b_A[c5_i29] = c5_A[c5_i29];
  }

  c5_b_eml_matlab_zgetrf(chartInstance, c5_b_A, c5_ipiv, c5_info);
}

static int32_T c5_eml_ixamax(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_n, real_T c5_x[16], int32_T c5_ix0)
{
  int32_T c5_idxmax;
  int32_T c5_b_n;
  int32_T c5_b_ix0;
  int32_T c5_c_n;
  int32_T c5_c_ix0;
  int32_T c5_ix;
  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_d_x;
  real_T c5_y;
  real_T c5_e_x;
  real_T c5_f_x;
  real_T c5_b_y;
  real_T c5_smax;
  int32_T c5_d_n;
  int32_T c5_c_b;
  int32_T c5_d_b;
  boolean_T c5_overflow;
  int32_T c5_k;
  int32_T c5_b_k;
  int32_T c5_a;
  real_T c5_g_x;
  real_T c5_h_x;
  real_T c5_i_x;
  real_T c5_c_y;
  real_T c5_j_x;
  real_T c5_k_x;
  real_T c5_d_y;
  real_T c5_s;
  c5_b_n = c5_n;
  c5_b_ix0 = c5_ix0;
  c5_c_n = c5_b_n;
  c5_c_ix0 = c5_b_ix0;
  if (c5_c_n < 1) {
    c5_idxmax = 0;
  } else {
    c5_idxmax = 1;
    if (c5_c_n > 1) {
      c5_ix = c5_c_ix0;
      c5_b_x = c5_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c5_ix), 1, 16, 1, 0) - 1];
      c5_c_x = c5_b_x;
      c5_d_x = c5_c_x;
      c5_y = muDoubleScalarAbs(c5_d_x);
      c5_e_x = 0.0;
      c5_f_x = c5_e_x;
      c5_b_y = muDoubleScalarAbs(c5_f_x);
      c5_smax = c5_y + c5_b_y;
      c5_d_n = c5_c_n;
      c5_c_b = c5_d_n;
      c5_d_b = c5_c_b;
      if (2 > c5_d_b) {
        c5_overflow = false;
      } else {
        c5_eml_switch_helper(chartInstance);
        c5_eml_switch_helper(chartInstance);
        c5_overflow = (c5_d_b > 2147483646);
      }

      if (c5_overflow) {
        c5_check_forloop_overflow_error(chartInstance, c5_overflow);
      }

      for (c5_k = 2; c5_k <= c5_d_n; c5_k++) {
        c5_b_k = c5_k;
        c5_a = c5_ix + 1;
        c5_ix = c5_a;
        c5_g_x = c5_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c5_ix), 1, 16, 1, 0) - 1];
        c5_h_x = c5_g_x;
        c5_i_x = c5_h_x;
        c5_c_y = muDoubleScalarAbs(c5_i_x);
        c5_j_x = 0.0;
        c5_k_x = c5_j_x;
        c5_d_y = muDoubleScalarAbs(c5_k_x);
        c5_s = c5_c_y + c5_d_y;
        if (c5_s > c5_smax) {
          c5_idxmax = c5_b_k;
          c5_smax = c5_s;
        }
      }
    }
  }

  return c5_idxmax;
}

static void c5_check_forloop_overflow_error(SFc5_Prova_inversioneInstanceStruct *
  chartInstance, boolean_T c5_overflow)
{
  const mxArray *c5_y = NULL;
  static char_T c5_u[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  const mxArray *c5_b_y = NULL;
  static char_T c5_b_u[5] = { 'i', 'n', 't', '3', '2' };

  (void)chartInstance;
  if (!c5_overflow) {
  } else {
    c5_y = NULL;
    sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c5_y, 14, c5_b_y));
  }
}

static void c5_b_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_xgeru(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_m, int32_T c5_n, real_T c5_alpha1, int32_T c5_ix0, int32_T c5_iy0,
  real_T c5_A[16], int32_T c5_ia0, real_T c5_b_A[16])
{
  int32_T c5_i30;
  for (c5_i30 = 0; c5_i30 < 16; c5_i30++) {
    c5_b_A[c5_i30] = c5_A[c5_i30];
  }

  c5_b_eml_xgeru(chartInstance, c5_m, c5_n, c5_alpha1, c5_ix0, c5_iy0, c5_b_A,
                 c5_ia0);
}

static void c5_eml_ipiv2perm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_ipiv[4], int32_T c5_perm[4])
{
  int32_T c5_i31;
  int32_T c5_k;
  real_T c5_b_k;
  int32_T c5_ipk;
  int32_T c5_a;
  real_T c5_c_b;
  int32_T c5_b_a;
  real_T c5_d_b;
  int32_T c5_idx;
  real_T c5_flt;
  boolean_T c5_p;
  int32_T c5_pipk;
  (void)chartInstance;
  for (c5_i31 = 0; c5_i31 < 4; c5_i31++) {
    c5_perm[c5_i31] = 1 + c5_i31;
  }

  for (c5_k = 0; c5_k < 3; c5_k++) {
    c5_b_k = 1.0 + (real_T)c5_k;
    c5_ipk = c5_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", c5_b_k), 1, 4, 1, 0) - 1];
    c5_a = c5_ipk;
    c5_c_b = c5_b_k;
    c5_b_a = c5_a;
    c5_d_b = c5_c_b;
    c5_idx = c5_b_a;
    c5_flt = c5_d_b;
    c5_p = ((real_T)c5_idx > c5_flt);
    if (c5_p) {
      c5_pipk = c5_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c5_ipk), 1, 4, 1, 0) - 1];
      c5_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c5_ipk), 1, 4, 1, 0) - 1] = c5_perm[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", c5_b_k), 1, 4, 1, 0) - 1];
      c5_perm[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c5_b_k), 1, 4, 1, 0) - 1] = c5_pipk;
    }
  }
}

static void c5_eml_xtrsm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[16], real_T c5_b_B[16])
{
  int32_T c5_i32;
  int32_T c5_i33;
  real_T c5_b_A[16];
  for (c5_i32 = 0; c5_i32 < 16; c5_i32++) {
    c5_b_B[c5_i32] = c5_B[c5_i32];
  }

  for (c5_i33 = 0; c5_i33 < 16; c5_i33++) {
    c5_b_A[c5_i33] = c5_A[c5_i33];
  }

  c5_b_eml_xtrsm(chartInstance, c5_b_A, c5_b_B);
}

static void c5_c_eml_switch_helper(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c5_norm(SFc5_Prova_inversioneInstanceStruct *chartInstance, real_T
                      c5_x[16])
{
  real_T c5_y;
  int32_T c5_j;
  real_T c5_b_j;
  real_T c5_s;
  int32_T c5_i;
  real_T c5_b_i;
  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_b_y;
  real_T c5_d_x;
  boolean_T c5_c_b;
  boolean_T exitg1;
  (void)chartInstance;
  c5_y = 0.0;
  c5_j = 0;
  exitg1 = false;
  while ((exitg1 == false) && (c5_j < 4)) {
    c5_b_j = 1.0 + (real_T)c5_j;
    c5_s = 0.0;
    for (c5_i = 0; c5_i < 4; c5_i++) {
      c5_b_i = 1.0 + (real_T)c5_i;
      c5_b_x = c5_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", c5_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c5_b_j), 1, 4, 2, 0) - 1) << 2)) - 1];
      c5_c_x = c5_b_x;
      c5_b_y = muDoubleScalarAbs(c5_c_x);
      c5_s += c5_b_y;
    }

    c5_d_x = c5_s;
    c5_c_b = muDoubleScalarIsNaN(c5_d_x);
    if (c5_c_b) {
      c5_y = rtNaN;
      exitg1 = true;
    } else {
      if (c5_s > c5_y) {
        c5_y = c5_s;
      }

      c5_j++;
    }
  }

  return c5_y;
}

static void c5_eml_warning(SFc5_Prova_inversioneInstanceStruct *chartInstance)
{
  const mxArray *c5_y = NULL;
  static char_T c5_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  (void)chartInstance;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_varargin_1, 10, 0U, 1U, 0U, 2, 1,
    27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c5_y));
}

static void c5_b_eml_warning(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  char_T c5_varargin_2[14])
{
  const mxArray *c5_y = NULL;
  static char_T c5_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  const mxArray *c5_b_y = NULL;
  (void)chartInstance;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_varargin_1, 10, 0U, 1U, 0U, 2, 1,
    33), false);
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_varargin_2, 10, 0U, 1U, 0U, 2, 1,
    14), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c5_y, 14, c5_b_y));
}

static void c5_b_eml_scalar_eg(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_xgemm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[4], real_T c5_C[4], real_T c5_b_C[4])
{
  int32_T c5_i34;
  int32_T c5_i35;
  real_T c5_b_A[16];
  int32_T c5_i36;
  real_T c5_b_B[4];
  for (c5_i34 = 0; c5_i34 < 4; c5_i34++) {
    c5_b_C[c5_i34] = c5_C[c5_i34];
  }

  for (c5_i35 = 0; c5_i35 < 16; c5_i35++) {
    c5_b_A[c5_i35] = c5_A[c5_i35];
  }

  for (c5_i36 = 0; c5_i36 < 4; c5_i36++) {
    c5_b_B[c5_i36] = c5_B[c5_i36];
  }

  c5_b_eml_xgemm(chartInstance, c5_b_A, c5_b_B, c5_b_C);
}

static void c5_f_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_sprintf, const char_T *c5_identifier, char_T
  c5_y[14])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_sprintf), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_sprintf);
}

static void c5_g_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  char_T c5_y[14])
{
  char_T c5_cv0[14];
  int32_T c5_i37;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_cv0, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c5_i37 = 0; c5_i37 < 14; c5_i37++) {
    c5_y[c5_i37] = c5_cv0[c5_i37];
  }

  sf_mex_destroy(&c5_u);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_h_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i38;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i38, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i38;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_i_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_Prova_inversione, const
  char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_Prova_inversione), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_Prova_inversione);
  return c5_y;
}

static uint8_T c5_j_emlrt_marshallIn(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_eml_matlab_zgetrf(SFc5_Prova_inversioneInstanceStruct
  *chartInstance, real_T c5_A[16], int32_T c5_ipiv[4], int32_T *c5_info)
{
  int32_T c5_i39;
  int32_T c5_j;
  int32_T c5_b_j;
  int32_T c5_a;
  int32_T c5_b_a;
  int32_T c5_jm1;
  int32_T c5_c_b;
  int32_T c5_d_b;
  int32_T c5_mmj;
  int32_T c5_c_a;
  int32_T c5_d_a;
  int32_T c5_c;
  int32_T c5_e_b;
  int32_T c5_f_b;
  int32_T c5_jj;
  int32_T c5_e_a;
  int32_T c5_f_a;
  int32_T c5_jp1j;
  int32_T c5_g_a;
  int32_T c5_h_a;
  int32_T c5_b_c;
  int32_T c5_i40;
  real_T c5_b_A[16];
  int32_T c5_i_a;
  int32_T c5_j_a;
  int32_T c5_jpiv_offset;
  int32_T c5_k_a;
  int32_T c5_g_b;
  int32_T c5_l_a;
  int32_T c5_h_b;
  int32_T c5_jpiv;
  int32_T c5_m_a;
  int32_T c5_i_b;
  int32_T c5_n_a;
  int32_T c5_j_b;
  int32_T c5_c_c;
  int32_T c5_k_b;
  int32_T c5_l_b;
  int32_T c5_jrow;
  int32_T c5_o_a;
  int32_T c5_m_b;
  int32_T c5_p_a;
  int32_T c5_n_b;
  int32_T c5_jprow;
  int32_T c5_ix0;
  int32_T c5_iy0;
  int32_T c5_b_ix0;
  int32_T c5_b_iy0;
  int32_T c5_c_ix0;
  int32_T c5_c_iy0;
  int32_T c5_ix;
  int32_T c5_iy;
  int32_T c5_k;
  real_T c5_temp;
  int32_T c5_q_a;
  int32_T c5_r_a;
  int32_T c5_b_jp1j;
  int32_T c5_s_a;
  int32_T c5_t_a;
  int32_T c5_d_c;
  int32_T c5_u_a;
  int32_T c5_o_b;
  int32_T c5_v_a;
  int32_T c5_p_b;
  int32_T c5_i41;
  int32_T c5_w_a;
  int32_T c5_q_b;
  int32_T c5_x_a;
  int32_T c5_r_b;
  boolean_T c5_overflow;
  int32_T c5_i;
  int32_T c5_b_i;
  real_T c5_x;
  real_T c5_y;
  real_T c5_b_x;
  real_T c5_b_y;
  real_T c5_z;
  int32_T c5_s_b;
  int32_T c5_t_b;
  int32_T c5_e_c;
  int32_T c5_y_a;
  int32_T c5_ab_a;
  int32_T c5_f_c;
  int32_T c5_bb_a;
  int32_T c5_cb_a;
  int32_T c5_g_c;
  c5_realmin(chartInstance);
  c5_eps(chartInstance);
  for (c5_i39 = 0; c5_i39 < 4; c5_i39++) {
    c5_ipiv[c5_i39] = 1 + c5_i39;
  }

  *c5_info = 0;
  c5_eml_switch_helper(chartInstance);
  for (c5_j = 1; c5_j < 4; c5_j++) {
    c5_b_j = c5_j;
    c5_a = c5_b_j;
    c5_b_a = c5_a - 1;
    c5_jm1 = c5_b_a;
    c5_c_b = c5_b_j;
    c5_d_b = c5_c_b;
    c5_mmj = 4 - c5_d_b;
    c5_c_a = c5_jm1;
    c5_d_a = c5_c_a;
    c5_c = c5_d_a * 5;
    c5_e_b = c5_c;
    c5_f_b = c5_e_b + 1;
    c5_jj = c5_f_b;
    c5_e_a = c5_jj;
    c5_f_a = c5_e_a + 1;
    c5_jp1j = c5_f_a;
    c5_g_a = c5_mmj;
    c5_h_a = c5_g_a;
    c5_b_c = c5_h_a;
    for (c5_i40 = 0; c5_i40 < 16; c5_i40++) {
      c5_b_A[c5_i40] = c5_A[c5_i40];
    }

    c5_i_a = c5_eml_ixamax(chartInstance, c5_b_c + 1, c5_b_A, c5_jj);
    c5_j_a = c5_i_a - 1;
    c5_jpiv_offset = c5_j_a;
    c5_k_a = c5_jj;
    c5_g_b = c5_jpiv_offset;
    c5_l_a = c5_k_a;
    c5_h_b = c5_g_b;
    c5_jpiv = c5_l_a + c5_h_b;
    if (c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c5_jpiv), 1, 16, 1, 0) - 1] != 0.0) {
      if (c5_jpiv_offset != 0) {
        c5_m_a = c5_b_j;
        c5_i_b = c5_jpiv_offset;
        c5_n_a = c5_m_a;
        c5_j_b = c5_i_b;
        c5_c_c = c5_n_a + c5_j_b;
        c5_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c5_b_j), 1, 4, 1, 0) - 1] = c5_c_c;
        c5_k_b = c5_jm1;
        c5_l_b = c5_k_b + 1;
        c5_jrow = c5_l_b;
        c5_o_a = c5_jrow;
        c5_m_b = c5_jpiv_offset;
        c5_p_a = c5_o_a;
        c5_n_b = c5_m_b;
        c5_jprow = c5_p_a + c5_n_b;
        c5_ix0 = c5_jrow;
        c5_iy0 = c5_jprow;
        c5_b_ix0 = c5_ix0;
        c5_b_iy0 = c5_iy0;
        c5_b_eml_switch_helper(chartInstance);
        c5_c_ix0 = c5_b_ix0;
        c5_c_iy0 = c5_b_iy0;
        c5_ix = c5_c_ix0;
        c5_iy = c5_c_iy0;
        c5_eml_switch_helper(chartInstance);
        for (c5_k = 1; c5_k < 5; c5_k++) {
          c5_temp = c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c5_ix), 1, 16, 1, 0) - 1];
          c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_ix), 1, 16, 1, 0) - 1] = c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c5_iy), 1, 16, 1, 0) -
            1];
          c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_iy), 1, 16, 1, 0) - 1] = c5_temp;
          c5_q_a = c5_ix + 4;
          c5_ix = c5_q_a;
          c5_r_a = c5_iy + 4;
          c5_iy = c5_r_a;
        }
      }

      c5_b_jp1j = c5_jp1j;
      c5_s_a = c5_mmj;
      c5_t_a = c5_s_a;
      c5_d_c = c5_t_a;
      c5_u_a = c5_jp1j;
      c5_o_b = c5_d_c - 1;
      c5_v_a = c5_u_a;
      c5_p_b = c5_o_b;
      c5_i41 = c5_v_a + c5_p_b;
      c5_w_a = c5_b_jp1j;
      c5_q_b = c5_i41;
      c5_x_a = c5_w_a;
      c5_r_b = c5_q_b;
      if (c5_x_a > c5_r_b) {
        c5_overflow = false;
      } else {
        c5_eml_switch_helper(chartInstance);
        c5_eml_switch_helper(chartInstance);
        c5_overflow = (c5_r_b > 2147483646);
      }

      if (c5_overflow) {
        c5_check_forloop_overflow_error(chartInstance, c5_overflow);
      }

      for (c5_i = c5_b_jp1j; c5_i <= c5_i41; c5_i++) {
        c5_b_i = c5_i;
        c5_x = c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c5_b_i), 1, 16, 1, 0) - 1];
        c5_y = c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c5_jj), 1, 16, 1, 0) - 1];
        c5_b_x = c5_x;
        c5_b_y = c5_y;
        c5_z = c5_b_x / c5_b_y;
        c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c5_b_i), 1, 16, 1, 0) - 1] = c5_z;
      }
    } else {
      *c5_info = c5_b_j;
    }

    c5_s_b = c5_b_j;
    c5_t_b = c5_s_b;
    c5_e_c = 4 - c5_t_b;
    c5_y_a = c5_jj;
    c5_ab_a = c5_y_a;
    c5_f_c = c5_ab_a;
    c5_bb_a = c5_jj;
    c5_cb_a = c5_bb_a;
    c5_g_c = c5_cb_a;
    c5_b_eml_xgeru(chartInstance, c5_mmj, c5_e_c, -1.0, c5_jp1j, c5_f_c + 4,
                   c5_A, c5_g_c + 5);
  }

  if (*c5_info == 0) {
    if (!(c5_A[15] != 0.0)) {
      *c5_info = 4;
    }
  }
}

static void c5_b_eml_xgeru(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  int32_T c5_m, int32_T c5_n, real_T c5_alpha1, int32_T c5_ix0, int32_T c5_iy0,
  real_T c5_A[16], int32_T c5_ia0)
{
  int32_T c5_b_m;
  int32_T c5_b_n;
  real_T c5_b_alpha1;
  int32_T c5_b_ix0;
  int32_T c5_b_iy0;
  int32_T c5_b_ia0;
  int32_T c5_c_m;
  int32_T c5_c_n;
  real_T c5_c_alpha1;
  int32_T c5_c_ix0;
  int32_T c5_c_iy0;
  int32_T c5_c_ia0;
  int32_T c5_d_m;
  int32_T c5_d_n;
  real_T c5_d_alpha1;
  int32_T c5_d_ix0;
  int32_T c5_d_iy0;
  int32_T c5_d_ia0;
  int32_T c5_e_m;
  int32_T c5_e_n;
  real_T c5_e_alpha1;
  int32_T c5_e_ix0;
  int32_T c5_e_iy0;
  int32_T c5_e_ia0;
  int32_T c5_ixstart;
  int32_T c5_a;
  int32_T c5_jA;
  int32_T c5_jy;
  int32_T c5_f_n;
  int32_T c5_c_b;
  int32_T c5_d_b;
  boolean_T c5_overflow;
  int32_T c5_j;
  real_T c5_yjy;
  real_T c5_temp;
  int32_T c5_ix;
  int32_T c5_e_b;
  int32_T c5_i42;
  int32_T c5_b_a;
  int32_T c5_f_b;
  int32_T c5_i43;
  int32_T c5_c_a;
  int32_T c5_g_b;
  int32_T c5_d_a;
  int32_T c5_h_b;
  boolean_T c5_b_overflow;
  int32_T c5_ijA;
  int32_T c5_b_ijA;
  int32_T c5_e_a;
  int32_T c5_f_a;
  int32_T c5_g_a;
  c5_b_m = c5_m;
  c5_b_n = c5_n;
  c5_b_alpha1 = c5_alpha1;
  c5_b_ix0 = c5_ix0;
  c5_b_iy0 = c5_iy0;
  c5_b_ia0 = c5_ia0;
  c5_c_m = c5_b_m;
  c5_c_n = c5_b_n;
  c5_c_alpha1 = c5_b_alpha1;
  c5_c_ix0 = c5_b_ix0;
  c5_c_iy0 = c5_b_iy0;
  c5_c_ia0 = c5_b_ia0;
  c5_d_m = c5_c_m;
  c5_d_n = c5_c_n;
  c5_d_alpha1 = c5_c_alpha1;
  c5_d_ix0 = c5_c_ix0;
  c5_d_iy0 = c5_c_iy0;
  c5_d_ia0 = c5_c_ia0;
  c5_e_m = c5_d_m;
  c5_e_n = c5_d_n;
  c5_e_alpha1 = c5_d_alpha1;
  c5_e_ix0 = c5_d_ix0;
  c5_e_iy0 = c5_d_iy0;
  c5_e_ia0 = c5_d_ia0;
  if (c5_e_alpha1 == 0.0) {
  } else {
    c5_ixstart = c5_e_ix0;
    c5_a = c5_e_ia0 - 1;
    c5_jA = c5_a;
    c5_jy = c5_e_iy0;
    c5_f_n = c5_e_n;
    c5_c_b = c5_f_n;
    c5_d_b = c5_c_b;
    if (1 > c5_d_b) {
      c5_overflow = false;
    } else {
      c5_eml_switch_helper(chartInstance);
      c5_eml_switch_helper(chartInstance);
      c5_overflow = (c5_d_b > 2147483646);
    }

    if (c5_overflow) {
      c5_check_forloop_overflow_error(chartInstance, c5_overflow);
    }

    for (c5_j = 1; c5_j <= c5_f_n; c5_j++) {
      c5_yjy = c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c5_jy), 1, 16, 1, 0) - 1];
      if (c5_yjy != 0.0) {
        c5_temp = c5_yjy * c5_e_alpha1;
        c5_ix = c5_ixstart;
        c5_e_b = c5_jA + 1;
        c5_i42 = c5_e_b;
        c5_b_a = c5_e_m;
        c5_f_b = c5_jA;
        c5_i43 = c5_b_a + c5_f_b;
        c5_c_a = c5_i42;
        c5_g_b = c5_i43;
        c5_d_a = c5_c_a;
        c5_h_b = c5_g_b;
        if (c5_d_a > c5_h_b) {
          c5_b_overflow = false;
        } else {
          c5_eml_switch_helper(chartInstance);
          c5_eml_switch_helper(chartInstance);
          c5_b_overflow = (c5_h_b > 2147483646);
        }

        if (c5_b_overflow) {
          c5_check_forloop_overflow_error(chartInstance, c5_b_overflow);
        }

        for (c5_ijA = c5_i42; c5_ijA <= c5_i43; c5_ijA++) {
          c5_b_ijA = c5_ijA;
          c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_b_ijA), 1, 16, 1, 0) - 1] =
            c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_b_ijA), 1, 16, 1, 0) - 1] +
            c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c5_ix), 1, 16, 1, 0) - 1] * c5_temp;
          c5_e_a = c5_ix + 1;
          c5_ix = c5_e_a;
        }
      }

      c5_f_a = c5_jy + 4;
      c5_jy = c5_f_a;
      c5_g_a = c5_jA + 4;
      c5_jA = c5_g_a;
    }
  }
}

static void c5_b_eml_xtrsm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[16])
{
  int32_T c5_j;
  int32_T c5_b_j;
  int32_T c5_jBcol;
  int32_T c5_k;
  int32_T c5_b_k;
  int32_T c5_kAcol;
  int32_T c5_i44;
  int32_T c5_c_b;
  int32_T c5_d_b;
  boolean_T c5_overflow;
  int32_T c5_i;
  int32_T c5_b_i;
  c5_c_eml_switch_helper(chartInstance);
  c5_eml_switch_helper(chartInstance);
  for (c5_j = 1; c5_j < 5; c5_j++) {
    c5_b_j = c5_j - 1;
    c5_jBcol = c5_b_j << 2;
    c5_eml_switch_helper(chartInstance);
    for (c5_k = 4; c5_k > 0; c5_k--) {
      c5_b_k = c5_k;
      c5_kAcol = (c5_b_k - 1) << 2;
      if (c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c5_b_k + c5_jBcol)), 1, 16, 1, 0) - 1] != 0.0) {
        c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)(c5_b_k + c5_jBcol)), 1, 16, 1, 0) - 1] = c5_rdivide
          (chartInstance, c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)(c5_b_k + c5_jBcol)), 1, 16, 1, 0) -
           1], c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
             "", (real_T)(c5_b_k + c5_kAcol)), 1, 16, 1, 0) - 1]);
        c5_i44 = c5_b_k - 1;
        c5_c_b = c5_i44;
        c5_d_b = c5_c_b;
        if (1 > c5_d_b) {
          c5_overflow = false;
        } else {
          c5_eml_switch_helper(chartInstance);
          c5_eml_switch_helper(chartInstance);
          c5_overflow = (c5_d_b > 2147483646);
        }

        if (c5_overflow) {
          c5_check_forloop_overflow_error(chartInstance, c5_overflow);
        }

        for (c5_i = 1; c5_i <= c5_i44; c5_i++) {
          c5_b_i = c5_i;
          c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c5_b_i + c5_jBcol)), 1, 16, 1, 0) - 1] =
            c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c5_b_i + c5_jBcol)), 1, 16, 1, 0) - 1] -
            c5_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c5_b_k + c5_jBcol)), 1, 16, 1, 0) - 1] *
            c5_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)(c5_b_i + c5_kAcol)), 1, 16, 1, 0) - 1];
        }
      }
    }
  }
}

static void c5_b_eml_xgemm(SFc5_Prova_inversioneInstanceStruct *chartInstance,
  real_T c5_A[16], real_T c5_B[4], real_T c5_C[4])
{
  int32_T c5_i45;
  int32_T c5_i46;
  int32_T c5_i47;
  (void)chartInstance;
  for (c5_i45 = 0; c5_i45 < 4; c5_i45++) {
    c5_C[c5_i45] = 0.0;
    c5_i46 = 0;
    for (c5_i47 = 0; c5_i47 < 4; c5_i47++) {
      c5_C[c5_i45] += c5_A[c5_i46 + c5_i45] * c5_B[c5_i47];
      c5_i46 += 4;
    }
  }
}

static void init_dsm_address_info(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_Prova_inversioneInstanceStruct
  *chartInstance)
{
  chartInstance->c5_Fx = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c5_Fy = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c5_T = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c5_L = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    3);
  chartInstance->c5_M = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    4);
  chartInstance->c5_N = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    5);
  chartInstance->c5_alpha_1 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_omega_hover = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c5_alpha_2 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_omega_1 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c5_omega_2 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c5_omega_3 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c5_omega_4 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_Prova_inversione_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3836610487U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1967583030U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3838939409U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(418222688U);
}

mxArray* sf_c5_Prova_inversione_get_post_codegen_info(void);
mxArray *sf_c5_Prova_inversione_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("boiueTPUZb0fXIJKAhzMaG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_Prova_inversione_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_Prova_inversione_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_Prova_inversione_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_Prova_inversione_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_Prova_inversione_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c5_Prova_inversione(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[5],T\"alpha_1\",},{M[1],M[26],T\"alpha_2\",},{M[1],M[27],T\"omega_1\",},{M[1],M[28],T\"omega_2\",},{M[1],M[29],T\"omega_3\",},{M[1],M[30],T\"omega_4\",},{M[8],M[0],T\"is_active_c5_Prova_inversione\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_Prova_inversione_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_Prova_inversioneInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_Prova_inversioneInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Prova_inversioneMachineNumber_,
           5,
           1,
           1,
           0,
           16,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_Prova_inversioneMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_Prova_inversioneMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Prova_inversioneMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Fx");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Fy");
          _SFD_SET_DATA_PROPS(2,1,1,0,"T");
          _SFD_SET_DATA_PROPS(3,1,1,0,"L");
          _SFD_SET_DATA_PROPS(4,1,1,0,"M");
          _SFD_SET_DATA_PROPS(5,1,1,0,"N");
          _SFD_SET_DATA_PROPS(6,1,1,0,"omega_hover");
          _SFD_SET_DATA_PROPS(7,2,0,1,"alpha_1");
          _SFD_SET_DATA_PROPS(8,2,0,1,"alpha_2");
          _SFD_SET_DATA_PROPS(9,2,0,1,"omega_1");
          _SFD_SET_DATA_PROPS(10,2,0,1,"omega_2");
          _SFD_SET_DATA_PROPS(11,2,0,1,"omega_3");
          _SFD_SET_DATA_PROPS(12,2,0,1,"omega_4");
          _SFD_SET_DATA_PROPS(13,10,0,0,"Kq");
          _SFD_SET_DATA_PROPS(14,10,0,0,"Kt");
          _SFD_SET_DATA_PROPS(15,10,0,0,"b");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1232);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Prova_inversioneMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_Prova_inversioneInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_Prova_inversioneInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c5_Fx);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c5_Fy);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c5_T);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c5_L);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c5_M);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c5_N);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c5_alpha_1);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c5_omega_hover);
        _SFD_SET_DATA_VALUE_PTR(14U, &chartInstance->c5_Kt);
        _SFD_SET_DATA_VALUE_PTR(13U, &chartInstance->c5_Kq);
        _SFD_SET_DATA_VALUE_PTR(15U, &chartInstance->c5_b);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c5_alpha_2);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c5_omega_1);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c5_omega_2);
        _SFD_SET_DATA_VALUE_PTR(11U, chartInstance->c5_omega_3);
        _SFD_SET_DATA_VALUE_PTR(12U, chartInstance->c5_omega_4);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s6j1ctvD24iqiDVJd274nXB";
}

static void sf_opaque_initialize_c5_Prova_inversione(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
  initialize_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_Prova_inversione(void *chartInstanceVar)
{
  enable_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c5_Prova_inversione(void *chartInstanceVar)
{
  disable_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_Prova_inversione(void *chartInstanceVar)
{
  sf_gateway_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_Prova_inversione(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_Prova_inversione(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c5_Prova_inversione(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_Prova_inversioneInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Prova_inversione_optimization_info();
    }

    finalize_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_Prova_inversione(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c5_Prova_inversione((SFc5_Prova_inversioneInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_Prova_inversione(SimStruct *S)
{
  /* Actual parameters from chart:
     Kq Kt b
   */
  const char_T *rtParamNames[] = { "Kq", "Kt", "b" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Kq*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for Kt*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for b*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Prova_inversione_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,6);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=6; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2686193374U));
  ssSetChecksum1(S,(4014901742U));
  ssSetChecksum2(S,(2693220380U));
  ssSetChecksum3(S,(2389879813U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_Prova_inversione(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_Prova_inversione(SimStruct *S)
{
  SFc5_Prova_inversioneInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_Prova_inversioneInstanceStruct *)utMalloc(sizeof
    (SFc5_Prova_inversioneInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_Prova_inversioneInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_Prova_inversione;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_Prova_inversione;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c5_Prova_inversione;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_Prova_inversione;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_Prova_inversione;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_Prova_inversione;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_Prova_inversione;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_Prova_inversione;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_Prova_inversione;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_Prova_inversione;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c5_Prova_inversione;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->isEnhancedMooreMachine = 0;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->fCheckOverflow = sf_runtime_overflow_check_is_on(S);
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
}

void c5_Prova_inversione_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_Prova_inversione(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_Prova_inversione(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_Prova_inversione(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_Prova_inversione_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
