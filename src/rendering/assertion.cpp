#include "assertion.hpp"

#include <iostream>

void Logger::reportAssertionFailure(const char* expression, const char* message, const char* file, int line) {
    std::cerr << "Assertion Failure: " << expression << ", message: " << message << ", in file: " << file << ", line: " << line << std::endl;
}
