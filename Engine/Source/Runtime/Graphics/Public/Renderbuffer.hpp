/**
 * @file Renderbuffer.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_RENDERBUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_RENDERBUFFER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Renderbuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Renderbuffer objects.
             * @details Constructs a new Renderbuffer with default initialization for all members.
             */
            Renderbuffer();

            /**
             * @brief The copy constructor for Renderbuffer objects.
             * @details Constructs a new Renderbuffer by copying an existing Renderbuffer.
             */
            Renderbuffer(const Renderbuffer& ref) = default;
            
            /**
             * @brief The move constructor for Renderbuffer objects.
             * @details Constructs a new Renderbuffer by moving the data of a Renderbuffer into this object.
             */
            Renderbuffer(Renderbuffer&& ref) noexcept = default;

            /**
             * @brief The destructor for Renderbuffer objects.
             * @details Called when an instance of Renderbuffer is deleted.
             */
            virtual ~Renderbuffer();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Renderbuffer objects.
             * @details Reassigns the value of this object by copying the data of a Renderbuffer into this object.
             */
            Renderbuffer& operator=(const Renderbuffer& rhs) = default;

            /**
             * @brief The move assignment operator for Renderbuffer objects.
             * @details Reassigns the value of this object by moving the data of a Renderbuffer into this object.
             */
            Renderbuffer& operator=(Renderbuffer&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif