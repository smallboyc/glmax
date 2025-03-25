#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"

class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3

private:
    // single mesh
    glmax::Mesh m_mesh;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};