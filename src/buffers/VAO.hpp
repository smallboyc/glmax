#pragma once
#include <glad/glad.h>

class VAO {
public:
    VAO();
    ~VAO();
    void init();
    void bind() const;
    void unbind() const;
private:
    GLuint m_id;
};