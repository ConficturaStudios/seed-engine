#include "Mesh.hpp"

namespace seedengine {

    Mesh::Mesh(const string& path) : Asset<meshdata>(path) {
        
    }

    void Mesh::load() {
        // Extract mesh data from file
        meshdata m_data = extractMesh(path_);
        if (m_data == nullobj) {
            ENGINE_ERROR("Failed to load mesh. Skipping load.");
            return;
        }
        delete data_;
        data_ = new meshdata();
        *data_ = m_data;

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            //TODO: Check that open gl context has been set up

            // Assign VAO
            glGenVertexArrays(1, &vao_);
            glBindVertexArray(vao_);

            // Create indices buffer
            opglCreateIndicesBuffer(data_->faces);

            // Create and bind new vertex buffers
            opglCreateVertexBuffer(0, 3, data_->positions);
            //opglCreateVertexBuffer(3, pos);
            if (data_->normals.size() > 0) opglCreateVertexBuffer(1, 3, data_->normals);
            if (data_->p_colors.size() > 0) opglCreateVertexBuffer(2, 4, data_->p_colors);
            //if (data_->s_colors.size() > 0) opglCreateVertexBuffer(3, 4, data_->s_colors);
            if (data_->uv_0.size() > 0) opglCreateVertexBuffer(3, 2, data_->uv_0);
            /*if (data_->uv_1.size() > 0) opglCreateVertexBuffer(5, 2, data_->uv_1);
            if (data_->uv_2.size() > 0) opglCreateVertexBuffer(6, 2, data_->uv_2);
            if (data_->uv_3.size() > 0) opglCreateVertexBuffer(7, 2, data_->uv_3);
            if (data_->uv_4.size() > 0) opglCreateVertexBuffer(8, 2, data_->uv_4);
            if (data_->uv_5.size() > 0) opglCreateVertexBuffer(9, 2, data_->uv_5);
            if (data_->uv_6.size() > 0) opglCreateVertexBuffer(10, 2, data_->uv_6);
            if (data_->uv_7.size() > 0) opglCreateVertexBuffer(11, 2, data_->uv_7);*/

            // Unbind buffers
            //glBindBuffer(GL_ARRAY_BUFFER, 0);
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

    meshdata Mesh::extractMesh(const string& path) {
        
        // Data values that will be returned on success.
        meshdata m_data = meshdata();

        // Regex templates in ECMAScript format
        std::regex path_regex("^.*\\.mesh$");
        std::smatch p_m;
        if (!std::regex_match(path, p_m, path_regex)) {
            ENGINE_ERROR("File '{0}' is not a valid *.mesh file.", path);
            return nullobj;
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
                    return nullobj;
                }

                if (values.size() != expected_count && type.compare("v") != 0) {
                    ENGINE_ERROR(
                        "File '{0}' has an error at line {1}. Unexpected number of values ({2}!={3}).",
                        path, line_num, values.size(), expected_count);
                }
            }
            else {
                ENGINE_ERROR("File '{0}' has an error at line {1}.", path, line_num);
                return nullobj;
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
            return nullobj;
        }
        // Check for an empty mesh
        else if (f_count == 0) {
            ENGINE_ERROR("Mesh file '{0}' has an no faces.", path);
            return nullobj;
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
            return nullobj;
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
            return nullobj;
        }
        else {
            return m_data;
        }
    }
}