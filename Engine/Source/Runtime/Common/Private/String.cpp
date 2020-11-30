/**
 * String.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "String.hpp"


namespace seedengine {
/*
// Constructors and Destructors

    StringClass::StringClass() noexcept {
        m_capacity = 0;
        m_buffer = nullptr;
        m_size = 0;
    }

    StringClass::StringClass(const StringClass& ref) {
        m_capacity = m_capcity;
        m_size = ref.m_size;
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, ref.m_buffer, m_size);
    }

    StringClass::StringClass(StringClass&& ref) {
        m_capacity = ref.m_capacity;
        m_size = ref.m_size;
        m_buffer = ref.m_buffer;
        ref.m_buffer = nullptr;
    }


    StringClass::StringClass(const char* cstr) {
        m_capacity = strlen(cstr);
        m_size = strlen(cstr);
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, cstr, m_size);
    }


    StringClass::StringClass(const ::std::string& str) {
        m_capacity = str.capacity();
        m_size = ref.length();
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, ref.c_str(), m_size);
    }


    StringClass::~StringClass() {
        if (m_buffer) delete[] m_buffer;
    }

// Assignment operators

    StringClass& StringClass::operator=(const StringClass& rhs) {
        clear();
        m_size = rhs.m_size;
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, rhs.m_buffer, m_size);
    }

    StringClass& StringClass::operator=(StringClass&& rhs) {
        clear();
        m_size = rhs.m_size;
        m_buffer = rhs.m_buffer;
        rhs.m_buffer = nullptr;
    }

    StringClass& StringClass::operator=(const char* rhs) {
        clear();
        m_size = strlen(rhs);
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, rhs, m_size);
    }

    StringClass& StringClass::operator=(const ::std::string& rhs) {
        clear();
        m_size = rhs.length();
        m_buffer = new value_type[m_size + 1];
        strncpy_s(m_buffer, m_size + 1, rhs.c_str(), m_size);
    }

    

// Container Functions
    
    [[nodiscard]] StringClass::size_type StringClass::size() const noexcept {
        return m_size;
    }

    [[nodiscard]] StringClass::size_type StringClass::length() const noexcept {
        return m_size;
    }

    [[nodiscard]] StringClass::size_type StringClass::maxSize() const noexcept {
        return ((size_type)0) - 1;
    }

    [[nodiscard]] StringClass::size_type StringClass::capacity() const noexcept {

    }

    [[nodiscard]] bool StringClass::empty() const noexcept {
        return m_size == 0;
    }

    void StringClass::resize(StringClass::size_type n) noexcept {
        if (n < m_size) {
            value_type* temp = new value_type[n + 1];
            memmove(temp, m_buffer, n * sizeof(valu_type));
        }
        else if (n > m_size) {

        }
    }
    void StringClass::resize(StringClass::size_type n, char fill) noexcept {

    }

    void StringClass::reserve(StringClass::size_type n) noexcept {

    }

    void StringClass::clear() noexcept {
        if (m_buffer) delete[] m_buffer;
        m_size = 0;
        m_capacity = 0;
    }

    void StringClass::shrinkToFit() {

    }*/
}