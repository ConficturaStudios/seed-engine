/**
 * XmlData.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_XML_DATA_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_XML_DATA_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API XmlData {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for XmlData objects.
             * @details Constructs a new XmlData with default initialization for all members.
             */
            XmlData();

            /**
             * @brief The copy constructor for XmlData objects.
             * @details Constructs a new XmlData by copying an existing XmlData.
             */
            XmlData(const XmlData& ref) = default;
            
            /**
             * @brief The move constructor for XmlData objects.
             * @details Constructs a new XmlData by moving the data of a XmlData into this object.
             */
            XmlData(XmlData&& ref) = default;

            /**
             * @brief The destructor for XmlData objects.
             * @details Called when an instance of XmlData is deleted.
             */
            virtual ~XmlData();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for XmlData objects.
             * @details Reassigns the value of this object by copying the data of a XmlData into this object.
             */
            XmlData& operator=(const XmlData& ref) = default;

            /**
             * @brief The move assignment operator for XmlData objects.
             * @details Reassigns the value of this object by moving the data of a XmlData into this object.
             */
            XmlData& operator=(XmlData&& ref) = default;

        protected:

        private:

    };

}

#endif