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
             * @brief The copy constructor for Renderer objects.
             * @details Constructs a new Renderer by copying an existing Renderer.
             */
            Renderer(const Renderer& ref) = default;
            
            /**
             * @brief The move constructor for Renderer objects.
             * @details Constructs a new Renderer by moving the data of a Renderer into this object.
             */
            Renderer(Renderer&& ref) noexcept = default;

            /**
             * @brief The destructor for Renderer objects.
             * @details Called when an instance of Renderer is deleted.
             */
            virtual ~Renderer();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Renderer objects.
             * @details Reassigns the value of this object by copying the data of a Renderer into this object.
             */
            Renderer& operator=(const Renderer& rhs) = default;

            /**
             * @brief The move assignment operator for Renderer objects.
             * @details Reassigns the value of this object by moving the data of a Renderer into this object.
             */
            Renderer& operator=(Renderer&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif