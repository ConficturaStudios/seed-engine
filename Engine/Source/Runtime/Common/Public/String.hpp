/**
 * String.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_STRING_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_STRING_H_

#include "CommonAPI.hpp"

#include <iostream>
#include <string>
#include <initializer_list>

namespace seedengine {

    using String = ::std::string;

    //TODO: Decide if custom String implementation should be immutable or not
    //*NOTE: std::string is NOT immutable, C# and Java implementations are

    //TODO: Add custom string view class for compile time strings

/*
    class StringClass final {

            struct StringIterator final {
                friend class StringClass;
            };

        public:

        // Types

            using value_type     = char;
            using traits_type    = ::std::char_traits<value_type>;
            using allocator_type = ::std::allocator<value_type>;

            using reference       = value_type&;
            using const_reference = const value_type&;
            using pointer         = value_type*;
            using const_pointer   = const value_type*;

            using iterator       = StringIterator;
            using const_iterator = const StringIterator;

            using reverse_iterator       = ::std::reverse_iterator<iterator>;
            using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

            using difference_type = ::std::ptrdiff_t;
            using size_type       = ::std::size_t;

        // Constants

            static constexpr const size_type npos = -1;

        private:

            value_type* m_buffer = nullptr;

            size_type m_length = 0;
            size_type m_capacity = 0;

        public:

        // Constructors and Destructors

            StringClass() noexcept;

            StringClass(const StringClass& ref);
            StringClass(StringClass&& ref);

            StringClass(const char* cstr);

            StringClass(const ::std::string& str);

            ~StringClass();

            //TODO: Add constructors and assignment operators for string view and other types

        // Assignment operators

            StringClass& operator=(const StringClass& rhs);
            StringClass& operator=(StringClass&& rhs);

            StringClass& operator=(const char* rhs);

            StringClass& operator=(const ::std::string& rhs);

        // Container Functions
            
            [[nodiscard]] size_type size() const noexcept;

            [[nodiscard]] size_type length() const noexcept;

            [[nodiscard]] size_type maxSize() const noexcept;

            [[nodiscard]] size_type capacity() const noexcept;

            [[nodiscard]] bool empty() const noexcept;

            void resize(size_type n) noexcept;
            void resize(size_type n, char fill) noexcept;

            void reserve(size_type n) noexcept;

            void clear() noexcept;

            void shrinkToFit();

        // Static Functions

            //TODO: Consider integrating with runtime type info system
            //TODO: Create specializations for primative data types, custom classes (implement toString method in classes???)

            template <typename T>
            [[nodiscard]] static StringClass toString(const T& value);

        // String Functions

            [[nodiscard]] const_pointer cstring() const noexcept;
            [[nodiscard]] const_pointer data() const noexcept;

            [[nodiscard]] void* getAllocator() const noexcept;

            size_type copy(pointer dest, size_type len, size_type pos) const;

            [[nodiscard]] size_type find(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type find(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type find(const char*          str, size_type pos) const;
            [[nodiscard]] size_type find(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type find(char                   c, size_type pos) const noexcept;

            [[nodiscard]] size_type rfind(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type rfind(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type rfind(const char*          str, size_type pos) const;
            [[nodiscard]] size_type rfind(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type rfind(char                   c, size_type pos) const noexcept;

            [[nodiscard]] size_type findFirstOf(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type findFirstOf(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type findFirstOf(const char*          str, size_type pos) const;
            [[nodiscard]] size_type findFirstOf(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type findFirstOf(char                   c, size_type pos) const noexcept;

            [[nodiscard]] size_type findLastOf(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type findLastOf(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type findLastOf(const char*          str, size_type pos) const;
            [[nodiscard]] size_type findLastOf(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type findLastOf(char                   c, size_type pos) const noexcept;

            [[nodiscard]] size_type findFirstNotOf(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type findFirstNotOf(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type findFirstNotOf(const char*          str, size_type pos) const;
            [[nodiscard]] size_type findFirstNotOf(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type findFirstNotOf(char                   c, size_type pos) const noexcept;

            [[nodiscard]] size_type findLastNotOf(const StringClass&   str, size_type pos) const noexcept;
            [[nodiscard]] size_type findLastNotOf(const ::std::string& str, size_type pos) const noexcept;
            [[nodiscard]] size_type findLastNotOf(const char*          str, size_type pos) const;
            [[nodiscard]] size_type findLastNotOf(const char*          str, size_type pos, size_type len) const;
            [[nodiscard]] size_type findLastNotOf(char                   c, size_type pos) const noexcept;

            [[nodiscard]] StringClass substr(size_type pos, size_type len) const;

            [[nodiscard]] uint32_t compare(const StringClass&   str) const noexcept;
            [[nodiscard]] uint32_t compare(const ::std::string& str) const noexcept;
            [[nodiscard]] uint32_t compare(const char*          str) const;

            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const StringClass&   str) const;
            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const ::std::string& str) const;
            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const char*          str) const;
            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const char*          str, size_type n) const;

            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const StringClass&   str,
                                           size_type subpos, size_type sublen) const;
            [[nodiscard]] uint32_t compare(size_type pos, size_type len, const ::std::string& str,
                                           size_type subpos, size_type sublen) const;

            [[nodiscard]] bool startsWith(const StringClass&   substr) const noexcept;
            [[nodiscard]] bool startsWith(const ::std::string& substr) const noexcept;
            [[nodiscard]] bool startsWith(const char*          substr) const;

            [[nodiscard]] bool endsWith(const StringClass&   substr) const noexcept;
            [[nodiscard]] bool endsWith(const ::std::string& substr) const noexcept;
            [[nodiscard]] bool endsWith(const char*          substr) const;

            [[nodiscard]] StringClass toLowerCase() const noexcept;
            [[nodiscard]] StringClass toUpperCase() const noexcept;

        // Modifier Functions

            StringClass& append(const StringClass&   str);
            StringClass& append(const ::std::string& str);

            StringClass& append(const StringClass&   str, size_type subpos, size_type sublen);
            StringClass& append(const ::std::string& str, size_type subpos, size_type sublen);

            StringClass& append(const char*          str);
            StringClass& append(const char*          str, size_type n);

            StringClass& append(char c);
            StringClass& append(char c, size_type n);

            template<class InputIterator>
            StringClass& append(InputIterator first, InputIterator last);

            StringClass& append(std::initializer_list<char> il);

            //TODO: Add other modifier methods and iterator methods http://www.cplusplus.com/reference/string/string/

            //assign, insert, erase, replace, swap; push back and pop back (?)
            
        // Accessor Functions

            [[nodiscard]]       char& at(size_type pos);
            [[nodiscard]] const char& at(size_type pos) const;

            [[nodiscard]]       char& back();
            [[nodiscard]] const char& back() const;

            [[nodiscard]]       char& front();
            [[nodiscard]] const char& front() const;

        // Accessor Operators

            [[nodiscard]]       char& operator[](size_type pos);
            [[nodiscard]] const char& operator[](size_type pos) const;

        // Concatination Operators

            [[nodiscard]] StringClass operator+(const StringClass&   rhs) const noexcept;
            [[nodiscard]] StringClass operator+(const ::std::string& rhs) const noexcept;
            [[nodiscard]] StringClass operator+(const char*          rhs) const;

            //NOTE: Use toString<T>() method and operator+(const StringClass&) for implementation
            template <typename T>
            [[nodiscard]] StringClass operator+(const T& rhs) const;

            friend StringClass operator+(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend StringClass operator+(const char*          lhs, const StringClass& rhs);

            //NOTE: Use toString<T>() method and operator+(const StringClass&) for implementation
            template <typename T>
            friend StringClass operator+(const T& lhs, const StringClass& rhs) const;

        // Modifier Operators

            StringClass& operator+=(const StringClass&   rhs) noexcept;
            StringClass& operator+=(const ::std::string& rhs) noexcept;
            StringClass& operator+=(const char*          rhs);

            //NOTE: Use toString<T>() method and operator+=(const StringClass&) for implementation
            template <typename T>
            StringClass& operator+=(const T& rhs) const;

        // Relational Operators

            [[nodiscard]] bool operator==(const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator==(const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator==(const char*          rhs) const;

            [[nodiscard]] bool operator!=(const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator!=(const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator!=(const char*          rhs) const;

            [[nodiscard]] bool operator< (const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator< (const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator< (const char*          rhs) const;

            [[nodiscard]] bool operator<=(const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator<=(const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator<=(const char*          rhs) const;

            [[nodiscard]] bool operator> (const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator> (const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator> (const char*          rhs) const;

            [[nodiscard]] bool operator>=(const StringClass&   rhs) const noexcept;
            [[nodiscard]] bool operator>=(const ::std::string& rhs) const noexcept;
            [[nodiscard]] bool operator>=(const char*          rhs) const;
            
            friend bool operator==(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator==(const char*          lhs, const StringClass& rhs);
            
            friend bool operator!=(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator!=(const char*          lhs, const StringClass& rhs);
            
            friend bool operator< (const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator< (const char*          lhs, const StringClass& rhs);
            
            friend bool operator<=(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator<=(const char*          lhs, const StringClass& rhs);
            
            friend bool operator> (const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator> (const char*          lhs, const StringClass& rhs);
            
            friend bool operator>=(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend bool operator>=(const char*          lhs, const StringClass& rhs);

        // Cast Operators

            [[nodiscard]] operator ::std::string() const;

        // Global IO Operators

            friend ::std::istream& operator>>(::std::istream& lhs, StringClass& rhs);
            friend ::std::ostream& operator<<(::std::ostream& lhs, const StringClass& rhs);

    };

    [[nodiscard]] StringClass operator+(const ::std::string& lhs, const StringClass& rhs) noexcept;
    [[nodiscard]] StringClass operator+(const char*&         lhs, const StringClass& rhs) noexcept;*/

}

#endif