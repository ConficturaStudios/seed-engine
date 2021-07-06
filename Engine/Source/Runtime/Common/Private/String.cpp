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

/*template struct ENGINE_API ::std::char_traits<char>;
template class ENGINE_API ::std::allocator<char>;
template class ENGINE_API ::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>;*/

namespace seedengine {


// Constructors and Destructors

    StringClass::StringClass() noexcept {
        m_capacity = 10;
        m_buffer = new value_type[m_capacity];
        m_length = 0;
    }

    StringClass::StringClass(const StringClass& ref) {
        m_capacity = ref.m_capacity;
        m_length = ref.m_length;
        m_buffer = new value_type[m_capacity];
        strncpy(m_buffer, ref.m_buffer, m_length);
    }

    StringClass::StringClass(StringClass&& ref) {
        m_capacity = ref.m_capacity;
        m_length = ref.m_length;
        m_buffer = ref.m_buffer;
        ref.m_buffer = nullptr;
    }


    StringClass::StringClass(const char* cstr) {
        m_capacity = strlen(cstr) + 1;
        m_length = strlen(cstr);
        m_buffer = new value_type[m_capacity];
        strncpy(m_buffer, cstr, m_length);
    }


    StringClass::StringClass(const ::std::string& str) {
        m_capacity = str.capacity();
        m_length = str.length();
        m_buffer = new value_type[m_capacity];
        strncpy(m_buffer, str.c_str(), m_length);
    }


    StringClass::~StringClass() {
        if (m_buffer) delete[] m_buffer;
    }

// Assignment operators

    StringClass& StringClass::operator=(const StringClass& rhs) {
        clear();
        m_capacity = rhs.m_capacity;
        m_length = rhs.m_length;
        m_buffer = new value_type[m_capacity];
        strncpy(m_buffer, rhs.m_buffer, m_length);
        return *this;
    }

    StringClass& StringClass::operator=(StringClass&& rhs) {
        clear();
        m_capacity = rhs.m_capacity;
        m_length = rhs.m_length;
        m_buffer = rhs.m_buffer;
        rhs.m_buffer = nullptr;
        return *this;
    }

    StringClass& StringClass::operator=(const char* rhs) {
        clear();
        m_capacity = strlen(rhs);
        m_length = strlen(rhs);
        m_buffer = new value_type[m_length + 1];
        strncpy(m_buffer, rhs, m_length);
        return *this;
    }

    StringClass& StringClass::operator=(const ::std::string& rhs) {
        clear();
        m_capacity = rhs.capacity();
        m_length = rhs.length();
        m_buffer = new value_type[m_capacity];
        strncpy(m_buffer, rhs.c_str(), m_length);
        return *this;
    }

// Container Functions
    
    [[nodiscard]] StringClass::size_type StringClass::size() const noexcept {
        return m_length;
    }

    [[nodiscard]] StringClass::size_type StringClass::length() const noexcept {
        return m_length;
    }

    [[nodiscard]] StringClass::size_type StringClass::maxSize() const noexcept {
        return npos / sizeof(value_type);
    }

    [[nodiscard]] StringClass::size_type StringClass::capacity() const noexcept {
        return m_capacity;
    }

    [[nodiscard]] bool StringClass::empty() const noexcept {
        return m_length == 0;
    }

    void StringClass::resize(StringClass::size_type n) noexcept {
        if (n < m_length) {
            value_type* temp = new value_type[n + 1];
            memmove(temp, m_buffer, n * sizeof(value_type));
            m_length = n;
            m_capacity = n;
        }
        else if (n > m_length) {

        }
    }
    void StringClass::resize(StringClass::size_type n, char fill) noexcept {

    }

    void StringClass::reserve(StringClass::size_type n) noexcept {

    }

    void StringClass::clear() noexcept {
        if (m_buffer) delete[] m_buffer;
        m_length = 0;
        m_capacity = 10;
        m_buffer = new value_type[m_capacity];
    }

    void StringClass::shrinkToFit() {

    }
}