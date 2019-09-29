#include "Mesh.hpp"

namespace seedengine {

    Mesh::Mesh(const string& path) : Asset<mesh_data>(path) {
        
    }

    void Mesh::load() {

        // Extract mesh data from file
        mesh_data m_data;
        if (!parse(path_, &m_data)) {
            ENGINE_ERROR("Failed to load mesh. Skipping load.");
            return;
        }
        delete data_;
        data_ = new mesh_data();
        *data_ = m_data;

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            // Check that open gl context has been set up
            if (glfwGetCurrentContext() == NULL) {
                ENGINE_ERROR("No active OpenGL context, unable to load mesh into graphics memory. Exiting load.");
                return;
            }

            // Assign VAO
            glGenVertexArrays(1, &vao_);
            glBindVertexArray(vao_);

            // Create indices buffer
            opglCreateIndicesBuffer(data_->indices);

            // Create and bind new vertex buffers
            opglCreateVertexBuffer(0, 3, data_->positions);
            opglCreateVertexBuffer(1, 3, data_->normals);
            opglCreateVertexBuffer(2, 2, data_->uvs);
            opglCreateVertexBuffer(3, 4, data_->colors);

            // Unbind VAO
            glBindVertexArray(0);
            
            //TODO: Create attribute list helper function.

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

            return;
        #endif
    }

    void Mesh::unload() {
        delete data_;
        data_ = nullptr;
        
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            glDeleteVertexArrays(1, &vao_);
            glDeleteBuffers(vertex_buffers_.size() + 1, &vertex_buffers_[0]);
            vao_ = 0;
            indices_buffer_ = 0;
            vertex_buffers_.clear();

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

            return;
        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

            return;
        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

            return;
        #endif
    }

    bool Mesh::extractMesh(const string& path, meshdata& out) {
        
        // Data values that will be returned on success.
        meshdata m_data = meshdata();

        // Regex templates in ECMAScript format
        std::regex path_regex("^.*\\.mesh$");
        std::smatch p_m;
        if (!std::regex_match(path, p_m, path_regex)) {
            ENGINE_ERROR("File '{0}' is not a valid *.mesh file.", path);
            return false;
        }
        std::regex white_regex("^[\\s]*$");
        std::regex property_regex("^[\\s]*\\[([a-zA-Z][\\w]*)\\][\\s]*=[\\s]*(.*)$");
        std::regex attribute_regex("^[\\s]*([a-z][0-9]?)[\\s]+(.*)$");

        // Read the passed file
        std::ifstream file(path);

        string line;
        int line_num = 1;

        // Count all attribute types to make sure that vertices are uniform.
        int p_count  = 0;
        int n_count  = 0;
        int c0_count = 0;
        int c1_count = 0;
        int u0_count = 0;
        int u1_count = 0;
        int u2_count = 0;
        int u3_count = 0;
        int u4_count = 0;
        int u5_count = 0;
        int u6_count = 0;
        int u7_count = 0;
        int u8_count = 0;
        int f_count  = 0;

        //TODO: Rework .mesh file format to include smoothing groups and reusable data

        while (std::getline(file, line)) {
            std::smatch m;
            // Remove comments
            string ncomment_line = line.substr(0, line.find("#", 0));

            if (std::regex_match(ncomment_line, m, white_regex)) {
                // Skip line
            }
            else if (std::regex_match(ncomment_line, m, property_regex)) {
                m_data.properties.insert(std::pair<string, const string>(m[1], m[2]));
            }
            else if (std::regex_match(ncomment_line, m, attribute_regex)) {
                size_t pos = 0;
                string type = m[1];
                string value = m[2];
                // Remove all spaces
                value.erase(remove(value.begin(), value.end(), ' '), value.end());
                // Seperate by commas
                int expected_count = 0; // The number expected

                std::vector<string> values;

                while ((pos = value.find(",")) != string::npos) {
                    string t = value.substr(0, pos);
                    values.push_back(t);
                    // Move on to next token
                    value.erase(0, pos + 1);
                }
                values.push_back(value);

                // Choose array to pass the value to
                if (type.compare("p") == 0) {
                    for (string t : values) m_data.positions.push_back(std::stof(t));
                    expected_count = 3;
                    p_count++;
                }
                else if (type.compare("n") == 0) {
                    for (string t : values) m_data.normals.push_back(std::stof(t));
                    expected_count = 3;
                    n_count++;
                }
                else if (type.compare("c0") == 0) {
                    for (string t : values) m_data.p_colors.push_back(std::stof(t));
                    expected_count = 4;
                    c0_count++;
                }
                else if (type.compare("c1") == 0) {
                    for (string t : values) m_data.s_colors.push_back(std::stof(t));
                    expected_count = 4;
                    c1_count++;
                }
                else if (type.compare("u0") == 0) {
                    for (string t : values) m_data.uv_0.push_back(std::stof(t));
                    expected_count = 2;
                    u0_count++;
                }
                else if (type.compare("u1") == 0) {
                    for (string t : values) m_data.uv_1.push_back(std::stof(t));
                    expected_count = 2;
                    u1_count++;
                }
                else if (type.compare("u2") == 0) {
                    for (string t : values) m_data.uv_2.push_back(std::stof(t));
                    expected_count = 2;
                    u2_count++;
                }
                else if (type.compare("u3") == 0) {
                    for (string t : values) m_data.uv_3.push_back(std::stof(t));
                    expected_count = 2;
                    u3_count++;
                }
                else if (type.compare("u4") == 0) {
                    for (string t : values) m_data.uv_4.push_back(std::stof(t));
                    expected_count = 2;
                    u4_count++;
                }
                else if (type.compare("u5") == 0) {
                    for (string t : values) m_data.uv_5.push_back(std::stof(t));
                    expected_count = 2;
                    u5_count++;
                }
                else if (type.compare("u6") == 0) {
                    for (string t : values) m_data.uv_6.push_back(std::stof(t));
                    expected_count = 2;
                    u6_count++;
                }
                else if (type.compare("u7") == 0) {
                    for (string t : values) m_data.uv_7.push_back(std::stof(t));
                    expected_count = 2;
                    u7_count++;
                }
                else if (type.compare("f") == 0) {
                    for (string t : values) m_data.faces.push_back(std::stoi(t));
                    expected_count = 3;
                    f_count++;
                }
                else {
                    ENGINE_ERROR("File '{0}' has an error at line {1}: Invalid identifier '{2}'.",
                    path, line_num, type);
                    return false;
                }

                if (values.size() != expected_count && type.compare("v") != 0) {
                    ENGINE_ERROR(
                        "File '{0}' has an error at line {1}. Unexpected number of values ({2}!={3}).",
                        path, line_num, values.size(), expected_count);
                }
            }
            else {
                ENGINE_ERROR("File '{0}' has an error at line {1}.", path, line_num);
                return false;
            }
            line_num++;

        }

        int attributes = 3 + (c0_count > 0) + (c1_count > 0) + (u1_count > 0) +
            (u2_count > 0) + (u3_count > 0) + (u4_count > 0) + (u5_count > 0) +
            (u6_count > 0) + (u7_count > 0);
        m_data.vertex_attrib_count = attributes;

        // Check for an empty mesh
        if (p_count == 0) {
            ENGINE_ERROR("Mesh file '{0}' has an no vertices.", path);
            return false;
        }
        // Check for an empty mesh
        else if (f_count == 0) {
            ENGINE_ERROR("Mesh file '{0}' has an no faces.", path);
            return false;
        }
        // Check for inconsistent vertex counts
        else if (
            ( n_count != p_count &&  n_count != 0) ||
            (c0_count != p_count && c0_count != 0) ||
            (c1_count != p_count && c1_count != 0) ||
            (u0_count != p_count && u0_count != 0) ||
            (u1_count != p_count && u1_count != 0) ||
            (u2_count != p_count && u2_count != 0) ||
            (u3_count != p_count && u3_count != 0) ||
            (u4_count != p_count && u4_count != 0) ||
            (u5_count != p_count && u5_count != 0) ||
            (u6_count != p_count && u6_count != 0) ||
            (u7_count != p_count && u7_count != 0)) {
            ENGINE_ERROR("Mesh file '{0}' has an inconsistent vertex count.", path);
            return false;
        }
        // Check if dependent attributes are included properly
        else if (
            (c1_count != c0_count && c1_count != 0) ||
            (u1_count != u0_count && u1_count != 0) ||
            (u2_count != u1_count && u2_count != 0) ||
            (u3_count != u2_count && u3_count != 0) ||
            (u4_count != u3_count && u4_count != 0) ||
            (u5_count != u4_count && u5_count != 0) ||
            (u6_count != u5_count && u6_count != 0) ||
            (u7_count != u6_count && u7_count != 0)) {
            ENGINE_ERROR("Mesh file '{0}' has an inconsistent vertex attribute count.", path);
            return false;
        }
        else {
            out = m_data;
            return true;
        }
    }

    bool Mesh::parse(const string& path, mesh_data* out) {

        util::BinaryParser parser(path);

        // Header data
        std::array<uint32_t, 8> h_data_32{}; // group count, position count, normal count, uv count, color count, bone weight count, morph count, vertices count
        std::array<uint16_t, 1> h_data_16{}; // bone count
        std::array<uint8_t, 2> h_data_8{}; // the number of uv and vertex color channels, unused byte

        //TODO: Store and process bone hierarchy and name data
        //TODO: Consolidate mesh file parsing code

        // Iterate through 32 bit header data
        for (uint32_t i = 0; i < h_data_32.size(); i++) {
            if (!parser.getNext(&h_data_32[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Iterate through 16 bit header data
        for (uint32_t i = 0; i < h_data_16.size(); i++) {
            if (!parser.getNext(&h_data_16[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Iterate through 8 bit header data
        for (uint32_t i = 0; i < h_data_8.size(); i++) {
            if (!parser.getNext(&h_data_8[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        uint8_t uvs_p_vert = (h_data_8[0] & 0xE0) >> 5;
        uint8_t colors_p_vert = (h_data_8[0] & 0x1C) >> 2;
        uint32_t vertex_size = 2 + uvs_p_vert + colors_p_vert;

        // Gather position floats
        std::vector<float> positions = std::vector<float>();
        positions.resize(h_data_32[1] * 3);

        for (uint32_t i = 0; i < h_data_32[1] * 3; i++) {
            if (!parser.getNext(&positions[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather normal floats
        std::vector<float> normals = std::vector<float>();
        normals.resize(h_data_32[2] * 3);

        for (uint32_t i = 0; i < h_data_32[2] * 3; i++) {
            if (!parser.getNext(&normals[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather uv floats
        std::vector<float> uvs = std::vector<float>();
        uvs.resize(h_data_32[3] * 2);

        for (uint32_t i = 0; i < h_data_32[3] * 2; i++) {
            if (!parser.getNext(&uvs[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather color floats
        std::vector<float> colors = std::vector<float>();
        colors.resize(h_data_32[4] * 4);

        for (uint32_t i = 0; i < h_data_32[4] * 4; i++) {
            if (!parser.getNext(&colors[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather bone weight floats
        std::vector<float> bone_weights = std::vector<float>();
        bone_weights.resize(h_data_32[5]);

        for (uint32_t i = 0; i < h_data_32[5]; i++) {
            if (!parser.getNext(&bone_weights[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather morph floats
        std::vector<float> morphs = std::vector<float>();
        morphs.resize(h_data_32[6] * 3);

        for (uint32_t i = 0; i < h_data_32[6] * 3; i++) {
            if (!parser.getNext(&morphs[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather vertices indices
        std::vector<uint32_t> vertices = std::vector<uint32_t>();
        vertices.resize(h_data_32[7] * vertex_size);

        for (uint32_t i = 0; i < h_data_32[7] * vertex_size; i++) {
            if (!parser.getNext(&vertices[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather bones
        std::vector<float> bones = std::vector<float>();
        bones.resize(h_data_16[0]);

        //TODO: Implement mesh file bone system

        for (uint16_t i = 0; i < h_data_16[0]; i++) {
            if (!parser.getNext(&bones[i])) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }
        }

        // Gather vertices data

        std::vector<std::vector<uint32_t>> smoothing_groups = std::vector<std::vector<uint32_t>>();
        smoothing_groups.resize(h_data_32[0]);

        // Iterate through smoothing groups
        for (uint32_t g = 0; g < h_data_32[0]; g++) {
            uint32_t face_count = 0; // The faces in this group
            if (!parser.getNext(&face_count)) {
                ENGINE_WARN("Failed to read mesh file {0}.", path);
                return false;
            }

            std::vector<uint32_t> faces = std::vector<uint32_t>();
            faces.resize(face_count * 3);

            for (uint32_t f = 0; f < face_count * 3; f++) {
                if (!parser.getNext(&faces[f])) {
                    ENGINE_WARN("Failed to read mesh file {0}.", path);
                    return false;
                }
            }

            smoothing_groups[g] = faces;

        }

        std::vector<float> t_positions{};
        t_positions.resize(h_data_32[7] * 3);

        std::vector<float> t_normals{};
        t_normals.resize(h_data_32[7] * 3);

        std::vector<float> t_uvs{};
        t_uvs.resize(h_data_32[7] * 2);

        std::vector<float> t_colors{};
        t_colors.resize(h_data_32[7] * 4);

        //TODO: implement additional uv and color channels

        for (uint32_t v = 0; v < h_data_32[7]; v++) {
            for (uint32_t i = 0; i < 3; i++) t_positions[(v * 3) + i] = positions[vertices[(v * vertex_size)] * 3 + i];
            for (uint32_t i = 0; i < 3; i++) t_normals[(v * 3) + i] = normals[vertices[(v * vertex_size) + 1] * 3 + i];
            for (uint32_t i = 0; i < 2; i++) t_uvs[(v * 2) + i] = uvs[vertices[(v * vertex_size) + 2] * 2 + i];
            for (uint32_t i = 0; i < 4; i++) t_colors[(v * 4) + i] = colors[vertices[(v * vertex_size) + 3] * 4 + i];
        }

        //TODO: Handle animation data

        std::vector<uint32_t> indices_buffer = std::vector<uint32_t>();
        for (uint32_t s = 0; s < smoothing_groups.size(); s++) {
            for (uint32_t f = 0; f < smoothing_groups[s].size(); f++) {
                indices_buffer.push_back(smoothing_groups[s][f]);
            }
        }

        out->positions = t_positions;
        out->normals = t_normals;
        out->uvs = t_uvs;
        out->colors = t_colors;
        out->bone_weights = bone_weights;
        out->morphs = morphs;
        out->uvs_per_vertex = uvs_p_vert;
        out->colors_per_vertex = colors_p_vert;
        out->vertex_size = vertex_size;
        out->indices = indices_buffer;

        return true;

    }

}