/**
 * LinkedList.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LINKED_LIST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LINKED_LIST_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API LinkedList {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for LinkedList objects.
             * @details Constructs a new LinkedList with default initialization for all members.
             */
            LinkedList() {
                
            }

            /**
             * @brief The copy constructor for LinkedList objects.
             * @details Constructs a new LinkedList by copying an existing LinkedList.
             */
            LinkedList(const LinkedList& ref) = default;
            
            /**
             * @brief The move constructor for LinkedList objects.
             * @details Constructs a new LinkedList by moving the data of a LinkedList into this object.
             */
            LinkedList(LinkedList&& ref) = default;

            /**
             * @brief The destructor for LinkedList objects.
             * @details Called when an instance of LinkedList is deleted.
             */
            virtual ~LinkedList() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for LinkedList objects.
             * @details Reassigns the value of this object by copying the data of a LinkedList into this object.
             */
            LinkedList& operator=(const LinkedList& rhs) = default;

            /**
             * @brief The move assignment operator for LinkedList objects.
             * @details Reassigns the value of this object by moving the data of a LinkedList into this object.
             */
            LinkedList& operator=(LinkedList&& rhs) = default;

        protected:

        private:

    };

}

#endif