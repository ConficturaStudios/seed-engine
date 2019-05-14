#include "Shader.hpp"

namespace seedengine {

    Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path,
                    std::string[] attributes, std::string[] uniforms) {
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
            vertex_shader_id_ = loadShader(vertex_shader_path, GL_VERTEX_SHADER);
            fragment_shader_id_ = loadShader(fragment_shader_path, GL_FRAGMENT_SHADER);
            program_id_ = glCreateProgram();
            glAttachShader(program_id_, vertex_shader_id_);
            glAttachShader(program_id_, fragment_shader_id_);
            bindAttributes(attributes);
            glLinkProgram(program_id_);
            glValidateProgram(program_id_);
            getAllUniformLocations(uniforms);
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
            glUseProgram(program_id_);
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
            glUseProgram(0);
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
            stop();
            glDetachShader(program_id_, vertex_shader_id_);
            glDetachShader(program_id_, fragment_shader_id_);
            glDeleteShader(vertex_shader_id_);
            glDeleteShader(fragment_shader_id_);
            glDeleteProgram(program_id_)
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

        std::map<std::string, unsigned int> Shader::locations_;


        void Shader::getAllUniformLocations(std::string[] uniforms) {
            if (uniforms == nullptr) return;
            size_t i = 0;
            while (!uniforms[i].empty()) {
                locations_[uniforms[i]] = getUniformLocation(uniform[i]);
                i++;
            }
        }

        void Shader::bindAttributes(std::string[] attributes) {
            if (attributes == nullptr) return;
            size_t i = 0;
            while (!attributes[i].empty()) {
                bindAttribute(i, attributes[i]);
                i++;
            }
        }

        int Shader::loadShader(std::string file, int shader_type) {
            
            // Read the passed file
            std::ifstream file(file);

            std::string line;
            int line_num = 1;

            std::string buffer = "";

            while (std::getline(file, line)) {
                buffer += line;
                buffer += "\n";
            }

            int shader_id = glCreateShader(shader_type);
            glShaderSource(shader_id, buffer);
            glCompileShader(shader_id);
            if (glGetShader(shader_id, GL_COMPILE_STATUS) == GL_FALSE){
                ENGINE_ERROR(glGetShaderInfoLog(shader_id, 500));
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