# k_log_format

A lightweight, colorized logging library for C/C++ applications that provides formatted log messages with different severity levels.

## Features

- 🎨 **Colorized Output**: Different colors for different log levels (DEBUG, INFO, WARN, ERROR)
- ⏱️ **Timestamp Support**: Millisecond precision timestamp formatting
- 📦 **Module-based Logging**: Organize logs by module names
- 🔧 **Printf-style Formatting**: Support for standard printf format specifiers
- 🚀 **Lightweight**: Minimal dependencies, suitable for embedded systems
- 📱 **Cross-platform**: Works on Linux, Windows, and other platforms
- 🧪 **Well-tested**: Comprehensive test suite with Google Test

## Log Levels

The library supports four log levels with distinct visual styling:

- **DEBUG** (`K_LOG_FORMAT_LEVEL_DEBUG`): Gray text, single 'D' prefix
- **INFO** (`K_LOG_FORMAT_LEVEL_INFO`): White text, single 'I' prefix
- **WARN** (`K_LOG_FORMAT_LEVEL_WARN`): Yellow text, highlighted '*W*' prefix
- **ERROR** (`K_LOG_FORMAT_LEVEL_ERROR`): Red text, highlighted '**E**' prefix

## Quick Start

### Basic Usage

```c
#include "k_log_format.h"

int main() {
    char log_buffer[256];
    size_t timestamp = 123456789; // milliseconds

    // Create a debug log message
    k_log_format_create_string(
        "MyModule",                    // Module name
        K_LOG_FORMAT_LEVEL_DEBUG,      // Log level
        timestamp,                     // Timestamp in milliseconds
        log_buffer,                    // Output buffer
        sizeof(log_buffer),            // Buffer size
        "User %s logged in with ID %d", // Format string
        "john_doe", 42                 // Arguments
    );

    printf("%s", log_buffer);
    return 0;
}
```

### Example Output

```
123456.789 [D][MyModule]User john_doe logged in with ID 42
123456.790 [I][MyModule]System initialized successfully
123456.791 [*W*][MyModule]Memory usage at 80%
123456.792 [**E**][MyModule]Failed to connect to database
```

## API Reference

### Functions

#### `k_log_format_create_string`

Creates a formatted log string with timestamp, level, and module information.

```c
size_t k_log_format_create_string(
    const char *module_name,           // Module generating the log
    k_log_format_level_t level,        // Log level
    size_t timestamp,                  // Timestamp in milliseconds
    char *out_buffer,                  // Output buffer
    size_t out_buffer_size,            // Size of output buffer
    const char *format,                // Printf-style format string
    ...                                // Format arguments
);
```

**Parameters:**
- `module_name`: Name of the module generating the log message
- `level`: Log level (DEBUG, INFO, WARN, ERROR)
- `timestamp`: Timestamp in milliseconds
- `out_buffer`: Buffer to store the formatted message
- `out_buffer_size`: Size of the output buffer
- `format`: Printf-style format string
- `...`: Additional arguments for the format string

**Returns:** Size of the formatted log string, or 0 if input parameters are invalid

### Enumerations

#### `k_log_format_level_t`

```c
typedef enum {
    K_LOG_FORMAT_LEVEL_DEBUG,    // Debug level logging
    K_LOG_FORMAT_LEVEL_INFO,     // Information level logging
    K_LOG_FORMAT_LEVEL_WARN,     // Warning level logging
    K_LOG_FORMAT_LEVEL_ERROR     // Error level logging
} k_log_format_level_t;
```

## Integration

### CMake Integration

Add the library to your CMake project:

```cmake
# Add k_log_format as a subdirectory
add_subdirectory(path/to/k_log_format)

# Include the CMake module
include(path/to/k_log_format/k_log_format.cmake)

# Get sources and headers
k_log_format_get_sources(K_LOG_SOURCES)
k_log_format_get_public_headers(K_LOG_INCLUDES)

# Add to your target
target_sources(your_target PRIVATE ${K_LOG_SOURCES})
target_include_directories(your_target PRIVATE ${K_LOG_INCLUDES})
```

### Manual Integration

1. Copy `include/k_log_format.h` to your include path
2. Copy `src/k_log_format.c` to your source files
3. Compile and link with your project

## Testing and Mocking

The library includes a mock implementation using the FFF (Fake Function Framework) for unit testing.

### Using the Mock Library

The mock library provides fake implementations that can be used to verify logging calls in your tests:

```c
#include "k_log_format_mock.h"

void test_my_function() {
    // Reset the mock before each test
    RESET_FAKE(k_log_format_create_string);

    // Set up the mock behavior
    k_log_format_create_string_fake.return_val = 25; // Expected return value

    // Call your function under test
    my_function_that_logs();

    // Verify the mock was called
    assert(k_log_format_create_string_fake.call_count == 1);
    assert(k_log_format_create_string_fake.arg0_val == "MyModule");
    assert(k_log_format_create_string_fake.arg1_val == K_LOG_FORMAT_LEVEL_INFO);
    // ... verify other arguments as needed
}
```

### CMake Integration for Testing

To use the mock library in your tests, link against the mock library:

```cmake
# Create the mock library
k_log_format_create_mock_library()

# Link your test executable with the mock
target_link_libraries(your_test_target PRIVATE k_log_format_mock)
```

### Available Mock Functions

The mock provides the following fake function:

```c
DECLARE_FAKE_VALUE_FUNC_VARARG(size_t, k_log_format_create_string,
    const char*,           // module_name
    k_log_format_level_t,  // level
    size_t,                // timestamp
    char*,                 // out_buffer
    size_t,                // out_buffer_size
    const char*,           // format
    ...                    // format arguments
);
```

### Mock Control Functions

Use these FFF macros to control and verify the mock behavior:

- `RESET_FAKE(k_log_format_create_string)` - Reset the mock state
- `k_log_format_create_string_fake.call_count` - Number of times called
- `k_log_format_create_string_fake.return_val` - Set return value
- `k_log_format_create_string_fake.arg0_val` - Access first argument value
- `k_log_format_create_string_fake.arg1_val` - Access second argument value
- And so on for other arguments...

For more information about FFF usage, see the [FFF documentation](https://github.com/meekrosoft/fff).

## Dependencies

- **Build Dependencies**: CMake 3.10+, C compiler
- **Runtime Dependencies**: Standard C library (stdio.h, string.h, stdarg.h)

## License

[Add your license information here]

## Contributing

## Contribution Guidelines

Everyone is welcome to contribute! Whether you are reporting bugs, suggesting features, improving documentation, or submitting code, your input is appreciated.

- Please open an issue for bug reports or feature requests.
- Create a new branch for your changes.
- Follow the existing code style and add tests where appropriate.
- Submit a pull request with a clear description of your changes.
- Be respectful and constructive in discussions.

Thank you for helping improving this project!

## Changelog

### Version 1.0.0
- Initial release
- Basic logging functionality with color support
- Four log levels (DEBUG, INFO, WARN, ERROR)
- Timestamp formatting
- Module-based organization
