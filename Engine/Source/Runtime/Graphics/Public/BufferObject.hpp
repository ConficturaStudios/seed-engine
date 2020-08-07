/**
 * BufferObject.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_BUFFER_OBJECT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_BUFFER_OBJECT_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API BufferObject {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for BufferObject objects.
             * @details Constructs a new BufferObject with default initialization for all members.
             */
            BufferObject();

            /**
             * @brief The copy constructor for BufferObject objects.
             * @details Constructs a new BufferObject by copying an existing BufferObject.
             */
            BufferObject(const BufferObject& ref) = default;
            
            /**
             * @brief The move constructor for BufferObject objects.
             * @details Constructs a new BufferObject by moving the data of a BufferObject into this object.
             */
            BufferObject(BufferObject&& ref) = default;

            /**
             * @brief The destructor for BufferObject objects.
             * @details Called when an instance of BufferObject is deleted.
             */
            virtual ~BufferObject();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for BufferObject objects.
             * @details Reassigns the value of this object by copying the data of a BufferObject into this object.
             */
            BufferObject& operator=(const BufferObject& ref) = default;

            /**
             * @brief The move assignment operator for BufferObject objects.
             * @details Reassigns the value of this object by moving the data of a BufferObject into this object.
             */
            BufferObject& operator=(BufferObject&& ref) = default;

        protected:

        private:

    };

}

#endif