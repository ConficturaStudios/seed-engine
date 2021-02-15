/**
 * Iterator.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ITERATOR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ITERATOR_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Iterator {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Iterator objects.
             * @details Constructs a new Iterator with default initialization for all members.
             */
            Iterator() {
                
            }

            /**
             * @brief The copy constructor for Iterator objects.
             * @details Constructs a new Iterator by copying an existing Iterator.
             */
            Iterator(const Iterator& ref) = default;
            
            /**
             * @brief The move constructor for Iterator objects.
             * @details Constructs a new Iterator by moving the data of a Iterator into this object.
             */
            Iterator(Iterator&& ref) = default;

            /**
             * @brief The destructor for Iterator objects.
             * @details Called when an instance of Iterator is deleted.
             */
            virtual ~Iterator() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Iterator objects.
             * @details Reassigns the value of this object by copying the data of a Iterator into this object.
             */
            Iterator& operator=(const Iterator& rhs) = default;

            /**
             * @brief The move assignment operator for Iterator objects.
             * @details Reassigns the value of this object by moving the data of a Iterator into this object.
             */
            Iterator& operator=(Iterator&& rhs) = default;

        protected:

        private:

    };

}

#endif