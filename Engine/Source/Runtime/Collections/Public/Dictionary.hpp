/**
 * Dictionary.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_DICTIONARY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_DICTIONARY_H_

#include "CollectionsAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class Dictionary {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Dictionary objects.
             * @details Constructs a new Dictionary with default initialization for all members.
             */
            Dictionary() {
                
            }

            /**
             * @brief The copy constructor for Dictionary objects.
             * @details Constructs a new Dictionary by copying an existing Dictionary.
             */
            Dictionary(const Dictionary& ref) = default;
            
            /**
             * @brief The move constructor for Dictionary objects.
             * @details Constructs a new Dictionary by moving the data of a Dictionary into this object.
             */
            Dictionary(Dictionary&& ref) = default;

            /**
             * @brief The destructor for Dictionary objects.
             * @details Called when an instance of Dictionary is deleted.
             */
            virtual ~Dictionary() {
                
            }

        // Functions



        // Assignment Operators

            /**
             * @brief The copy assignment operator for Dictionary objects.
             * @details Reassigns the value of this object by copying the data of a Dictionary into this object.
             */
            Dictionary& operator=(const Dictionary& rhs) = default;

            /**
             * @brief The move assignment operator for Dictionary objects.
             * @details Reassigns the value of this object by moving the data of a Dictionary into this object.
             */
            Dictionary& operator=(Dictionary&& rhs) = default;

        protected:

        private:

    };

}

#endif