/**
 * @file Renderer.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_RENDERER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_RENDERER_H_

#include "GraphicsAPI.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Color.hpp"
#include "Framebuffer.hpp"
#include "Shader.hpp"

namespace seedengine {

    /**
     * @brief The base class for a graphics framework specific renderer implementation.
     * @details
     * 
     */
    class ENGINE_API Renderer {

            // TODO: Document Renderer class
            // TODO: Complete OpenGLRenderer class
            // TODO: Create LevelRenderer in EngineCore

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Renderer objects.
             * @details Constructs a new Renderer with default initialization for all members.
             */
            Renderer();

            /**
             * @brief The destructor for Renderer objects.
             * @details Called when an instance of Renderer is deleted.
             */
            virtual ~Renderer();

            /**
             * Called when this Renderer is created, implementation specific. This method
             * is responsible for initializing the current graphics api.
             */
            virtual void startup() = 0;

            /**
             * Called when this Renderer is destroyed, implementation specific. This method
             * is responsible for shutting down the current graphics api.
             */
            virtual void shutdown() = 0;

            /**
             * Clears the screen of all currently rendered objects and fills the screen with the clear color.
             */
            virtual void clear() = 0;
            /**
             * Sets the color that the screen will clear to upon refresh.
             * @param color The clear color.
             */
            virtual void setClearColor(const LinearColor& color);

            /**
             * Set to true to enable depth testing, false to disable.
             * @param state the state to set the useDepthTest flag to.
             */
            virtual void setUseDepthTest(bool state);
            /**
             * Set to true to enable backface culling, false to disable.
             * @param state the state to set the useBackfaceCulling flag to.
             */
            virtual void setUseBackfaceCulling(bool state);

            /**
             * Binds the specified shader to the renderer.
             * @param shader The shader to bind.
             */
            virtual void bindShader(const Shader& shader);
            /**
             * Binds the specified mesh to the renderer.
             * @param mesh The mesh to bind.
             */
            virtual void bindMesh(const Mesh& mesh);
            /**
             * Binds the specified material to the renderer.
             * @param material The material to bind.
             */
            virtual void bindMaterial(const Material& material);

            /**
             * Unbinds the currently active shader from the renderer.
             */
            virtual void unbindShader();
            /**
             * Unbinds the currently active mesh from the renderer.
             */
            virtual void unbindMesh();
            /**
             * Unbinds the currently active material from the renderer.
             */
            virtual void unbindMaterial();

            // This could be used for visibility flags and other object instance data?
            //virtual void setCurrentRenderProperties(const RenderProperties& properties) = 0;

            /**
             * Draws the currently bound data to the screen.
             */
            virtual void drawCurrent() = 0;

            /**
             * Binds the specified texture into the next available texture slot.
             * @param texture The texture to bind.
             */
            virtual void bindTexture(const Texture& texture);
            /**
             * Unbinds all textures from the renderer.
             */
            virtual void clearTextures();

        private:

            /** Is backface culling enabled? */
            bool m_useBackfaceCulling = true;
            /** Is depth testing enabled? */
            bool m_useDepth = true;

        protected:

            /** The clear color applied to the screen upon refresh. */
            LinearColor m_clearColor = LinearColor::clear;

            /** The currently active shader. */
            const Shader* m_currentShader = nullptr;
            /** The currently active mesh. */
            const Mesh* m_currentMesh = nullptr;
            /** The currently active material. */
            const Material* m_currentMaterial = nullptr;

            /** A list of all currently bound textures. */
            List<const Texture*>* m_textures;
            /** The number of texture slots currently bound. */
            uint32 m_filledTextureSlots = 0;

    };

}

#endif