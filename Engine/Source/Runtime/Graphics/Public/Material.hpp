/**
 * @file Material.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MATERIAL_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MATERIAL_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Material {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Material objects.
             * @details Constructs a new Material with default initialization for all members.
             */
            Material();

            /**
             * @brief The copy constructor for Material objects.
             * @details Constructs a new Material by copying an existing Material.
             */
            Material(const Material& ref) = default;
            
            /**
             * @brief The move constructor for Material objects.
             * @details Constructs a new Material by moving the data of a Material into this object.
             */
            Material(Material&& ref) noexcept = default;

            /**
             * @brief The destructor for Material objects.
             * @details Called when an instance of Material is deleted.
             */
            virtual ~Material();

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Material objects.
             * @details Reassigns the value of this object by copying the data of a Material into this object.
             */
            Material& operator=(const Material& rhs) = default;

            /**
             * @brief The move assignment operator for Material objects.
             * @details Reassigns the value of this object by moving the data of a Material into this object.
             */
            Material& operator=(Material&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif