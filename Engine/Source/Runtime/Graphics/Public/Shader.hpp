/**
 * Shader.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_SHADER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_SHADER_H_

#include "GraphicsAPI.hpp"
#include "String.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix.hpp"
#include "SmartPointer.hpp"
#include "Texture.hpp"

namespace seedengine {

    /**
     * @brief A shader program to by run by the rendering pipeline.
     * @details
     * A shader program that is run within the rendering pipeline. The implementation
     * of this program is determined by the active graphics framework such as OpenGL or DirectX.
     * 
     * Shaders may only be instanced through the factory method Shader::Create(...), and will
     * be created using the appropriate implementation. The implementation used is meant to
     * remain ambiguous to end users in terms of functionality.
     * 
     */
    class ENGINE_API Shader {

        public:

        // Destructor

            /**
             * @brief The destructor for Shader objects.
             * @details Called when an instance of Shader is deleted.
             */
            virtual ~Shader();

        // Factory

            /**
             * @brief Creates a new Shader object.
             * @details
             * Creates a new Shader object using the framework specific implementation
             * of the current graphics system (OpenGL, DirectX, etc.).
             * 
             * @param filepath The path to the shader to use.
             * 
             * @return SharedPtr<Shader> A pointer to the new shader.
             */
            [[nodiscard]] static SharedPtr<Shader> Create(const String& filepath);

            /**
             * @brief Creates a new Shader object.
             * @details
             * Creates a new Shader object using the framework specific implementation
             * of the current graphics system (OpenGL, DirectX, etc.).
             * 
             * @param name The name of the shader to create.
             * @param vs_filepath The path to the vertex shader to use.
             * @param fs_filepath The path to the fragment shader to use.
             * 
             * @return SharedPtr<Shader> A pointer to the new shader.
             */
            [[nodiscard]] static SharedPtr<Shader> Create(const String& name, const String& vs_filepath, const String& fs_filepath);

        // Functions

            /** @brief Starts this shader program. */
            virtual void bind() = 0;
            /** Stops this shader program. */
            virtual void unbind() = 0;

        // Load Scalar Parameters

            virtual void setParameter(const String& name, bool value) = 0;

            virtual void setParameter(const String& name, int32_t value) = 0;
            virtual void setParameter(const String& name, uint32_t value) = 0;

            virtual void setParameter(const String& name, float value) = 0;

        // Load Vector Parameters

            virtual void setParameter(const String& name, const Vector2& value) = 0;
            virtual void setParameter(const String& name, const Vector3& value) = 0;
            virtual void setParameter(const String& name, const Vector4& value) = 0;

            virtual void setParameter(const String& name, const Vector2Int& value) = 0;
            virtual void setParameter(const String& name, const Vector3Int& value) = 0;
            virtual void setParameter(const String& name, const Vector4Int& value) = 0;

        // Load Matrix Parameters

            virtual void setParameter(const String& name, const Matrix2x2& value) = 0;
            virtual void setParameter(const String& name, const Matrix2x3& value) = 0;
            virtual void setParameter(const String& name, const Matrix2x4& value) = 0;

            virtual void setParameter(const String& name, const Matrix3x2& value) = 0;
            virtual void setParameter(const String& name, const Matrix3x3& value) = 0;
            virtual void setParameter(const String& name, const Matrix3x4& value) = 0;

            virtual void setParameter(const String& name, const Matrix4x2& value) = 0;
            virtual void setParameter(const String& name, const Matrix4x3& value) = 0;
            virtual void setParameter(const String& name, const Matrix4x4& value) = 0;

        // Load Texture Parameters

            virtual void setParameter(const String& name, const Texture& value) = 0;

        // Cast Operators

            [[nodiscard]] virtual operator bool() const noexcept = 0;

        protected:

            /**
             * @brief Attempts to initialize this shader.
             * 
             * @param filepath The path to the shader to load.
             * @return true If initialization is successful.
             * @return false If initialization fails.
             */
            [[nodiscard]] virtual bool init(const String& filepath) = 0;
            /**
             * @brief Attempts to initialize this shader.
             * 
             * @param name The name of the shader to initialize.
             * @param vs_filepath The path to the vertex shader to load.
             * @param fs_filepath The path to the fragment shader to load.
             * @return true If initialization is successful.
             * @return false If initialization fails.
             */
            [[nodiscard]] virtual bool init(const String& name, const String& vs_filepath, const String& fs_filepath) = 0;

            /** Used to clean up shader memory. */
            virtual void cleanUp() = 0;

        private:

    };

}

#endif