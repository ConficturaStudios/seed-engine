/**
 * IniHandler.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_INI_HANDLER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_INI_HANDLER_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API IniHandler {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for IniHandler objects.
             * @details Constructs a new IniHandler with default initialization for all members.
             */
            IniHandler();

            /**
             * @brief The copy constructor for IniHandler objects.
             * @details Constructs a new IniHandler by copying an existing IniHandler.
             */
            IniHandler(const IniHandler& ref) = default;
            
            /**
             * @brief The move constructor for IniHandler objects.
             * @details Constructs a new IniHandler by moving the data of a IniHandler into this object.
             */
            IniHandler(IniHandler&& ref) = default;

            /**
             * @brief The destructor for IniHandler objects.
             * @details Called when an instance of IniHandler is deleted.
             */
            virtual ~IniHandler();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for IniHandler objects.
             * @details Reassigns the value of this object by copying the data of a IniHandler into this object.
             */
            IniHandler& operator=(const IniHandler& ref) = default;

            /**
             * @brief The move assignment operator for IniHandler objects.
             * @details Reassigns the value of this object by moving the data of a IniHandler into this object.
             */
            IniHandler& operator=(IniHandler&& ref) = default;

        protected:

        private:

    };

}

#endif