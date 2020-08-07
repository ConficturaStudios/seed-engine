/**
 * File.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "File.hpp"

namespace seedengine {

    File::File(const String& path) : File(path, FileMode::READ_WRITE) {

    }

    File::File(const String& path, const FileMode& mode)
        : path_(path), mode_(static_cast<std::ios_base::openmode>(mode)) {
        file_.open(path, mode_);
        if (file_) {
            file_.seekg(0, file_.end);
            length_ = (std::streamoff)file_.tellg();
            file_.seekg(0, file_.beg);
        }
    }

    File::~File() {
        if (file_.is_open()) file_.close();
    }

    bool File::read(void* content, const size_t& size, const size_t& len) {
        if (mode_ & static_cast<std::ios_base::openmode>(FileMode::READ) && file_.is_open()) {
            file_.read((char*)content, size * len);
            return true;
        }
        else return false;
    }

    bool File::read(void* content, const size_t& size, const size_t& len, const size_t& pos) {
        if (mode_ & static_cast<std::ios_base::openmode>(FileMode::READ) && file_.is_open()) {
            file_.seekg(pos);
            file_.read((char*)content, size * len);
            return true;
        }
        else return false;
    }

    bool File::write(const void* content, const size_t& size) {
        if (mode_ & static_cast<std::ios_base::openmode>(FileMode::WRITE) && file_.is_open()) {
            file_.write((char*)content, size);
            return true;
        }
        else return false;
    }

    bool File::write(const void* content, const size_t& size, const size_t& pos) {
        if (mode_ & static_cast<std::ios_base::openmode>(FileMode::WRITE) && file_.is_open()) {
            file_.seekp(pos);
            file_.write((char*)content, size);
            return true;
        }
        else return false;
    }

    bool File::append(const void* content, const size_t& size) {
        if (mode_ & static_cast<std::ios_base::openmode>(FileMode::WRITE) && file_.is_open()) {
            std::streampos pos = file_.tellp();
            file_.seekg(0, file_.end);
            write(content, size);
            file_.seekg(pos);
            return true;
        }
        else return false;
    }

    String File::path() const {
        return path_;
    }

    FileMode File::mode() const {
        return static_cast<FileMode>(mode_);
    }

    std::streamoff File::length() const {
        return length_;
    }

}