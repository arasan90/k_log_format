#include "k_log_format.h"

#include <gtest/gtest.h>

#include <string>
class KLogFormatTest : public ::testing::Test
{
   protected:
	void SetUp() override { out_buf.clear(); }

	std::string module_name	 = "k_log_format_test";
	std::string test_message = "%s %d\r\n";
	std::string out_buf		 = std::string(1024, '\0');	 // Initialize output buffer with 1024 null characters
};

TEST_F(KLogFormatTest, formatDebugMessage)
{
	std::string expected_output =
		"\033[24;40m\033[2;37m123456.789 [\033[24;40m\033[1;30mD\033[24;40m\033[2;37m]\033[24;40m\033[1;30m[k_log_format_test]Purpose of life:  42\r\n";
	k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), out_buf.capacity(), test_message.c_str(),
							   "Purpose of life: ", 42);
	std::cout << out_buf;
	EXPECT_STREQ(out_buf.c_str(), expected_output.c_str());
}

TEST_F(KLogFormatTest, formatInfoMessage)
{
	std::string expected_output =
		"\x1B[24;40m\x1B[2;37m123456.789 [\x1B[24;40m\x1B[1;32mI\x1B[24;40m\x1B[2;37m]\x1B[24;40m\x1B[2;37m[k_log_format_test]Purpose of life:  42\r\n";
	k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_INFO, 123456789, out_buf.data(), out_buf.capacity(), test_message.c_str(),
							   "Purpose of life: ", 42);
	std::cout << out_buf;
	EXPECT_STREQ(out_buf.c_str(), expected_output.c_str());
}

TEST_F(KLogFormatTest, formatWarnMessage)
{
	std::string expected_output =
		"\x1B[24;40m\x1B[2;37m123456.789 [\x1B[4;43m\x1B[2;30m*W*\x1B[24;40m\x1B[2;37m]\x1B[24;40m\x1B[1;33m[k_log_format_test]Purpose of life:  42\r\n";
	k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_WARN, 123456789, out_buf.data(), out_buf.capacity(), test_message.c_str(),
							   "Purpose of life: ", 42);
	std::cout << out_buf;
	EXPECT_STREQ(out_buf.c_str(), expected_output.c_str());
}

TEST_F(KLogFormatTest, formatErrorMessage)
{
	std::string expected_output =
		"\x1B[24;40m\x1B[2;37m123456.789 [\x1B[4;41m\x1B[2;30m**E**\x1B[24;40m\x1B[2;37m]\x1B[24;40m\x1B[1;31m[k_log_format_test]Purpose of life:  42\r\n";
	k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_ERROR, 123456789, out_buf.data(), out_buf.capacity(), test_message.c_str(),
							   "Purpose of life: ", 42);
	std::cout << out_buf;
	EXPECT_STREQ(out_buf.c_str(), expected_output.c_str());
}

TEST_F(KLogFormatTest, formatWithInvalidBuffer)
{
	// Test with an invalid output buffer size
	size_t result =
		k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), 0, test_message.c_str(), "Purpose of life: ", 42);
	EXPECT_EQ(result, 0);  // Expect the function to return 0 for invalid buffer size
}

TEST_F(KLogFormatTest, formatWithNullModuleName)
{
	// Test with a null module name
	size_t result = k_log_format_create_string(nullptr, K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), out_buf.capacity(), test_message.c_str(),
											   "Purpose of life: ", 42);
	EXPECT_EQ(result, 0);  // Expect the function to return 0 for null module name
}

TEST_F(KLogFormatTest, formatWithNullFormat)
{
	// Test with a null format string
	size_t result = k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), out_buf.capacity(), nullptr);
	EXPECT_EQ(result, 0);  // Expect the function to return 0 for null format string
}

TEST_F(KLogFormatTest, formatWithEmptyFormat)
{
	// Test with an empty format string
	size_t result = k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), out_buf.capacity(), "");
	EXPECT_GT(result, 0);  // Expect the function to return a positive size for an empty format string
}

TEST_F(KLogFormatTest, formatWithLongMessage)
{
	// Test with a long message that exceeds the temporary buffer size
	std::string long_message =
		"This is a very long message that should exceed the temporary buffer size and test the truncation behavior of the logging function.This is a very long "
		"message that should exceed the temporary buffer size and test the truncation behavior of the logging function.This is a very long message that should "
		"exceed the temporary buffer size and test the truncation behavior of the logging function.This is a very long message that should exceed the "
		"temporary buffer size and test the truncation behavior of the logging function.This is a very long message that should exceed the temporary buffer "
		"size and test the truncation behavior of the logging function.This is a very long message that should exceed the temporary buffer size and test the "
		"truncation behavior of the logging function.";
	size_t result =
		k_log_format_create_string(module_name.c_str(), K_LOG_FORMAT_LEVEL_DEBUG, 123456789, out_buf.data(), out_buf.capacity(), long_message.c_str());
	EXPECT_EQ(result, 255);	 // Expect the function to return a positive size
}