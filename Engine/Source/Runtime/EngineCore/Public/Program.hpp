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
     * @brief The main program class instanced and run by the client application.
     * @details The Program class is responsible for instancing and running the main game loop
     *          and the initialization of all other program paths. A Program object should be
     *          created by the client application, and allowed to perform its run method on another
     *          thread.
     *          Additionally, any gameplay data needed at runtime should be passed to this object
     *          from the hosting thread.
     *          When runtime is complete, the Prgoram will handle memory cleanup and return
     *          information about the program execution and success back to the client.
     */
    class ENGINE_API Program final {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Program objects.
             * @details Constructs a new Program with default initialization for all members.
             */
            Program();

            /**
             * @brief (Deleted) The copy constructor for Program objects.
             * @details (Deleted) Constructs a new Program by copying an existing Program.
             */
            Program(const Program& ref) = delete;
            
            /**
             * @brief (Deleted) The move constructor for Program objects.
             * @details (Deleted) Constructs a new Program by moving the data of a Program into
             *          this object.
             */
            Program(Program&& ref) = delete;

            /**
             * @brief The destructor for Program objects.
             * @details Called when an instance of Program is deleted.
             */
            ~Program();

        // Functions

            /**
             * @brief Runs the program's main logic loop, returning an exit code.
             * 
             * @return int The exit status of the program.
             */
            int run();

        // Operators

            /**
             * @brief (Deleted) The copy assignment operator for Program objects.
             * @details (Deleted) Reassigns the value of this object by copying the data of a
             *          Program into this object.
             */
            Program& operator=(const Program& ref) = delete;

            /**
             * @brief (Deleted) The move assignment operator for Program objects.
             * @details (Deleted) Reassigns the value of this object by moving the data of a
             *          Program into this object.
             */
            Program& operator=(Program&& ref) = delete;

        private:

    };

}

#endif