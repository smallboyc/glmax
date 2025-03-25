#include "VAO.hpp"

VAO::VAO()
    : m_id(0) {}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_id);
}

void VAO::init()
{
    glGenVertexArrays(1, &m_id);
}

void VAO::bind() const
{
    glBindVertexArray(m_id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}