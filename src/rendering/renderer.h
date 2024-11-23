#pragma once

#include <glad/glad.h>

class Renderer {
   public:
    static void init(GLADloadproc loadProcedure);
    static void setClearColor();
    static void clear();
    static void draw(int elementCount);
    static void makeTextureActive(int index);
    static void setViewport(int x, int y, int width, int height);
};
