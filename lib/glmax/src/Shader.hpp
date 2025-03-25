#pragma once
#include <glad/glad.h>
#include <optional>
#include <string>
#include <unordered_map>
#include "glm/fwd.hpp"

namespace glmax {

class Shader {
public:
    Shader() = default;
    ~Shader();

    void   use() const;
    GLuint getID() const;
    void   load_shader(const std::string& vertexPath, const std::string& fragmentPath);
    void   set_uniform_matrix_4fv(const std::string& name, const glm::mat4& value);
    void   set_uniform_3fv(const std::string& name, const glm::vec3& value);
    void   set_uniform_1f(const std::string& name, float value);
    void   set_uniform_1i(const std::string& name, int value);

private:
    GLuint                                 m_programID;
    std::unordered_map<std::string, GLint> m_uniform_cache;
    //
    GLuint               compile_shader(const std::string& path, GLenum type);
    std::string          read_file(const std::string& path);
    std::optional<GLint> get_uniform_location(const std::string& name);
};

} // namespace glmax
