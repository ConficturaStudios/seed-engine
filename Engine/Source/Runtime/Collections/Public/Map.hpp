/**
 * Map.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_MAP_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_MAP_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Map {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Map objects.
             * @details Constructs a new Map with default initialization for all members.
             */
            Map() {
                
            }

            /**
             * @brief The copy constructor for Map objects.
             * @details Constructs a new Map by copying an existing Map.
             */
            Map(const Map& ref) = default;
            
            /**
             * @brief The move constructor for Map objects.
             * @details Constructs a new Map by moving the data of a Map into this object.
             */
            Map(Map&& ref) = default;

            /**
             * @brief The destructor for Map objects.
             * @details Called when an instance of Map is deleted.
             */
            virtual ~Map() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Map objects.
             * @details Reassigns the value of this object by copying the data of a Map into this object.
             */
            Map& operator=(const Map& rhs) = default;

            /**
             * @brief The move assignment operator for Map objects.
             * @details Reassigns the value of this object by moving the data of a Map into this object.
             */
            Map& operator=(Map&& rhs) = default;

        protected:

        private:

    };

}

#endif