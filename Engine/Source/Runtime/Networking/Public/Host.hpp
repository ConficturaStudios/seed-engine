/**
 * Host.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_NETWORKING_HOST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_NETWORKING_HOST_H_

#include "NetworkingAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Host {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Host objects.
             * @details Constructs a new Host with default initialization for all members.
             */
            Host();

            /**
             * @brief The copy constructor for Host objects.
             * @details Constructs a new Host by copying an existing Host.
             */
            Host(const Host& ref) = default;
            
            /**
             * @brief The move constructor for Host objects.
             * @details Constructs a new Host by moving the data of a Host into this object.
             */
            Host(Host&& ref) = default;

            /**
             * @brief The destructor for Host objects.
             * @details Called when an instance of Host is deleted.
             */
            virtual ~Host();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Host objects.
             * @details Reassigns the value of this object by copying the data of a Host into this object.
             */
            Host& operator=(const Host& ref) = default;

            /**
             * @brief The move assignment operator for Host objects.
             * @details Reassigns the value of this object by moving the data of a Host into this object.
             */
            Host& operator=(Host&& ref) = default;

        protected:

        private:

    };

}

#endif