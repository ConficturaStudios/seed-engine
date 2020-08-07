/**
 * JsonHandler.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_JSON_HANDLER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_JSON_HANDLER_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API JsonHandler {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for JsonHandler objects.
             * @details Constructs a new JsonHandler with default initialization for all members.
             */
            JsonHandler();

            /**
             * @brief The copy constructor for JsonHandler objects.
             * @details Constructs a new JsonHandler by copying an existing JsonHandler.
             */
            JsonHandler(const JsonHandler& ref) = default;
            
            /**
             * @brief The move constructor for JsonHandler objects.
             * @details Constructs a new JsonHandler by moving the data of a JsonHandler into this object.
             */
            JsonHandler(JsonHandler&& ref) = default;

            /**
             * @brief The destructor for JsonHandler objects.
             * @details Called when an instance of JsonHandler is deleted.
             */
            virtual ~JsonHandler();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for JsonHandler objects.
             * @details Reassigns the value of this object by copying the data of a JsonHandler into this object.
             */
            JsonHandler& operator=(const JsonHandler& ref) = default;

            /**
             * @brief The move assignment operator for JsonHandler objects.
             * @details Reassigns the value of this object by moving the data of a JsonHandler into this object.
             */
            JsonHandler& operator=(JsonHandler&& ref) = default;

        protected:

        private:

    };

}

#endif