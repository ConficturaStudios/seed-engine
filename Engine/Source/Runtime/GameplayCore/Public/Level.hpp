/**
 * Level.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_LEVEL_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_LEVEL_H_

#include "GameplayCoreAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Level {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Level objects.
             * @details Constructs a new Level with default initialization for all members.
             */
            Level();

            /**
             * @brief The copy constructor for Level objects.
             * @details Constructs a new Level by copying an existing Level.
             */
            Level(const Level& ref) = default;
            
            /**
             * @brief The move constructor for Level objects.
             * @details Constructs a new Level by moving the data of a Level into this object.
             */
            Level(Level&& ref) = default;

            /**
             * @brief The destructor for Level objects.
             * @details Called when an instance of Level is deleted.
             */
            virtual ~Level();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Level objects.
             * @details Reassigns the value of this object by copying the data of a Level into this object.
             */
            Level& operator=(const Level& ref) = default;

            /**
             * @brief The move assignment operator for Level objects.
             * @details Reassigns the value of this object by moving the data of a Level into this object.
             */
            Level& operator=(Level&& ref) = default;

        protected:

        private:

    };

}

#endif