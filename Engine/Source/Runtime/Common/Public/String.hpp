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
    //NOTE: std::string is NOT immutable, C# and JAva implementations are

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

            static constexpr const std::size_t npos = -1;

        // Constructors and Destructors

            StringClass() noexcept;

            StringClass(const StringClass& ref);
            StringClass(StringClass&& ref);

            StringClass(const char* cstr);

            StringClass(const ::std::string& str);
            StringClass(::std::string&& str);

            ~StringClass();

        // Container Functions
            
            [[nodiscard]] std::size_t size() const noexcept;

            [[nodiscard]] std::size_t length() const noexcept;

            [[nodiscard]] std::size_t maxSize() const noexcept;

            [[nodiscard]] std::size_t capacity() const noexcept;

            [[nodiscard]] bool empty() const noexcept;

            void resize(std::size_t n) noexcept;
            void resize(std::size_t n, char fill) noexcept;

            void reserve(std::size_t n) noexcept;

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

            std::size_t copy(pointer dest, std::size_t len, std::size_t pos) const;

            [[nodiscard]] std::size_t find(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t find(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t find(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t find(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t find(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] std::size_t rfind(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t rfind(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t rfind(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t rfind(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t rfind(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] std::size_t findFirstOf(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findFirstOf(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findFirstOf(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t findFirstOf(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t findFirstOf(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] std::size_t findLastOf(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findLastOf(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findLastOf(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t findLastOf(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t findLastOf(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] std::size_t findFirstNotOf(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findFirstNotOf(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findFirstNotOf(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t findFirstNotOf(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t findFirstNotOf(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] std::size_t findLastNotOf(const StringClass&   str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findLastNotOf(const ::std::string& str, std::size_t pos) const noexcept;
            [[nodiscard]] std::size_t findLastNotOf(const char*          str, std::size_t pos) const;
            [[nodiscard]] std::size_t findLastNotOf(const char*          str, std::size_t pos, std::size_t len) const;
            [[nodiscard]] std::size_t findLastNotOf(char                   c, std::size_t pos) const noexcept;

            [[nodiscard]] StringClass substr(std::size_t pos, std::size_t len) const;

            [[nodiscard]] uint32_t compare(const StringClass&   str) const noexcept;
            [[nodiscard]] uint32_t compare(const ::std::string& str) const noexcept;
            [[nodiscard]] uint32_t compare(const char*          str) const;

            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const StringClass&   str) const;
            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const ::std::string& str) const;
            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const char*          str) const;
            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const char*          str, std::size_t n) const;

            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const StringClass&   str,
                                           std::size_t subpos, std::size_t sublen) const;
            [[nodiscard]] uint32_t compare(std::size_t pos, std::size_t len, const ::std::string& str,
                                           std::size_t subpos, std::size_t sublen) const;

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

            StringClass& append(const StringClass&   str, std::size_t subpos, std::size_t sublen);
            StringClass& append(const ::std::string& str, std::size_t subpos, std::size_t sublen);

            StringClass& append(const char*          str);
            StringClass& append(const char*          str, std::size_t n);

            StringClass& append(char c, std::size_t n);

            template<class InputIterator>
            StringClass& append(InputIterator first, InputIterator last);

            StringClass& append(std::initializer_list<char> il);

            //TODO: Add other modifier methods and iterator methods http://www.cplusplus.com/reference/string/string/

            //assign, insert, erase, replace, swap; push back and pop back (?)
            
        // Accessor Functions

            [[nodiscard]]       char& at(std::size_t pos);
            [[nodiscard]] const char& at(std::size_t pos) const;

            [[nodiscard]]       char& back();
            [[nodiscard]] const char& back() const;

            [[nodiscard]]       char& front();
            [[nodiscard]] const char& front() const;

        // Accessor Operators

            [[nodiscard]]       char& operator[](std::size_t pos);
            [[nodiscard]] const char& operator[](std::size_t pos) const;

        // Concatination Operators

            [[nodiscard]] StringClass operator+(const StringClass&   rhs) const noexcept;
            [[nodiscard]] StringClass operator+(const ::std::string& rhs) const noexcept;
            [[nodiscard]] StringClass operator+(const char*          rhs) const;

            friend StringClass operator+(const ::std::string& lhs, const StringClass& rhs) noexcept;
            friend StringClass operator+(const char*          lhs, const StringClass& rhs);

        // Modifier Operators

            StringClass& operator+=(const StringClass&   rhs) noexcept;
            StringClass& operator+=(const ::std::string& rhs) noexcept;
            StringClass& operator+=(const char*          rhs);

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