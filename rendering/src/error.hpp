#ifndef ERROR_HPP
#define ERROR_HPP

#include <glad/glad.h>

#include <iostream>
#include <string>

class Error {
   public:
    static GLenum glCheckError_(const char* file, int line);
};

#ifdef _DEBUG
#define glCheckError() Error::glCheckError_(__FILE__, __LINE__)
#else
#define glCheckError()  // Does nothing at all
#endif

#endif
