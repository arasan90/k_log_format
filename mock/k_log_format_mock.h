/**
 * @addtogroup k_log_format
 * @{
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/* Include -------------------------------------------------------------------*/
#include "fff.h"
#include "k_log_format.h"

/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/
/* Constant ------------------------------------------------------------------*/
/* Variable ------------------------------------------------------------------*/
/* Function Declaration ------------------------------------------------------*/
DECLARE_FAKE_VALUE_FUNC_VARARG(size_t, k_log_format_create_string, const char*, k_log_format_level_t, size_t, char*, size_t, const char*, ...)

#ifdef __cplusplus
}
#endif
/* @} */