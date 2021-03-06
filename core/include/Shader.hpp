#ifndef SEEDENGINE_INCLUDE_SHADER_H_
#define SEEDENGINE_INCLUDE_SHADER_H_

#include "Core.hpp"

namespace seedengine {

    /**
     * @brief The data necessary to render a vertex in 3D space.
     * 
     */
    struct shader_vertex_data_t {
        float transformation_mat[16];
        float projection_mat[16];
        float view_mat[16];
    };

    //TODO: Convert Shader class into an asset
    //TODO: Rework shader data into a single file, parse for vertex, pixel/fragment, etc.
    //TODO: Create Material asset class

    /**
     * @brief A shader asset that can be loaded from the disk and used within
     *        the rendering pipeline.
     * @details
     */
    class Shader {
        
    public:

        /**
         * @brief Constructs a new Shader.
         * 
         * @param vertex_shader_path The path to the vertex shader used by this shader.
         * @param fragment_shader_path The path to the fragment shader used by this shader.
         * @param attributes The attributes to bind.
         * @param uniforms The names of the uniforms to store.
         */
        Shader(string vertex_shader_path, string fragment_shader_path,
               std::vector<string> attributes, std::vector<string> uniforms);

        /** Destroys this shader. */
        virtual ~Shader();

        /** Starts the shader. */
        void start();
        /** Stops the shader. */
        void stop();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

        //TODO: Migrate loadUniform into load paramater generic functionality
        
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const float value) const {
                loadFloat(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const int value) const {
                loadInt(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const glm::vec2& value) const {
                loadVec2(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const glm::vec3& value) const {
                loadVec3(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const glm::vec4& value) const {
                loadVec4(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const bool value) const {
                loadBool(locations_.at(location), value);
            }
            /**
             * @brief Loads a uniform at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadUniform(string location, const glm::mat4& value) const {
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

        bool initialized_;

        /** Cleans up the memory used for this shader. */
        void cleanUp();

        // Check for OpenGL
        #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL

            std::map<string, unsigned int> locations_ = std::map<string, unsigned int>();

            /**
             * @brief Gets the locations of all needed uniforms.
             *        These locations are mapped by name and stored in memory.
             * 
             * @param uniforms The names of the uniforms to store.
             */
            void getAllUniformLocations(std::vector<string> uniforms);

            /**
             * @brief Binds all needed attributes to the shader. These will be bound to the
             *        array index that they were passed in.
             * 
             * @param attributes The attributes to bind.
             */
            void bindAttributes(std::vector<string> attributes);
            // TODO: Rework where bindAttributes and getAllUniformLocations are called

            /**
             * @brief Gets the location of the specified uniform.
             * 
             * @param uniform_name The name of the uniform to check.
             * @return int The location of the requested uniform.
             */
            inline int getUniformLocation(string uniform_name) const {
                return glGetUniformLocation(program_id_, uniform_name.c_str());
            }

            /**
             * @brief Binds the specified attribute to the shader.
             * 
             * @param attribute The attribute to bind.
             * @param name The name of the attirbute to bind.
             */
            inline void bindAttribute(int attribute, string name) const {
                glBindAttribLocation(program_id_, attribute, name.c_str());
            }

            /**
             * @brief Loads a float at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadFloat(int location, const float value) const {
                glUniform1f(location, value);
            }
            /**
             * @brief Loads an int at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadInt(int location, const int value) const {
                glUniform1i(location, value);
            }
            /**
             * @brief Loads a vector 2 at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadVec2(int location, const glm::vec2& value) const {
                glUniform2fv(location, 2, &value[0]);
            }
            /**
             * @brief Loads a vector 3 at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadVec3(int location, const glm::vec3& value) const {
                glUniform3fv(location, 3, &value[0]);
            }
            /**
             * @brief Loads a vector 4 at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadVec4(int location, const glm::vec4& value) const {
                glUniform4fv(location, 4, &value[0]);
            }
            /**
             * @brief Loads a bool at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
            inline void loadBool(int location, const bool value) const {
                glUniform1i(location, value);
            }
            /**
             * @brief Loads a 4x4 matrix at the specified location.
             * 
             * @param location The location to bind to.
             * @param value The value to bind.
             */
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
        
            /** The ID of this shader in memory. */
            int program_id_;
            /** The ID of this shader's vertex shader. */
            int vertex_shader_id_;
            /** The ID of this shader's fragment shader. */
            int fragment_shader_id_;
            /** The uniform buffer object identifier. */
            int uniform_buffer_;
            /** The vertex data bound to the shader in the UBO. */
            shader_vertex_data_t vertex_data_;

            /**
             * @brief Loads a shader from the disk.
             * 
             * @param file The path to the file to load from.
             * @param shader_type The type of shader being loaded.
             * @return int The ID of the shader in memory.
             */
            static int loadShader(string file, int shader_type);

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