#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

class Renderer {
   private:
    static Renderer* instance;
    
    Renderer();

   public:
    static Renderer* getInstance();
    static void disposeInstance();

    void init(GLADloadproc loadProcedure);
    void setClearColor();
    void clear();
    void draw(int elementCount);
    void makeTextureActive(int index);
    void setViewport(int x, int y, int width, int height);
};

#endif
