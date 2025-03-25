#pragma once
#include <glad/glad.h>

class EBO {
public:
    EBO();
    ~EBO();
    void init();
    void bind() const;
    void unbind() const;
    void set_data(const void* data, GLsizeiptr size);
private:
    GLuint m_id;
};