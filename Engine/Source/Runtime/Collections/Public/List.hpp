/**
 * List.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LIST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LIST_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API List {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for List objects.
             * @details Constructs a new List with default initialization for all members.
             */
            List() {
                
            }

            /**
             * @brief The copy constructor for List objects.
             * @details Constructs a new List by copying an existing List.
             */
            List(const List& ref) = default;
            
            /**
             * @brief The move constructor for List objects.
             * @details Constructs a new List by moving the data of a List into this object.
             */
            List(List&& ref) = default;

            /**
             * @brief The destructor for List objects.
             * @details Called when an instance of List is deleted.
             */
            virtual ~List() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for List objects.
             * @details Reassigns the value of this object by copying the data of a List into this object.
             */
            List& operator=(const List& rhs) = default;

            /**
             * @brief The move assignment operator for List objects.
             * @details Reassigns the value of this object by moving the data of a List into this object.
             */
            List& operator=(List&& rhs) = default;

        protected:

        private:

    };

}

#endif