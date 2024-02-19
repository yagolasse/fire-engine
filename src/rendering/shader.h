#pragma once

class Shader {
   private:
    GLuint handle;

   public:
    Shader();
    ~Shader();

    inline GLuint getHandle() const {
        return handle;
    }

    void bind() const;
    void unbind() const;
};
