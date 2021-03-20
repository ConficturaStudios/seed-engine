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

#ifndef SEEDENGINE_INCLUDE_RUNTIME_RENDERING_RENDERER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_RENDERING_RENDERER_H_

#include "RenderingAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Renderer {

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

        // Static Functions

            [[nodiscard]] static GraphicsMode GetGraphicsAPI();

        protected:

        private:

    };

}

#endif