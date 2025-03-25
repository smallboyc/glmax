#include "Texture.hpp"
#include <iostream>
#include <string>
#include "Shader.hpp"
#include "stb_image.h"

namespace glmax {

Texture::Texture(const std::string& filePath)
{
    load_texture(filePath);
}

Texture::~Texture()
{
    if (m_textureID)
    {
        glDeleteTextures(1, &m_textureID);
    }
}

void Texture::load_texture(const std::string& filePath)
{
    int width      = 0;
    int height     = 0;
    int nrChannels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);
    if (!data)
    {
        std::cerr << "Erreur : Impossible de charger la texture " << filePath << std::endl;
        return;
    }

    glGenTextures(1, &m_textureID);

    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    //
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace glmax
