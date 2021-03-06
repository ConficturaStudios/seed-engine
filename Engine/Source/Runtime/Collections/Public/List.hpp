/**
 * List.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LIST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LIST_H_

#include "CollectionsAPI.hpp"

#include "Iterator.hpp"
#include "Array.hpp"

namespace seedengine {

    /**
     * @brief The generic interface for all dynamically sized list objects.
     * @details The base collection used to represent a dynamically resized list
     *          object. This class is abstract and cannot be instanced directly,
     *          and should instead be used to reference an arbitrary dynamic list.
     * @tparam T The type of data stored in this list.
     */
    template <typename T>
    class ENGINE_API List : public Iterable<T>, public ReverseIterable<T> {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for List objects.
             * @details Constructs a new List with default initialization for all members.
             */
            List() = default;

            /**
             * @brief The copy constructor for List objects.
             * @details Constructs a new List by copying an existing List.
             */
            List(const List& ref) = default;
            
            /**
             * @brief The move constructor for List objects.
             * @details Constructs a new List by moving the data of a List into this object.
             */
            List(List&& ref) = default;

            /**
             * @brief The destructor for List objects.
             * @details Called when an instance of List is deleted.
             */
            virtual ~List() = default;

        // Functions

            virtual void add(std::size_t index, T value) = 0;
            
            virtual void addFirst(T value) {
                add(0, value);
            }
            
            virtual void addLast(T value) {
                add(size(), value);
            }
            
            virtual T set(std::size_t index, T value) = 0;
            
            [[nodiscard]] virtual T& get(std::size_t index) = 0;
            [[nodiscard]] virtual const T& get(std::size_t index) const = 0;
            
            [[nodiscard]] virtual T& first() {
                return get(0);
            }
            
            [[nodiscard]] virtual const T& first() const {
                return get(0);
            }
            
            [[nodiscard]] virtual T& last() {
                return get(size() - 1);
            }
            
            [[nodiscard]] virtual const T& last() const {
                return get(size() - 1);
            }
            
            [[nodiscard]] virtual std::size_t size() const noexcept = 0;
            
            [[nodiscard]] inline bool isEmpty() const noexcept { return size() == 0; }
            
            virtual T remove(std::size_t index) = 0;
            
            virtual T removeFirst() {
                return remove(0);
            }
            
            virtual T removeLast() {
                return remove(size() - 1);
            }
            
            // Bulk modifiers
            
            virtual void clear() {
                const std::size_t s = size();
                for (std::size_t i = 0; i < s; i++) {
                    removeFirst();
                }
            }
            
            virtual void reverse() {
                const std::size_t s = size();
                for (std::size_t i = 0; i < s; i++) {
                    add(i, removeLast());
                }
            }
            
            // Conditional modifiers
            
            virtual void removeIf(bool (*check)(const T&)) {
                for (std::size_t i = 0; i < size(); i++) {
                    if (check(get(i))) remove(i--);
                }
            }
            
            // Conversion
            
            // TODO: Decide what type of array to return from 
            [[nodiscard]] virtual T* toArray() const = 0;
            
            // Operators
            
            [[nodiscard]] virtual T& operator[](std::size_t index) {
                return get(index);
            }
            
            [[nodiscard]] virtual const T& operator[](std::size_t index) const {
                return get(index);
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for List objects.
             * @details Reassigns the value of this object by copying the data of a List into this object.
             */
            List& operator=(const List& rhs) = default;

            /**
             * @brief The move assignment operator for List objects.
             * @details Reassigns the value of this object by moving the data of a List into this object.
             */
            List& operator=(List&& rhs) = default;

        protected:

        private:

    };

}

#endif