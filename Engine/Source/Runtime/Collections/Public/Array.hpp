/**
 * Array.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Array {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Array objects.
             * @details Constructs a new Array with default initialization for all members.
             */
            Array() {
                
            }

            /**
             * @brief The copy constructor for Array objects.
             * @details Constructs a new Array by copying an existing Array.
             */
            Array(const Array& ref) = default;
            
            /**
             * @brief The move constructor for Array objects.
             * @details Constructs a new Array by moving the data of a Array into this object.
             */
            Array(Array&& ref) = default;

            /**
             * @brief The destructor for Array objects.
             * @details Called when an instance of Array is deleted.
             */
            virtual ~Array() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Array objects.
             * @details Reassigns the value of this object by copying the data of a Array into this object.
             */
            Array& operator=(const Array& rhs) = default;

            /**
             * @brief The move assignment operator for Array objects.
             * @details Reassigns the value of this object by moving the data of a Array into this object.
             */
            Array& operator=(Array&& rhs) = default;

        protected:

        private:

    };

}

#endif