#pragma once

#define ERROR_CHECK_AVAILABLE

#ifdef ERROR_CHECK_AVAILABLE
#define ERROR_CHECK ErrorCheck::logOpenGlErrors();

#include <iostream>

class ErrorCheck {
   public:
    static void logOpenGlErrors();
};

#else
#define ERROR_CHECK
#endif