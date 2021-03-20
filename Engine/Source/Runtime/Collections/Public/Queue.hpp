/**
 * @file Queue.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_QUEUE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_QUEUE_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class Queue {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Queue objects.
             * @details Constructs a new Queue with default initialization for all members.
             */
            Queue() {
                
            }

            /**
             * @brief The copy constructor for Queue objects.
             * @details Constructs a new Queue by copying an existing Queue.
             */
            Queue(const Queue& ref) = default;
            
            /**
             * @brief The move constructor for Queue objects.
             * @details Constructs a new Queue by moving the data of a Queue into this object.
             */
            Queue(Queue&& ref) noexcept = default;

            /**
             * @brief The destructor for Queue objects.
             * @details Called when an instance of Queue is deleted.
             */
            virtual ~Queue() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Queue objects.
             * @details Reassigns the value of this object by copying the data of a Queue into this object.
             */
            Queue& operator=(const Queue& rhs) = default;

            /**
             * @brief The move assignment operator for Queue objects.
             * @details Reassigns the value of this object by moving the data of a Queue into this object.
             */
            Queue& operator=(Queue&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif