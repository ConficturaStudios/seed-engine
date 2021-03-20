/**
 * Tree.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_TREE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_TREE_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class Tree {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Tree objects.
             * @details Constructs a new Tree with default initialization for all members.
             */
            Tree() {
                
            }

            /**
             * @brief The copy constructor for Tree objects.
             * @details Constructs a new Tree by copying an existing Tree.
             */
            Tree(const Tree& ref) = default;
            
            /**
             * @brief The move constructor for Tree objects.
             * @details Constructs a new Tree by moving the data of a Tree into this object.
             */
            Tree(Tree&& ref) = default;

            /**
             * @brief The destructor for Tree objects.
             * @details Called when an instance of Tree is deleted.
             */
            virtual ~Tree() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Tree objects.
             * @details Reassigns the value of this object by copying the data of a Tree into this object.
             */
            Tree& operator=(const Tree& rhs) = default;

            /**
             * @brief The move assignment operator for Tree objects.
             * @details Reassigns the value of this object by moving the data of a Tree into this object.
             */
            Tree& operator=(Tree&& rhs) = default;

        protected:

        private:

    };

}

#endif