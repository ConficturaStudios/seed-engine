/**
 * @file Stack.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_STACK_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_STACK_H_

#include "CollectionsAPI.hpp"

#include "Collection.hpp"

namespace seedengine {

    /**
     * @brief A last-in first-out stack of generic data.
     * @details
     * A first-in last-out stack of generic data built on top of a linked list implementation.
     * It is worth noting that this stack implementation is not what would be considered a pure stack in that
     * it allows for all generic collection operations and iteration without removal. This may be changed
     * in a later update.
     * @tparam T The type of data stored inside of this stack.
     */
    template <typename T>
    class Stack : public Collection<T> {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Stack objects.
             * @details Constructs a new Stack with default initialization for all members.
             */
            Stack() : Collection<T>() {
                m_list();
            }

            /**
             * @brief The copy constructor for Stack objects.
             * @details Constructs a new Stack by copying an existing Stack.
             */
            Stack(const Stack& ref) = default;
            
            /**
             * @brief The move constructor for Stack objects.
             * @details Constructs a new Stack by moving the data of a Stack into this object.
             */
            Stack(Stack&& ref) noexcept = default;

            /**
             * @brief The destructor for Stack objects.
             * @details Called when an instance of Stack is deleted.
             */
            virtual ~Stack() = default;

        // Functions

            /**
             * Pushes the provided value onto the top of this stack.
             * @param value The value to add to this stack.
             */
            void push(const T& value) {
                m_list.addLast(value);
            }

            /**
             * Removes and returns the element at the top of this stack.
             * @return The element previously on the top of this stack.
             */
            T pop() {
                return m_list.removeLast();
            }

            /**
             * Checks the value on the top of this stack without removing it.
             * @return A reference to the value on the top of this stack.
             */
            [[nodiscard]] T& peek() {
                return m_list.last();
            }

            /**
             * Checks the value on the top of this stack without removing it.
             * @return A reference to the value on the top of this stack.
             */
            [[nodiscard]] const T& peek() const {
                return m_list.last();
            }

            [[nodiscard]] size_t size() const noexcept override {
                return m_list.size();
            }

            bool removeElement(const T& element) override {
                return m_list.removeElement(element);
            }

            [[nodiscard]] bool contains(const T& element) const override {
                return m_list.contains(element);
            }

            void clear() override {
                m_list.clear();
            }

        // Iterators

            [[nodiscard]] Iterator<T> begin() override {
                return m_list.begin();
            }

            [[nodiscard]] const Iterator<T> begin() const override {
                return m_list.begin();
            }

            [[nodiscard]] const Iterator<T> cbegin() const override {
                return m_list.cbegin();
            }

            [[nodiscard]] Iterator<T> end() override {
                return m_list.end();
            }

            [[nodiscard]] const Iterator<T> end() const override {
                return m_list.end();
            }

            [[nodiscard]] const Iterator<T> cend() const override {
                return m_list.cend();
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Stack objects.
             * @details Reassigns the value of this object by copying the data of a Stack into this object.
             */
            Stack& operator=(const Stack& rhs) = default;

            /**
             * @brief The move assignment operator for Stack objects.
             * @details Reassigns the value of this object by moving the data of a Stack into this object.
             */
            Stack& operator=(Stack&& rhs) noexcept = default;

        private:

            /** The internal linked list representing this stack. */
            LinkedList<T> m_list;

    };

}

#endif