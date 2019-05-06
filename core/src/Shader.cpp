#include "Shader.hpp"

namespace seedengine {

    Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path) {

    }

    Shader::~Shader() {
        cleanUp();
    }

    void Shader::start() {

    }

    void Shader::stop() {
        
    }

    void Shader::cleanUp() {
        
    }

    // Check for OpenGL
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        int Shader::getUniformLocation(std::string uniform_name) {
            return 0;
        }

        void Shader::bindAttribute(int attribute, std::string name) {

        }

        void Shader::loadFloat(int location, float value) {

        }
        void Shader::loadInt(int location, int value) {

        }
        void Shader::loadVec2(int location, glm::vec2 value) {

        }
        void Shader::loadVec3(int location, glm::vec3 value) {

        }
        void Shader::loadVec4(int location, glm::vec4 value) {

        }
        void Shader::loadBool(int location, bool value) {

        }
        void Shader::loadMat4(int location, glm::mat4 value) {

        }

        int Shader::loadShader(std::string file, int shader_type) {
            return 0;
        }

    // Check for Vulkan
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


    // Check for DirectX
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


    // Check for Metal
    #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL


    #endif

}