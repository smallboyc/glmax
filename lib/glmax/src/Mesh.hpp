#pragma once
#include <vector>
#include "Material.hpp"
#include "Vertex.hpp"

namespace glmax {

// stock les indices qui partagent le même material.
struct Submesh {
    unsigned int m_index_offset;
    unsigned int m_index_count;
    unsigned int m_material_id;
};

class Mesh {
private:
    std::vector<Vertex>       m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Material>     m_materials;
    std::vector<Submesh>      m_submeshes;

public:
    Mesh() = default;
    void                         load(const std::string& obj_path, const std::string& mtl_path);
    std::vector<Vertex>          get_vertices() const { return m_vertices; };
    std::vector<unsigned int>    get_indices() const { return m_indices; };
    const std::vector<Material>& get_materials() const { return m_materials; };
    std::vector<Submesh>         get_submeshes() const { return m_submeshes; };
};
} // namespace glmax