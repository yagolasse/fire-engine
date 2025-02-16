#ifndef RENDERER_HPP
#define RENDERER_HPP


typedef void* (* LoadProcedure)(const char *name);

class Renderer {
   private:
    static Renderer* instance;
    
    Renderer();

   public:
    static Renderer* getInstance();
    static void disposeInstance();

    void init(LoadProcedure procedure);
    void setClearColor();
    void clear();
    void draw(int elementCount);
    void makeTextureActive(int index);
    void setViewport(int x, int y, int width, int height);
};

#endif
