#include "Mesh.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
//
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace glmax {

// create vertex
Vertex create_vertex(const tinyobj::index_t& index, const tinyobj::attrib_t& attrib)
{
    Vertex vertex{};
    // Remplissage des attributs du vertex
    vertex.m_position = glm::vec3(
        attrib.vertices[3 * index.vertex_index],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
    );

    vertex.m_normal = glm::vec3(
        attrib.normals[3 * index.normal_index],
        attrib.normals[3 * index.normal_index + 1],
        attrib.normals[3 * index.normal_index + 2]
    );

    vertex.m_tex_coord = glm::vec2(
        attrib.texcoords[2 * index.texcoord_index],
        attrib.texcoords[2 * index.texcoord_index + 1]
    );

    return vertex;
}

// save vertex or not, save index btw
void save_vertex(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const Vertex vertex)
{
    bool found{false};
    for (size_t i{0}; i < vertices.size(); i++)
    {
        if (vertices[i].m_position == vertex.m_position && vertices[i].m_normal == vertex.m_normal && vertices[i].m_tex_coord == vertex.m_tex_coord)
        {
            found = true;
            indices.push_back(i);
            break;
        }
    }
    if (!found)
    {
        vertices.push_back(vertex);
        indices.push_back(vertices.size() - 1);
    }
}

// create material
void fill_material(Material& mat, const tinyobj::material_t& material)
{
    mat.m_name = material.name;
    mat.m_Ka   = glm::vec3(material.ambient[0], material.ambient[1], material.ambient[2]);
    // on détermine la couleur diffuse à la volée dans le jeu d'échec.
    mat.m_Kd    = glm::vec3(material.diffuse[0], material.diffuse[1], material.diffuse[2]);
    mat.m_Ks    = glm::vec3(material.specular[0], material.specular[1], material.specular[2]);
    mat.m_Tr    = glm::vec3(material.transmittance[0], material.transmittance[1], material.transmittance[2]);
    mat.m_Le    = glm::vec3(material.emission[0], material.emission[1], material.emission[2]);
    mat.m_Ns    = material.shininess;
    mat.m_Ni    = material.ior;
    mat.m_d     = material.dissolve;
    mat.m_illum = static_cast<float>(material.illum);

    // Textures
    if (!material.ambient_texname.empty())
    {
        mat.m_mapKa.load_texture(material.ambient_texname);
        mat.m_hasMapKa = true;
    }

    if (!material.diffuse_texname.empty())
    {
        mat.m_mapKd.load_texture(material.diffuse_texname);
        mat.m_hasMapKd = true;
    }

    if (!material.specular_texname.empty())
    {
        mat.m_mapKs.load_texture(material.specular_texname);
        mat.m_hasMapKs = true;
    }

    if (!material.specular_highlight_texname.empty())
    {
        mat.m_mapNs.load_texture(material.specular_highlight_texname);
        mat.m_hasMapNs = true;
    }

    if (!material.alpha_texname.empty())
    {
        mat.m_mapD.load_texture(material.alpha_texname);
        mat.m_hasMapD = true;
    }

    if (!material.bump_texname.empty())
    {
        mat.m_mapBump.load_texture(material.bump_texname);
        mat.m_hasMapBump = true;
    }
}

// load .obj mesh
void Mesh::load(const std::string& obj_path, const std::string& mtl_path)
{
    std::string              relativePath = "../../assets/models/";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = relativePath + mtl_path;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(relativePath + obj_path, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    const tinyobj::attrib_t&                attrib    = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>&    shapes    = reader.GetShapes();
    const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();

    // push materials first
    m_materials.reserve(materials.size());
    for (const tinyobj::material_t& material : materials)
    {
        m_materials.push_back(Material{});
        fill_material(m_materials.back(), material);
    }

    // create vertex & give indices, in parallel we have to specify the submesh for multiple materials management
    unsigned int index_offset = 0;
    for (const tinyobj::shape_t& shape : shapes)
    {
        Submesh submesh{};
        submesh.m_index_offset = index_offset;
        submesh.m_material_id  = shape.mesh.material_ids[0];
        // shape = triangle = fragment
        unsigned int index_count = 0;
        for (const tinyobj::index_t index : shape.mesh.indices)
        {
            Vertex vertex = create_vertex(index, attrib);
            save_vertex(m_vertices, m_indices, vertex);
            index_count++;
        }
        submesh.m_index_count = index_count;
        index_offset += index_count;
        m_submeshes.push_back(submesh);
    }
}
} // namespace glmax
