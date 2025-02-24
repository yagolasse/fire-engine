#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
   private:
    static int currentBindingIndex;

    unsigned int handle;
    int width;
    int height;
    int channels;
    int bindingIndex;

   public:
    Texture(const char* path);
    ~Texture();

    void bind() const;

    inline unsigned int getHandle() const {
        return handle;
    }

    inline int getWidth() const {
        return width;
    }

    inline int getHeight() const {
        return height;
    }
};

#endif
