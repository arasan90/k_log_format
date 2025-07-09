/**
 * @file k_log_format.c
 * @ingroup k_log_format
 * @{
 */

/* Include -------------------------------------------------------------------*/
#include "k_log_format.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Macro ---------------------------------------------------------------------*/
#define K_LOG_FORMAT_COLOR_BG_BLACK			  "[24;40m"  //!< Background color black
#define K_LOG_FORMAT_COLOR_BG_BRIGHT_RED	  "[4;41m"	  //!< Background color bright red
#define K_LOG_FORMAT_COLOR_BG_BRIGHT_YELLOW	  "[4;43m"	  //!< Background color bright yellow
#define K_LOG_FORMAT_COLOR_TEXT_BLACK		  "[2;30m"	  //!< Text color black
#define K_LOG_FORMAT_COLOR_TEXT_BRIGHT_BLACK  "[1;30m"	  //!< Text color bright black
#define K_LOG_FORMAT_COLOR_TEXT_BRIGHT_RED	  "[1;31m"	  //!< Text color bright red
#define K_LOG_FORMAT_COLOR_TEXT_BRIGHT_GREEN  "[1;32m"	  //!< Text color bright green
#define K_LOG_FORMAT_COLOR_TEXT_BRIGHT_YELLOW "[1;33m"	  //!< Text color bright yellow
#define K_LOG_FORMAT_COLOR_TEXT_WHITE		  "[2;37m"	  //!< Text color white

#define K_LOG_FORMAT_COLOR_DEFAULT		K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_WHITE
#define K_LOG_FORMAT_COLOR_HEADER_ERROR K_LOG_FORMAT_COLOR_BG_BRIGHT_RED K_LOG_FORMAT_COLOR_TEXT_BLACK
#define K_LOG_FORMAT_COLOR_HEADER_WARN	K_LOG_FORMAT_COLOR_BG_BRIGHT_YELLOW K_LOG_FORMAT_COLOR_TEXT_BLACK
#define K_LOG_FORMAT_COLOR_HEADER_INFO	K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_BRIGHT_GREEN
#define K_LOG_FORMAT_COLOR_HEADER_DEBUG K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_BRIGHT_BLACK
#define K_LOG_FORMAT_COLOR_TEXT_ERROR	K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_BRIGHT_RED
#define K_LOG_FORMAT_COLOR_TEXT_WARN	K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_BRIGHT_YELLOW
#define K_LOG_FORMAT_COLOR_TEXT_INFO	K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_WHITE
#define K_LOG_FORMAT_COLOR_TEXT_DEBUG	K_LOG_FORMAT_COLOR_BG_BLACK K_LOG_FORMAT_COLOR_TEXT_BRIGHT_BLACK

#define K_LOG_FORMAT_TMP_BUFFER_SIZE (256u)	 //!< Size of the temporary buffer used for formatting log message
/* Typedef -------------------------------------------------------------------*/
/* Function Declaration ------------------------------------------------------*/
/* Constant ------------------------------------------------------------------*/

const char* K_LOG_FORMAT_PREFIX_DEBUG = K_LOG_FORMAT_COLOR_HEADER_DEBUG "D" K_LOG_FORMAT_COLOR_DEFAULT;
const char* K_LOG_FORMAT_PREFIX_INFO  = K_LOG_FORMAT_COLOR_HEADER_INFO "I" K_LOG_FORMAT_COLOR_DEFAULT;
const char* K_LOG_FORMAT_PREFIX_WARN  = K_LOG_FORMAT_COLOR_HEADER_WARN "*W*" K_LOG_FORMAT_COLOR_DEFAULT;
const char* K_LOG_FORMAT_PREFIX_ERROR = K_LOG_FORMAT_COLOR_HEADER_ERROR "**E**" K_LOG_FORMAT_COLOR_DEFAULT;

/* Variable ------------------------------------------------------------------*/
/* Function Definition -------------------------------------------------------*/
size_t k_log_format_create_string(const char* module_name, k_log_format_level_t level, size_t timestamp, char* out_buffer, size_t out_buffer_size,
								  const char* format, ...)
{
	size_t message_size = 0;
	if (module_name && out_buffer && out_buffer_size && format)
	{
		char		 formatted_message[K_LOG_FORMAT_TMP_BUFFER_SIZE] = {0};	 // Temporary buffer for formatted message
		const size_t timestamp_seconds								 = timestamp / 1000;
		const size_t timestamp_milliseconds							 = timestamp % 1000;

		const char* level_prefix = K_LOG_FORMAT_LEVEL_DEBUG == level ? K_LOG_FORMAT_PREFIX_DEBUG :
								   K_LOG_FORMAT_LEVEL_INFO == level	 ? K_LOG_FORMAT_PREFIX_INFO :
								   K_LOG_FORMAT_LEVEL_WARN == level	 ? K_LOG_FORMAT_PREFIX_WARN :
																	   K_LOG_FORMAT_PREFIX_ERROR;  // Default to error if level is not recognized
		const char* text_color	 = K_LOG_FORMAT_LEVEL_DEBUG == level ? K_LOG_FORMAT_COLOR_TEXT_DEBUG :
								   K_LOG_FORMAT_LEVEL_INFO == level	 ? K_LOG_FORMAT_COLOR_TEXT_INFO :
								   K_LOG_FORMAT_LEVEL_WARN == level	 ? K_LOG_FORMAT_COLOR_TEXT_WARN :
																	   K_LOG_FORMAT_COLOR_TEXT_ERROR;  // Default to error if level is not recognized

		snprintf(formatted_message, K_LOG_FORMAT_TMP_BUFFER_SIZE, "%s%zu.%03zu [%s]%s[%s]", K_LOG_FORMAT_COLOR_DEFAULT, timestamp_seconds,
				 timestamp_milliseconds, level_prefix, text_color, module_name);
		char*	formatted_message_ptr = formatted_message + strlen(formatted_message);
		va_list args;
		va_start(args, format);
		vsnprintf(formatted_message_ptr, K_LOG_FORMAT_TMP_BUFFER_SIZE - strlen(formatted_message), format, args);
		va_end(args);
		strncpy(out_buffer, formatted_message, out_buffer_size - 1);  // Copy formatted message to output buffer
		message_size = strlen(out_buffer);
	}
	return message_size;
}