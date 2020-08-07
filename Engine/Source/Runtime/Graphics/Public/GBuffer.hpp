/**
 * GBuffer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_G_BUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_G_BUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API GBuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for GBuffer objects.
             * @details Constructs a new GBuffer with default initialization for all members.
             */
            GBuffer();

            /**
             * @brief The copy constructor for GBuffer objects.
             * @details Constructs a new GBuffer by copying an existing GBuffer.
             */
            GBuffer(const GBuffer& ref) = default;
            
            /**
             * @brief The move constructor for GBuffer objects.
             * @details Constructs a new GBuffer by moving the data of a GBuffer into this object.
             */
            GBuffer(GBuffer&& ref) = default;

            /**
             * @brief The destructor for GBuffer objects.
             * @details Called when an instance of GBuffer is deleted.
             */
            virtual ~GBuffer();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for GBuffer objects.
             * @details Reassigns the value of this object by copying the data of a GBuffer into this object.
             */
            GBuffer& operator=(const GBuffer& ref) = default;

            /**
             * @brief The move assignment operator for GBuffer objects.
             * @details Reassigns the value of this object by moving the data of a GBuffer into this object.
             */
            GBuffer& operator=(GBuffer&& ref) = default;

        protected:

        private:

    };

}

#endif