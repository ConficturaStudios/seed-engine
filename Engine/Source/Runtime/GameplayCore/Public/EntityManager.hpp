/**
 * EntityManager.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_ENTITY_MANAGER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_ENTITY_MANAGER_H_

#include "GameplayCoreAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API EntityManager {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for EntityManager objects.
             * @details Constructs a new EntityManager with default initialization for all members.
             */
            EntityManager();

            /**
             * @brief The copy constructor for EntityManager objects.
             * @details Constructs a new EntityManager by copying an existing EntityManager.
             */
            EntityManager(const EntityManager& ref) = default;
            
            /**
             * @brief The move constructor for EntityManager objects.
             * @details Constructs a new EntityManager by moving the data of a EntityManager into this object.
             */
            EntityManager(EntityManager&& ref) = default;

            /**
             * @brief The destructor for EntityManager objects.
             * @details Called when an instance of EntityManager is deleted.
             */
            virtual ~EntityManager();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for EntityManager objects.
             * @details Reassigns the value of this object by copying the data of a EntityManager into this object.
             */
            EntityManager& operator=(const EntityManager& ref) = default;

            /**
             * @brief The move assignment operator for EntityManager objects.
             * @details Reassigns the value of this object by moving the data of a EntityManager into this object.
             */
            EntityManager& operator=(EntityManager&& ref) = default;

        protected:

        private:

    };

}

#endif