#include "EBO.hpp"

EBO::EBO()
    : m_id(0) {}

EBO::~EBO()
{
    glDeleteBuffers(1, &m_id);
}

void EBO::init()
{
    glGenBuffers(1, &m_id);
}

void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::set_data(const void* data, GLsizeiptr size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}