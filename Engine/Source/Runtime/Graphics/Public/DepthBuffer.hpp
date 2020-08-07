/**
 * DepthBuffer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DEPTH_BUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DEPTH_BUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API DepthBuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for DepthBuffer objects.
             * @details Constructs a new DepthBuffer with default initialization for all members.
             */
            DepthBuffer();

            /**
             * @brief The copy constructor for DepthBuffer objects.
             * @details Constructs a new DepthBuffer by copying an existing DepthBuffer.
             */
            DepthBuffer(const DepthBuffer& ref) = default;
            
            /**
             * @brief The move constructor for DepthBuffer objects.
             * @details Constructs a new DepthBuffer by moving the data of a DepthBuffer into this object.
             */
            DepthBuffer(DepthBuffer&& ref) = default;

            /**
             * @brief The destructor for DepthBuffer objects.
             * @details Called when an instance of DepthBuffer is deleted.
             */
            virtual ~DepthBuffer();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for DepthBuffer objects.
             * @details Reassigns the value of this object by copying the data of a DepthBuffer into this object.
             */
            DepthBuffer& operator=(const DepthBuffer& ref) = default;

            /**
             * @brief The move assignment operator for DepthBuffer objects.
             * @details Reassigns the value of this object by moving the data of a DepthBuffer into this object.
             */
            DepthBuffer& operator=(DepthBuffer&& ref) = default;

        protected:

        private:

    };

}

#endif