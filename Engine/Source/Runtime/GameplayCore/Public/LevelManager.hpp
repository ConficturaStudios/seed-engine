/**
 * LevelManager.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_LEVEL_MANAGER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_LEVEL_MANAGER_H_

#include "GameplayCoreAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API LevelManager {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for LevelManager objects.
             * @details Constructs a new LevelManager with default initialization for all members.
             */
            LevelManager();

            /**
             * @brief The copy constructor for LevelManager objects.
             * @details Constructs a new LevelManager by copying an existing LevelManager.
             */
            LevelManager(const LevelManager& ref) = default;
            
            /**
             * @brief The move constructor for LevelManager objects.
             * @details Constructs a new LevelManager by moving the data of a LevelManager into this object.
             */
            LevelManager(LevelManager&& ref) = default;

            /**
             * @brief The destructor for LevelManager objects.
             * @details Called when an instance of LevelManager is deleted.
             */
            virtual ~LevelManager();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for LevelManager objects.
             * @details Reassigns the value of this object by copying the data of a LevelManager into this object.
             */
            LevelManager& operator=(const LevelManager& ref) = default;

            /**
             * @brief The move assignment operator for LevelManager objects.
             * @details Reassigns the value of this object by moving the data of a LevelManager into this object.
             */
            LevelManager& operator=(LevelManager&& ref) = default;

        protected:

        private:

    };

}

#endif