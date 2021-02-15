/**
 * Pair.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_PAIR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_PAIR_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Pair {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Pair objects.
             * @details Constructs a new Pair with default initialization for all members.
             */
            Pair() {
                
            }

            /**
             * @brief The copy constructor for Pair objects.
             * @details Constructs a new Pair by copying an existing Pair.
             */
            Pair(const Pair& ref) = default;
            
            /**
             * @brief The move constructor for Pair objects.
             * @details Constructs a new Pair by moving the data of a Pair into this object.
             */
            Pair(Pair&& ref) = default;

            /**
             * @brief The destructor for Pair objects.
             * @details Called when an instance of Pair is deleted.
             */
            virtual ~Pair() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Pair objects.
             * @details Reassigns the value of this object by copying the data of a Pair into this object.
             */
            Pair& operator=(const Pair& rhs) = default;

            /**
             * @brief The move assignment operator for Pair objects.
             * @details Reassigns the value of this object by moving the data of a Pair into this object.
             */
            Pair& operator=(Pair&& rhs) = default;

        protected:

        private:

    };

}

#endif