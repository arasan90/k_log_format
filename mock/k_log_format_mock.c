/**
 * @file k_log_format_mock.c
 * @ingroup k_log_format
 * @{
 */

/* Include -------------------------------------------------------------------*/
#include "k_log_format_mock.h"

/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Function Declaration ------------------------------------------------------*/
/* Constant ------------------------------------------------------------------*/
/* Variable ------------------------------------------------------------------*/
/* Function Definition -------------------------------------------------------*/
DEFINE_FAKE_VALUE_FUNC_VARARG(size_t, k_log_format_create_string, const char*, k_log_format_level_t, size_t, char*, size_t, const char*, ...)
