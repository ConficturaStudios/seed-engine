/**
 * Program.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_PROGRAM_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ENGINE_CORE_PROGRAM_H_

#include "EngineCoreAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Program {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Program objects.
             * @details Constructs a new Program with default initialization for all members.
             */
            Program();

            /**
             * @brief The copy constructor for Program objects.
             * @details Constructs a new Program by copying an existing Program.
             */
            Program(const Program& ref) = default;
            
            /**
             * @brief The move constructor for Program objects.
             * @details Constructs a new Program by moving the data of a Program into this object.
             */
            Program(Program&& ref) = default;

            /**
             * @brief The destructor for Program objects.
             * @details Called when an instance of Program is deleted.
             */
            virtual ~Program();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Program objects.
             * @details Reassigns the value of this object by copying the data of a Program into this object.
             */
            Program& operator=(const Program& ref) = default;

            /**
             * @brief The move assignment operator for Program objects.
             * @details Reassigns the value of this object by moving the data of a Program into this object.
             */
            Program& operator=(Program&& ref) = default;

        protected:

        private:

    };

}

#endif