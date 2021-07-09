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
#include "Collection.hpp"

namespace seedengine {

    /**
     * @brief The generic interface for all dynamically sized list objects.
     * @details The base collection used to represent a dynamically resized list
     *          object. This class is abstract and cannot be instanced directly,
     *          and should instead be used to reference an arbitrary dynamic list.
     * @tparam T The type of data stored in this list.
     */
    template <typename T>
    class List : public Collection<T>, public ReverseIterable<T, Iterator<T>> {

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
            List(List&& ref) noexcept = default;

            /**
             * @brief The destructor for List objects.
             * @details Called when an instance of List is deleted.
             */
            virtual ~List() = default;

        // Functions

            /**
             * Sets the value associated with the specified index to the provided value.
             * @param index The index to set at.
             * @param value The new value.
             * @return The previously stored value.
             */
            virtual T set(std::size_t index, const T& value) = 0;

            /**
             * Gets the value associated with the specified index.
             * @param index The index to get.
             * @return The value at the index.
             */
            [[nodiscard]] virtual T& get(std::size_t index) = 0;

            /**
             * Gets the value associated with the specified index.
             * @param index The index to get.
             * @return The value at the index.
             */
            [[nodiscard]] virtual const T& get(std::size_t index) const = 0;

            /**
             * Removes the element with the specified index.
             * @param index The index of the element to remove.
             * @return The removed object.
             */
            virtual T remove(std::size_t index) = 0;

            /**
             * Adds the provided value to the list at the specified index.
             * @param index The index position to insert the value at.
             * @param value The value to insert.
             */
            virtual void add(std::size_t index, const T& value) = 0;

            /**
             * Adds the provided value at the beginning of the list.
             * @param value The value to insert.
             */
            virtual void addFirst(const T& value) {
                this->add(0, value);
            }

            /**
             * Adds the provided value at the end of the list.
             * @param value The value to insert.
             */
            virtual void addLast(const T& value) {
                this->add(this->size(), value);
            }

            /**
             * Gets the first element in this list.
             * @return The first element in this list.
             */
            [[nodiscard]] virtual T& first() {
                return this->get(0);
            }

            /**
             * Gets the first element in this list.
             * @return The first element in this list.
             */
            [[nodiscard]] virtual const T& first() const {
                return this->get(0);
            }

            /**
             * Gets the last element in this list.
             * @return The last element in this list.
             */
            [[nodiscard]] virtual T& last() {
                return this->get(this->size() - 1);
            }

            /**
             * Gets the last element in this list.
             * @return The last element in this list.
             */
            [[nodiscard]] virtual const T& last() const {
                return this->get(this->size() - 1);
            }

            /**
             * Removes and returns the first element of the list.
             * @return The removed element.
             */
            virtual T removeFirst() {
                return this->remove(0);
            }

            /**
             * Removes and returns the last element of the list.
             * @return The removed element.
             */
            virtual T removeLast() {
                return this->remove(this->size() - 1);
            }

            // Search

        // Bulk modifiers
            
            virtual void clear() {
                const std::size_t s = this->size();
                for (std::size_t i = 0; i < s; i++) {
                    this->removeFirst();
                }
            }

            /**
             * Reverses the contents of this list.
             */
            virtual void reverse() {
                const std::size_t s = this->size();
                for (std::size_t i = 0; i < s; i++) {
                    this->add(i, removeLast());
                }
            }
            
            // Conditional modifiers

        // Conversion

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
            List& operator=(List&& rhs) noexcept = default;

        protected:

        private:

    };

}

#endif