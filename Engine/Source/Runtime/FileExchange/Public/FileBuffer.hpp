/**
 * FileBuffer.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_FILE_BUFFER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_FILE_BUFFER_H_

#include "FileExchangeAPI.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API FileBuffer {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for FileBuffer objects.
             * @details Constructs a new FileBuffer with default initialization for all members.
             */
            FileBuffer();

            /**
             * @brief The copy constructor for FileBuffer objects.
             * @details Constructs a new FileBuffer by copying an existing FileBuffer.
             */
            FileBuffer(const FileBuffer& ref) = default;
            
            /**
             * @brief The move constructor for FileBuffer objects.
             * @details Constructs a new FileBuffer by moving the data of a FileBuffer into this object.
             */
            FileBuffer(FileBuffer&& ref) = default;

            /**
             * @brief The destructor for FileBuffer objects.
             * @details Called when an instance of FileBuffer is deleted.
             */
            virtual ~FileBuffer();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for FileBuffer objects.
             * @details Reassigns the value of this object by copying the data of a FileBuffer into this object.
             */
            FileBuffer& operator=(const FileBuffer& ref) = default;

            /**
             * @brief The move assignment operator for FileBuffer objects.
             * @details Reassigns the value of this object by moving the data of a FileBuffer into this object.
             */
            FileBuffer& operator=(FileBuffer&& ref) = default;

        protected:

        private:

    };

}

#endif