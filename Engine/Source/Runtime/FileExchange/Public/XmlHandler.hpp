/**
 * XmlHandler.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_XML_HANDLER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_XML_HANDLER_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API XmlHandler {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for XmlHandler objects.
             * @details Constructs a new XmlHandler with default initialization for all members.
             */
            XmlHandler();

            /**
             * @brief The copy constructor for XmlHandler objects.
             * @details Constructs a new XmlHandler by copying an existing XmlHandler.
             */
            XmlHandler(const XmlHandler& ref) = default;
            
            /**
             * @brief The move constructor for XmlHandler objects.
             * @details Constructs a new XmlHandler by moving the data of a XmlHandler into this object.
             */
            XmlHandler(XmlHandler&& ref) = default;

            /**
             * @brief The destructor for XmlHandler objects.
             * @details Called when an instance of XmlHandler is deleted.
             */
            virtual ~XmlHandler();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for XmlHandler objects.
             * @details Reassigns the value of this object by copying the data of a XmlHandler into this object.
             */
            XmlHandler& operator=(const XmlHandler& ref) = default;

            /**
             * @brief The move assignment operator for XmlHandler objects.
             * @details Reassigns the value of this object by moving the data of a XmlHandler into this object.
             */
            XmlHandler& operator=(XmlHandler&& ref) = default;

        protected:

        private:

    };

}

#endif