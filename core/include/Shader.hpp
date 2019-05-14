#ifndef SEEDENGINE_INCLUDE_SHADER_H_
#define SEEDENGINE_INCLUDE_SHADER_H_

#include "Core.hpp"

namespace seedengine {

    struct shader_vertex_data_t {
        float transformation_mat[16];
        float projection_mat[16];
        float view_mat[16];
    };

    // A Shader
    class Shader {
        
    public:

        // Constructs a new Shader
        // @param(std::string) vertex_shader_path
        // @param(std::string) fragment_shader_path
        // @param(std::string[]) attributes: The attributes to bind.
        // @param(std::string[]) uniforms: The names of the uniforms to store.
        Shader(std::string, std::string, std::string[], std::string[]);

        // Destroys this shader.
        virtual ~Shader();

        // Starts the shader.
        inline void start();
        // Stops the shader.
        inline void stop();
        // Cleans up the memory used for this shader.
        inline void cleanUp();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        
            // Loads a float at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(float) value: The value to bind.
            inline void loadUniform(std::string location, const float value) const {
                loadFloat(locations_.at(location), value);
            }
            // Loads an int at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(int) value: The value to bind.
            inline void loadUniform(std::string location, const int value) const {
                loadInt(locations_.at(location), value);
            }
            // Loads a vector 2 at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(glm::vec2) value: The value to bind.
            inline void loadUniform(std::string location, const glm::vec2& value) const {
                loadVec2(locations_.at(location), value);
            }
            // Loads a vector 3 at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(glm::vec3) value: The value to bind.
            inline void loadUniform(std::string location, const glm::vec3& value) const {
                loadVec3(locations_.at(location), value);
            }
            // Loads a vector 4 at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(glm::vec4) value: The value to bind.
            inline void loadUniform(std::string location, const glm::vec4& value) const {
                loadVec4(locations_.at(location), value);
            }
            // Loads a bool at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(bool) value: The value to bind.
            inline void loadUniform(std::string location, const bool value) const {
                loadBool(locations_.at(location), value);
            }
            // Loads a 4x4 matrix at the specified location.
            // @param(std::string) location: The name of the location to bind to.
            // @param(glm::mat4) value: The value to bind.
            inline void loadUniform(std::string location, const glm::mat4& value) const {
                loadMat4(locations_.at(location), value);
            }

        // Check for Vulkan
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN


        // Check for DirectX
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX


        // Check for Metal
        #elif ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_METL


        #endif

    protected:
        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            std::map<std::string, unsigned int> locations_;

            // Gets the locations of all needed uniforms.
            // These locations are mapped by name and sstored in memory.
            // @param(std::string[]) uniforms: The names of the uniforms to store.
            void getAllUniformLocations(std::string[]);

            // Binds all needed attributes to the shader. These will be bound to the array index
            // that they were passed in.
            // @param(std::string[]) attributes: The attributes to bind.
            void bindAttributes(std::string[]);
            // TODO: Rework where bindAttributes and getAllUniformLocations are called

            // Gets the location of the specified uniform.
            // @param(std::string) uniform_name: The name of the uniform to check.
            // @returns: The location of the requested uniform.
            inline int getUniformLocation(std::string uniform_name) const {
                return glGetUniformLocation(program_id_, uniform_name.c_str());
            }

            // Binds the specified attribute to the shader.
            // @param(int) attribute: The attribute to bind.
            // @param(std::string) name: The name of the attirbute to bind.
            inline void bindAttribute(int attribute, std::string name) const {
                glBindAttribLocation(program_id_, attribute, name.c_str());
            }

            // Loads a float at the specified location.
            // @param(int) location: The location to bind to.
            // @param(float) value: The value to bind.
            inline void loadFloat(int location, const float value) const {
                glUniform1f(location, value);
            }
            // Loads an int at the specified location.
            // @param(int) location: The location to bind to.
            // @param(int) value: The value to bind.
            inline void loadInt(int location, const int value) const {
                glUniform1i(location, value);
            }
            // Loads a vector 2 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec2) value: The value to bind.
            inline void loadVec2(int location, const glm::vec2& value) const {
                glUniform2fv(location, 2, &value[0]);
            }
            // Loads a vector 3 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec3) value: The value to bind.
            inline void loadVec3(int location, const glm::vec3& value) const {
                glUniform3fv(location, 3, &value[0]);
            }
            // Loads a vector 4 at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::vec4) value: The value to bind.
            inline void loadVec4(int location, const glm::vec4& value) const {
                glUniform4fv(location, 4, &value[0]);
            }
            // Loads a bool at the specified location.
            // @param(int) location: The location to bind to.
            // @param(bool) value: The value to bind.
            inline void loadBool(int location, const bool value) const {
                glUniform1i(location, value);
            }
            // Loads a 4x4 matrix at the specified location.
            // @param(int) location: The location to bind to.
            // @param(glm::mat4) value: The value to bind.
            inline void loadMat4(int location, const glm::mat4& value) const {
                glUniformMatrix4fv(location, 1, false, &value[0][0]);
            }

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
            // The uniform buffer object identifier.
            int uniform_buffer_;
            // The vertex data bound to the shader in the UBO.
            shader_vertex_data_t vertex_data_;

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