/**
 * @file Stack.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_STACK_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_STACK_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class Stack {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Stack objects.
             * @details Constructs a new Stack with default initialization for all members.
             */
            Stack() {
                
            }

            /**
             * @brief The copy constructor for Stack objects.
             * @details Constructs a new Stack by copying an existing Stack.
             */
            Stack(const Stack& ref) = default;
            
            /**
             * @brief The move constructor for Stack objects.
             * @details Constructs a new Stack by moving the data of a Stack into this object.
             */
            Stack(Stack&& ref) noexcept = default;

            /**
             * @brief The destructor for Stack objects.
             * @details Called when an instance of Stack is deleted.
             */
            virtual ~Stack() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Stack objects.
             * @details Reassigns the value of this object by copying the data of a Stack into this object.
             */
            Stack& operator=(const Stack& rhs) = default;

            /**
             * @brief The move assignment operator for Stack objects.
             * @details Reassigns the value of this object by moving the data of a Stack into this object.
             */
            Stack& operator=(Stack&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif