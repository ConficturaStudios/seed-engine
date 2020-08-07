/**
 * JsonData.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_JSON_DATA_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_JSON_DATA_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API JsonData {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for JsonData objects.
             * @details Constructs a new JsonData with default initialization for all members.
             */
            JsonData();

            /**
             * @brief The copy constructor for JsonData objects.
             * @details Constructs a new JsonData by copying an existing JsonData.
             */
            JsonData(const JsonData& ref) = default;
            
            /**
             * @brief The move constructor for JsonData objects.
             * @details Constructs a new JsonData by moving the data of a JsonData into this object.
             */
            JsonData(JsonData&& ref) = default;

            /**
             * @brief The destructor for JsonData objects.
             * @details Called when an instance of JsonData is deleted.
             */
            virtual ~JsonData();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for JsonData objects.
             * @details Reassigns the value of this object by copying the data of a JsonData into this object.
             */
            JsonData& operator=(const JsonData& ref) = default;

            /**
             * @brief The move assignment operator for JsonData objects.
             * @details Reassigns the value of this object by moving the data of a JsonData into this object.
             */
            JsonData& operator=(JsonData&& ref) = default;

        protected:

        private:

    };

}

#endif