/**
 * File.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_FILE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_FILE_EXCHANGE_FILE_H_

#include "FileExchangeAPI.hpp"

#include "String.hpp"
#include <fstream>

namespace seedengine {

    /**
     * @brief The file access mode used when working with a file.
     * 
     */
    enum class ENGINE_API FileMode : std::ios_base::openmode {
        /** Open a file for read only access. */
        READ = std::ios_base::in,
        /** Open a file for write only access. */
        WRITE = std::ios_base::out,
        /** Open a file for read and write access. */
        READ_WRITE = READ | WRITE
    };

    /**
     * @brief A path within the local file system.
     * 
     */
    class ENGINE_API Path {

    };

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API File {

        public:

        // Constructors and destructor

            /**
             * @brief The constructor for File objects.
             * @details Constructs a new File object with the specified path in ReadWrite mode.
             * 
             * @param path The path of the file to read or write to.
             * 
             */
            File(const String& path);

            /**
             * @brief The constructor for File objects.
             * @details Constructs a new File object with the specified path the specified IO mode mode.
             * 
             * @param path The path of the file to read or write to.
             * 
             */
            File(const String& path, const FileMode& mode);

            /**
             * @brief The copy constructor for File objects.
             * @details Constructs a new File by copying an existing File.
             */
            File(const File& ref) = default;
            
            /**
             * @brief The move constructor for File objects.
             * @details Constructs a new File by moving the data of a File into this object.
             */
            File(File&& ref) = default;

            /**
             * @brief The destructor for File objects.
             * @details Called when an instance of File is deleted.
             */
            virtual ~File();

        // Functions

            /**
             * @brief Reads the content of this file from the current position until len into a pointer.
             * 
             * @param content The pointer to target with the read content.
             * @param size The size of the content unit in bytes (use sizeof(typename) for the type of content).
             * @param len The number of data units to read.
             * @return true If the read is successful.
             * @return false If reading is disabled for this file or if an error is encountered. Content may be corrupted.
             */
            bool read(void* content, const size_t& size, const size_t& len);

            /**
             * @brief Reads the content of this file from the specified position until len into a pointer.
             * 
             * @param content The pointer to target with the read content.
             * @param size The size of the content unit in bytes (use sizeof(typename) for the type of content).
             * @param len The number of data units to read.
             * @param pos The position to start the read in the file.
             * @return true If the read is successful.
             * @return false If reading is disabled for this file or if an error is encountered. Content may be corrupted.
             */
            bool read(void* content, const size_t& size, const size_t& len, const size_t& pos);

            /**
             * @brief Writes the values stored in content into the file at the current position.
             * 
             * @param content The pointer to the data to write.
             * @param size The size in bytes of the data to write.
             * @return true If the write is successful.
             * @return false If writing is disabled for this file or if an error is encountered.
             */
            bool write(const void* content, const size_t& size);

            /**
             * @brief Writes the values stored in content into the file at the specified position.
             * 
             * @param content The pointer to the data to write.
             * @param size The size in bytes of the data to write.
             * @param pos The position to begin the write at.
             * @return true If the write is successful.
             * @return false If writing is disabled for this file or if an error is encountered.
             */
            bool write(const void* content, const size_t& size, const size_t& pos);

            /**
             * @brief Appends the values stored in content into the file at the end.
             *        Write position is reset to its current location after completion.
             * 
             * @param content The pointer to the data to write.
             * @param size The size in bytes of the data to write.
             * @return true If the write is successful.
             * @return false If writing is disabled for this file or if an error is encountered.
             */
            bool append(const void* content, const size_t& size);

        // Getters

            /**
             * @brief Get the path of this file.
             * 
             * @return String the path of this file.
             */
            String path() const;

            /**
             * @brief Get the FileMode of this file.
             * 
             * @return FileMode the FileMode of this object.
             */
            FileMode mode() const;

            /**
             * @brief Gets the length of this file in number of bytes.
             * 
             * @return std::streamoff the number of bytes in this file.
             */
            std::streamoff length() const;

        // Operators

            /**
             * @brief The copy assignment operator for File objects.
             * @details Reassigns the value of this object by copying the data of a File into this object.
             */
            File& operator=(const File& ref) = default;

            /**
             * @brief The move assignment operator for File objects.
             * @details Reassigns the value of this object by moving the data of a File into this object.
             */
            File& operator=(File&& ref) = default;

        protected:

            /** The path to this file. */
            const String path_;
            /** The io mode of this file. */
            const std::ios_base::openmode mode_;

            /** The stream for this file. */
            std::fstream file_;

            /** The length of this file. */
            std::streamoff length_;

        private:

    };

}

#endif