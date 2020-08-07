/**
 * Framebuffer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_FRAMEBUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_FRAMEBUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Framebuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Framebuffer objects.
             * @details Constructs a new Framebuffer with default initialization for all members.
             */
            Framebuffer();

            /**
             * @brief The copy constructor for Framebuffer objects.
             * @details Constructs a new Framebuffer by copying an existing Framebuffer.
             */
            Framebuffer(const Framebuffer& ref) = default;
            
            /**
             * @brief The move constructor for Framebuffer objects.
             * @details Constructs a new Framebuffer by moving the data of a Framebuffer into this object.
             */
            Framebuffer(Framebuffer&& ref) = default;

            /**
             * @brief The destructor for Framebuffer objects.
             * @details Called when an instance of Framebuffer is deleted.
             */
            virtual ~Framebuffer();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Framebuffer objects.
             * @details Reassigns the value of this object by copying the data of a Framebuffer into this object.
             */
            Framebuffer& operator=(const Framebuffer& ref) = default;

            /**
             * @brief The move assignment operator for Framebuffer objects.
             * @details Reassigns the value of this object by moving the data of a Framebuffer into this object.
             */
            Framebuffer& operator=(Framebuffer&& ref) = default;

        protected:

        private:

    };

}

#endif