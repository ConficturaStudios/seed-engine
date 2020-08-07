/**
 * Terrain.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_ENVIRONMENT_TERRAIN_H_
#define SEEDENGINE_INCLUDE_RUNTIME_ENVIRONMENT_TERRAIN_H_

#include "EnvironmentAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Terrain {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Terrain objects.
             * @details Constructs a new Terrain with default initialization for all members.
             */
            Terrain();

            /**
             * @brief The copy constructor for Terrain objects.
             * @details Constructs a new Terrain by copying an existing Terrain.
             */
            Terrain(const Terrain& ref) = default;
            
            /**
             * @brief The move constructor for Terrain objects.
             * @details Constructs a new Terrain by moving the data of a Terrain into this object.
             */
            Terrain(Terrain&& ref) = default;

            /**
             * @brief The destructor for Terrain objects.
             * @details Called when an instance of Terrain is deleted.
             */
            virtual ~Terrain();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Terrain objects.
             * @details Reassigns the value of this object by copying the data of a Terrain into this object.
             */
            Terrain& operator=(const Terrain& ref) = default;

            /**
             * @brief The move assignment operator for Terrain objects.
             * @details Reassigns the value of this object by moving the data of a Terrain into this object.
             */
            Terrain& operator=(Terrain&& ref) = default;

        protected:

        private:

    };

}

#endif