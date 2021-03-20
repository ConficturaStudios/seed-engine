/**
 * ArrayList.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_LIST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_LIST_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ArrayList {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for ArrayList objects.
             * @details Constructs a new ArrayList with default initialization for all members.
             */
            ArrayList() {
                
            }

            /**
             * @brief The copy constructor for ArrayList objects.
             * @details Constructs a new ArrayList by copying an existing ArrayList.
             */
            ArrayList(const ArrayList& ref) = default;
            
            /**
             * @brief The move constructor for ArrayList objects.
             * @details Constructs a new ArrayList by moving the data of a ArrayList into this object.
             */
            ArrayList(ArrayList&& ref) = default;

            /**
             * @brief The destructor for ArrayList objects.
             * @details Called when an instance of ArrayList is deleted.
             */
            virtual ~ArrayList() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for ArrayList objects.
             * @details Reassigns the value of this object by copying the data of a ArrayList into this object.
             */
            ArrayList& operator=(const ArrayList& rhs) = default;

            /**
             * @brief The move assignment operator for ArrayList objects.
             * @details Reassigns the value of this object by moving the data of a ArrayList into this object.
             */
            ArrayList& operator=(ArrayList&& rhs) = default;

        protected:

        private:

    };

}

#endif