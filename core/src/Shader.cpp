#include "Shader.hpp"

namespace seedengine {

    Shader::Shader(string vertex_shader_path, string fragment_shader_path, std::vector<string> attributes, std::vector<string> uniforms) {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            vertex_shader_id_ = loadShader(vertex_shader_path, GL_VERTEX_SHADER);
            if (vertex_shader_id_ == 0) initialized_ = false;
            else {
                fragment_shader_id_ = loadShader(fragment_shader_path, GL_FRAGMENT_SHADER);
                if (fragment_shader_id_ == 0) {
                    initialized_ = false;
                    glDeleteShader(vertex_shader_id_);
                }
                else {
                    program_id_ = glCreateProgram();
                    glAttachShader(program_id_, vertex_shader_id_);
                    glAttachShader(program_id_, fragment_shader_id_);
                    bindAttributes(attributes);
                    glLinkProgram(program_id_);
                    glValidateProgram(program_id_);
                    getAllUniformLocations(uniforms);
                    initialized_ = true;
                }
            }
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif
    }

    Shader::~Shader() {
        cleanUp();
    }

    void Shader::start() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            if (initialized_) glUseProgram(program_id_);
            else ENGINE_WARN("Shader cannot be run, it is uninitialized.");
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif
    }

    void Shader::stop() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            if (initialized_) glUseProgram(0);
            else ENGINE_WARN("Shader could not run, it is uninitialized.");
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif
        
    }

    void Shader::cleanUp() {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            if (initialized_) {
                stop();
                glDetachShader(program_id_, vertex_shader_id_);
                glDetachShader(program_id_, fragment_shader_id_);
                glDeleteShader(vertex_shader_id_);
                glDeleteShader(fragment_shader_id_);
                glDeleteProgram(program_id_);
            }
        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN

        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX

        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL

        #endif
        
    }

    // Check for OpenGL
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL


        void Shader::getAllUniformLocations(std::vector<string> uniforms) {
            if (uniforms.empty()) return;
            for (string uniform : uniforms) {
                locations_.insert(std::pair<string, int>(uniform, getUniformLocation(uniform)));
            }
        }

        void Shader::bindAttributes(std::vector<string> attributes) {
            if (attributes.empty()) return;
            for (unsigned int i = 0; i < attributes.size(); i++) {
                bindAttribute(i, attributes[i]);
            }
        }

        int Shader::loadShader(string filepath, int shader_type) {
            
            // Read the passed file
            std::ifstream file(filepath, std::ifstream::in);

            string line;
            int line_num = 1;

            string buffer = "";

            if (file.is_open()) {
                while (std::getline(file, line)) {
                    buffer += line;
                    buffer += "\n";
                }
                file.close();
            }

            int shader_id = glCreateShader(shader_type);
            GLchar const* files[] = { buffer.c_str() };
            GLint lengths[] = { (GLuint)buffer.size() };

            //TODO: Create common shader code that can be written in prior to each source file
            glShaderSource(shader_id, 1, files, lengths);
            glCompileShader(shader_id);

            GLint compiled = 0;
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
            if (compiled == GL_FALSE) {

                GLint max_length = 0;
                glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

                std::vector<char> error_log(max_length);

                glGetShaderInfoLog(shader_id, max_length, &max_length, &error_log[0]);

                string msg(error_log.begin(), error_log.end());
                ENGINE_ERROR(msg);

                glDeleteShader(shader_id);

                return 0;
            }
            return shader_id;

        }

    // Check for Vulkan
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


    // Check for DirectX
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


    // Check for Metal
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL


    #endif

}