/**
 * IniData.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_INI_DATA_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_INI_DATA_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API IniData {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for IniData objects.
             * @details Constructs a new IniData with default initialization for all members.
             */
            IniData();

            /**
             * @brief The copy constructor for IniData objects.
             * @details Constructs a new IniData by copying an existing IniData.
             */
            IniData(const IniData& ref) = default;
            
            /**
             * @brief The move constructor for IniData objects.
             * @details Constructs a new IniData by moving the data of a IniData into this object.
             */
            IniData(IniData&& ref) = default;

            /**
             * @brief The destructor for IniData objects.
             * @details Called when an instance of IniData is deleted.
             */
            virtual ~IniData();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for IniData objects.
             * @details Reassigns the value of this object by copying the data of a IniData into this object.
             */
            IniData& operator=(const IniData& ref) = default;

            /**
             * @brief The move assignment operator for IniData objects.
             * @details Reassigns the value of this object by moving the data of a IniData into this object.
             */
            IniData& operator=(IniData&& ref) = default;

        protected:

        private:

    };

}

#endif