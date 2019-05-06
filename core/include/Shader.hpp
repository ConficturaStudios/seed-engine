#ifndef SEEDENGINE_INCLUDE_SHADER_H_
#define SEEDENGINE_INCLUDE_SHADER_H_

#include "Core.hpp"

namespace seedengine {

    // A Shader
    class Shader {
        
    public:

        // Constructs a new Shader
        // @param(std::string) vertex_shader_path
        // @param(std::string) fragment_shader_path
        Shader(std::string, std::string);

        // Destroys this shader.
        virtual ~Shader();

        // Starts the shader.
        inline void start();
        // Stops the shader.
        inline void stop();
        // Cleans up the memory used for this shader.
        inline void cleanUp();

    protected:
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            // Gets the locations of all needed uniforms.
            virtual void getAllUniformLocations() const = 0;

            // Binds all needed attributes to the shader.
            virtual void bindAttributes() const = 0;

            // Gets the location of the specified uniform.
            // @param(std::string) uniform_name: The name of the uniform to check.
            // @returns: The location of the requested uniform.
            inline int getUniformLocation(std::string);

            // Binds the specified attribute to the shader.
            // @param(int) attribute: The attribute to bind.
            // @param(std::string) name: The name of the attirbute to bind.
            inline void bindAttribute(int, std::string);

            // Loads a float at the specified location.
            // @param(int) location: The location to bind to.
            // @param(float) value: The value to bind.
            inline void loadFloat(int, float);
            // Loads a int at the specified location.
            // @param(int) location: The location to bind to.
            // @param(int) value: The value to bind.
            inline void loadInt(int, int);
            // Loads a vector 2 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec2) value: The value to bind.
            inline void loadVec2(int, glm::vec2);
            // Loads a vector 3 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec3) value: The value to bind.
            inline void loadVec3(int, glm::vec3);
            // Loads a vector 4 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec4) value: The value to bind.
            inline void loadVec4(int, glm::vec4);
            // Loads a bool at the specified location.
            // @param(int) location: The location to bind to.
            // @param(bool) value: The value to bind.
            inline void loadBool(int, bool);
            // Loads a 4x4 matrix at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::mat4) value: The value to bind.
            inline void loadMat4(int, glm::mat4);

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL


        #endif

    private:
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            // The ID of this shader in memory.
            int program_id_;
            // The ID of this shader's vertex shader.
            int vertex_shader_id_;
            // The ID of this shader's fragment shader.
            int fragment_shader_id_;

            // Loads a shader from the disk.
            // @param(std::string) file: The path to the file to load from.
            // @param(int) shader_type: The type of shader being loaded.
            // @returns: The ID of the shader in memory.
            static int loadShader(std::string, int);

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL


        #endif

    };

}

#endif