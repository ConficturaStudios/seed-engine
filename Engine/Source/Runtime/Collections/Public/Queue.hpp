/**
 * @file Queue.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_QUEUE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_QUEUE_H_

#include "CollectionsAPI.hpp"

#include "Collection.hpp"

namespace seedengine {

    /**
     * @brief A first-in first-out queue of generic data.
     * @details
     * A first-in first-out queue of generic data built on top of a linked list implementation.
     * It is worth noting that this queue implementation is not what would be considered a pure queue in that
     * it allows for all generic collection operations and iteration without removal. This may be changed
     * in a later update.
     *
     * @tparam T The type of data stored in this queue.
     */
    template <typename T>
    class Queue : public Collection<T> {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Queue objects.
             * @details Constructs a new Queue with default initialization for all members.
             */
            Queue() : Collection<T>() {
                m_list();
            }

            /**
             * @brief The copy constructor for Queue objects.
             * @details Constructs a new Queue by copying an existing Queue.
             */
            Queue(const Queue& ref) = default;
            
            /**
             * @brief The move constructor for Queue objects.
             * @details Constructs a new Queue by moving the data of a Queue into this object.
             */
            Queue(Queue&& ref) noexcept = default;

            /**
             * @brief The destructor for Queue objects.
             * @details Called when an instance of Queue is deleted.
             */
            virtual ~Queue() = default;

        // Functions

            /**
             * Pushes the provided value to the back of this queue.
             * @param value The value to add to this queue.
             */
            void enqueue(const T& value) {
                m_list.addLast(value);
            }

            /**
             * Removes and returns the first element in this queue.
             * @return The previously first element of this queue.
             */
            T dequeue() {
                return m_list.removeFirst();
            }

            /**
             * Returns the first element of this queue without removing it.
             * @return The first element of this queue.
             */
            [[nodiscard]] T& front() {
                return m_list.first();
            }

            /**
             * Returns the first element of this queue without removing it.
             * @return The first element of this queue.
             */
            [[nodiscard]] const T& front() const {
                return m_list.first();
            }

            [[nodiscard]] size_t size() const noexcept override {
                return m_list.size();
            }

            bool removeElement(const T& element) override {
                return m_list.removeElement(element);
            }

            [[nodiscard]]  bool contains(const T& element) const override {
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
             * @brief The copy assignment operator for Queue objects.
             * @details Reassigns the value of this object by copying the data of a Queue into this object.
             */
            Queue& operator=(const Queue& rhs) = default;

            /**
             * @brief The move assignment operator for Queue objects.
             * @details Reassigns the value of this object by moving the data of a Queue into this object.
             */
            Queue& operator=(Queue&& rhs) noexcept = default;

        private:

            /** The internal linked list representing this queue. */
            LinkedList<T> m_list;

    };

}

#endif