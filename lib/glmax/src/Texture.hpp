#pragma once
#include <string>
#include "Shader.hpp"
#include "stb_image.h"

namespace glmax {

class Texture {
public:
    Texture()                          = default;
    Texture(const Texture&)            = delete;
    Texture(Texture&&)                 = default;
    Texture& operator=(const Texture&) = delete;
    explicit Texture(const std::string& filePath);
    ~Texture();

    void   load_texture(const std::string& filePath);
    void   bind(unsigned int slot = 0) const;
    void   unbind() const;
    GLuint getID() const { return m_textureID; }

private:
    GLuint m_textureID{};
};

} // namespace glmax
