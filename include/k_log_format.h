/**
 * @brief Logging library header file
 * @addtogroup k_log_format
 * @{
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/* Include -------------------------------------------------------------------*/
#include <stddef.h>

/* Macro ---------------------------------------------------------------------*/
/* Typedef -------------------------------------------------------------------*/

/**
 * @brief Logging format levels
 */
typedef enum
{
	K_LOG_FORMAT_LEVEL_DEBUG,  //!< Debug level logging
	K_LOG_FORMAT_LEVEL_INFO,   //!< Information level logging
	K_LOG_FORMAT_LEVEL_WARN,   //!< Warning level logging
	K_LOG_FORMAT_LEVEL_ERROR   //!< Error level logging
} k_log_format_level_t;

/* Constant ------------------------------------------------------------------*/
/* Variable ------------------------------------------------------------------*/
/* Function Declaration ------------------------------------------------------*/
/**
 * @brief Create a formatted log string
 *
 * This function formats a log message with the specified module name, level, and format string.
 *
 * @note If the provided buffer is not large enough to hold the formatted string,
 *       the function will truncate the message to fit.
 * @param module_name The name of the module generating the log message
 * @param level The logging level (debug, info, warn, error)
 * @param timestamp The timestamp for the log message, in milliseconds
 * @param out_buffer The buffer to store the formatted log message
 * @param out_buffer_size The size of the output buffer
 * @param format The format string for the log message
 * @param ... Additional arguments for the format string
 * @return The size of log string created, or 0 if the input parameters are invalid.
 */
size_t k_log_format_create_string(const char *module_name, k_log_format_level_t level, size_t timestamp, char *out_buffer, size_t out_buffer_size,
								  const char *format, ...);

#ifdef __cplusplus
}
#endif
/* @} */