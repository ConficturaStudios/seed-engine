/**
 * OpenGLShader.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_SHADER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_SHADER_H_

#include "GraphicsAPI.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Shader.hpp"
#include "String.hpp"
#include <iostream>
#include <vector>

namespace seedengine {

    #if ENGINE_GRAPHICS_OPENGL

    /**
     * @brief
     * @details
     * 
     */
    class OpenGLShader : public Shader {

        friend class Shader;

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for OpenGLShader objects.
             * @details Constructs a new OpenGLShader with default initialization for all members.
             */
            OpenGLShader();

            /**
             * @brief The destructor for OpenGLShader objects.
             * @details Called when an instance of OpenGLShader is deleted.
             */
            virtual ~OpenGLShader();

        // Functions

            /** @brief Starts this shader program. */
            void bind() override;
            /** Stops this shader program. */
            void unbind() override;

        // Load Scalar Parameters

            void setParameter(const String& name, bool value) override;

            void setParameter(const String& name, int32_t value) override;
            void setParameter(const String& name, uint32_t value) override;

            void setParameter(const String& name, float value) override;

        // Load Vector Parameters

            void setParameter(const String& name, const Vector2& value) override;
            void setParameter(const String& name, const Vector3& value) override;
            void setParameter(const String& name, const Vector4& value) override;

            void setParameter(const String& name, const Vector2Int& value) override;
            void setParameter(const String& name, const Vector3Int& value) override;
            void setParameter(const String& name, const Vector4Int& value) override;

        // Load Matrix Parameters

            void setParameter(const String& name, const Matrix2x2& value) override;
            void setParameter(const String& name, const Matrix2x3& value) override;
            void setParameter(const String& name, const Matrix2x4& value) override;

            void setParameter(const String& name, const Matrix3x2& value) override;
            void setParameter(const String& name, const Matrix3x3& value) override;
            void setParameter(const String& name, const Matrix3x4& value) override;

            void setParameter(const String& name, const Matrix4x2& value) override;
            void setParameter(const String& name, const Matrix4x3& value) override;
            void setParameter(const String& name, const Matrix4x4& value) override;

        // Load Texture Parameters

            void setParameter(const String& name, const Texture& value) override;

        // Cast Operators

            [[nodiscard]] virtual operator bool() const noexcept override;

        protected:

            /**
             * @brief Attempts to initialize this shader.
             * 
             * @param filepath The path to the shader to load.
             * @return true If initialization is successful.
             * @return false If initialization fails.
             */
            [[nodiscard]] bool init(const String& filepath) override;
            /**
             * @brief Attempts to initialize this shader.
             * 
             * @param name The name of the shader to initialize.
             * @param vs_filepath The path to the vertex shader to load.
             * @param fs_filepath The path to the fragment shader to load.
             * @return true If initialization is successful.
             * @return false If initialization fails.
             */
            [[nodiscard]] bool init(const String& name, const String& vs_filepath, const String& fs_filepath) override;

            /** Used to clean up shader memory. */
            void cleanUp() override;

            /**
             * @brief Gets the location of a uniform by name.
             * 
             * @param name The name of the uniform to look up.
             * @return GLint The location of the uniform.
             */
            [[nodiscard]] GLint getUniformLocation(const String& name) const;

            /**
             * @brief Binds the provided attribute name to the provided attribute index.
             * 
             * @param attribute The index to bind to.
             * @param name The name to bind.
             */
            void bindAttribute(const GLuint& attribute, const String& name) const;


        private:

            /** Was this shader initialized successfully? */
            bool m_initialized;
            /** Is this shader running? */
            bool m_running;

            /** The name of this shader. */
            String m_name;
        
            /** The ID of this shader in memory. */
            GLuint m_program_id;
            /** The ID of this shader's vertex shader. */
            GLuint m_vertex_shader_id;
            /** The ID of this shader's fragment shader. */
            GLuint m_fragment_shader_id;

            /** The uniform buffer object identifier. */
            //GLuint m_uniform_buffer;

            /**
             * @brief Loads a shader from the disk.
             * 
             * @param filepath The path to the file to load from.
             * @param shader_type The type of shader being loaded.
             * @return GLuint The ID of the shader in memory.
             */
            [[nodiscard]] static GLuint loadShader(const String& filepath, const GLenum& shader_type);

    };

    #else

    class OpenGLShader : public Shader {

    };

    #endif

}

#endif