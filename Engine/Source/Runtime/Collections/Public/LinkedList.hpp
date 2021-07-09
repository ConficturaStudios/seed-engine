/**
 * LinkedList.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LINKED_LIST_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_LINKED_LIST_H_

#include "CollectionsAPI.hpp"

#include <cassert>

#include "Iterator.hpp"
#include "List.hpp"

namespace seedengine {

    /**
     * @brief A doubly linked list collection with a head and tail pointer.
     * @details
     *
     * @tparam T The type of data stored in this list.
     */
    template <typename T>
    class LinkedList : public List<T> {

            struct LinkedNode {
                T value;
                LinkedNode* next = nullptr;
                LinkedNode* prev = nullptr;
            };

            struct LinkedIterator final : public IteratorBase<T> {
                LinkedNode* node;

                explicit LinkedIterator(LinkedNode* node) : node(node) { }

                ~LinkedIterator() = default;

                [[nodiscard]] T& operator*() override {
                    return node->value;
                }

                [[nodiscard]] const T& operator*() const override {
                    return node->value;
                }

                [[nodiscard]] bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->node == dynamic_cast<const LinkedIterator&>(rhs).node;
                }

                [[nodiscard]] bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->node != dynamic_cast<const LinkedIterator&>(rhs).node;
                }

                [[nodiscard]] bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                IteratorBase<T>& operator++() override {
                    node = node->next;
                    return *this;
                }
            };



            struct LinkedReverseIterator final : public IteratorBase<T> {
                LinkedNode* node;

                explicit LinkedReverseIterator(LinkedNode* node) : node(node) { }

                ~LinkedReverseIterator() = default;

                [[nodiscard]] T& operator*() override {
                    return node->value;
                }

                [[nodiscard]] const T& operator*() const override {
                    return node->value;
                }

                [[nodiscard]] bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->node == dynamic_cast<const LinkedReverseIterator&>(rhs).node;
                }

                [[nodiscard]] bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->node != dynamic_cast<const LinkedReverseIterator&>(rhs).node;
                }

                [[nodiscard]] bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                IteratorBase<T>& operator++() override {
                    node = node->prev;
                    return *this;
                }
            };

            LinkedNode* m_sentinel;
            std::size_t m_size;

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for LinkedList objects.
             * @details Constructs a new empty LinkedList collection.
             */
            LinkedList() {
                m_size = 0;
                m_sentinel = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->next = m_sentinel;
                m_sentinel->prev = m_sentinel;
            }

            /**
             * Constructs a new linked list by copying each element of a provided array.
             * @param array The array to copy.
             */
            explicit LinkedList(const Array<T>& array) {
                m_size = 0;
                m_sentinel = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->next = m_sentinel;
                m_sentinel->prev = m_sentinel;
                for (const T& element : array) {
                    addLast(element);
                }
            }

            /**
             * Constructs a new linked list from the provided initializer list.
             * @param list The initializer list to use when building this list.
             */
            LinkedList(std::initializer_list<T> list) {
                m_sentinel = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->next = m_sentinel;
                m_sentinel->prev = m_sentinel;
                m_size = 0;
                for (const T& element : list) {
                    addLast(element);
                }
            }

            /**
             * @brief The copy constructor for LinkedList objects.
             * @details Constructs a new LinkedList by copying an existing LinkedList.
             */
            LinkedList(const LinkedList& ref) {
                m_size = ref.m_size;
                m_sentinel = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->next = m_sentinel;
                m_sentinel->prev = m_sentinel;

                LinkedNode* current = ref.m_sentinel;
                LinkedNode* pos = m_sentinel;
                while (current->next) {
                    current = current->next; // Iterate ref pointer
                    // Allocate new node
                    pos->next = (LinkedNode*)malloc(sizeof(LinkedNode));
                    // Link new node
                    pos->next->prev = pos;
                    // Connect to sentinel tail
                    pos->next->next = m_sentinel;
                    m_sentinel->prev = pos->next;
                    // Store value
                    pos->next->value = current->value;
                    // Increment pos
                    pos = pos->next;
                }
            }
            
            /**
             * @brief The move constructor for LinkedList objects.
             * @details Constructs a new LinkedList by moving the data of a LinkedList into this object.
             */
            LinkedList(LinkedList&& ref) noexcept = default;

            /**
             * @brief The destructor for LinkedList objects.
             * @details Called when an instance of LinkedList is deleted.
             */
            virtual ~LinkedList() {
                clear();
                free(m_sentinel);
            }

        // Functions

        // Overloaded functions

            T set(size_t index, const T& value) override {
                // TODO: Change to assertion macro
                if (index >= m_size) fail("Invalid index used in LinkedList.set()");

                LinkedNode* current = m_sentinel->next;
                for (std::size_t i = 0; i < index; i++) {
                    current = current->next;
                }
                T temp = current->value;
                current->value = value;
                return temp;
            }

            T& get(size_t index) override {
                // TODO: Change to assertion macro
                if (index >= m_size) fail("Invalid index used in LinkedList.get()");

                LinkedNode* current = m_sentinel->next;
                for (std::size_t i = 0; i < index; i++) {
                    current = current->next;
                }
                return current->value;
            }

            const T& get(size_t index) const override {
                // TODO: Change to assertion macro
                if (index >= m_size) fail("Invalid index used in LinkedList.get()");

                LinkedNode* current = m_sentinel->next;
                for (std::size_t i = 0; i < index; i++) {
                    current = current->next;
                }
                return current->value;
            }

            bool removeElement(const T& element) override {
                LinkedNode* current = m_sentinel->next;
                while (current && current != m_sentinel) {
                    if (current->value == element) {
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        m_size--;
                        free(current);
                        return true;
                    }
                    current = current->next;
                }
                return false;
            }

            T remove(size_t index) override {
                // TODO: Change to assertion macro
                if (index >= m_size) fail("Invalid index used in LinkedList.remove()");

                LinkedNode* current = m_sentinel->next;
                for (std::size_t i = 0; i < index; i++) {
                    current = current->next;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                // TODO: Consider returning unique pointers or other scoped pointer instead of by value to reduce copies
                T temp = current->value;
                m_size--;
                free(current);
                return temp;
            }

            bool contains(const T& element) const override {
                LinkedNode* current = m_sentinel->next;
                while (current && current != m_sentinel) {
                    if (current->value == element) {
                        return true;
                    }
                    current = current->next;
                }
                return false;
            }

            [[nodiscard]] Iterator<T> begin() override {
                return Iterator<T>(new LinkedIterator(m_sentinel->next));
            }

            [[nodiscard]] const Iterator<T> begin() const override {
                return Iterator<T>(new LinkedIterator(m_sentinel->next));
            }

            [[nodiscard]] const Iterator<T> cbegin() const override {
                return Iterator<T>(new LinkedIterator(m_sentinel->next));
            }

            [[nodiscard]] Iterator<T> end() override {
                return Iterator<T>(new LinkedIterator(m_sentinel));
            }

            [[nodiscard]] const Iterator<T> end() const override {
                return Iterator<T>(new LinkedIterator(m_sentinel));
            }

            [[nodiscard]] const Iterator<T> cend() const override {
                return Iterator<T>(new LinkedIterator(m_sentinel));
            }

            [[nodiscard]] Iterator<T> rbegin() override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel->prev));
            }

            [[nodiscard]] const Iterator<T> rbegin() const override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel->prev));
            }

            [[nodiscard]] const Iterator<T> crbegin() const override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel->prev));
            }

            [[nodiscard]] Iterator<T> rend() override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel));
            }

            [[nodiscard]] const Iterator<T> rend() const override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel));
            }

            [[nodiscard]] const Iterator<T> crend() const override {
                return Iterator<T>(new LinkedReverseIterator(m_sentinel));
            }

            void add(std::size_t index, const T& value) override {
                // TODO: Change to assertion macro
                if (index > m_size) fail("Invalid index used in LinkedList.add()");

                LinkedNode* current = m_sentinel;
                for (std::size_t i = 0; i < index; i++) {
                    current = current->next;
                }
                LinkedNode* next = current->next;
                current->next = (LinkedNode*)malloc(sizeof(LinkedNode));
                current->next->value = value;
                current->next->prev = current;
                current->next->next = next;
                next->prev = current->next;
                m_size++;
            }

            size_t removeIf(bool (*filter)(const T &)) override {
                size_t removed = 0;
                LinkedNode* current = m_sentinel->next;
                while (current && current != m_sentinel) {
                    LinkedNode* next = current->next;
                    if (filter(current->value)) {
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        m_size--;
                        free(current);
                        removed++;
                    }
                    current = next;
                }
                return removed;
            }

            void addFirst(const T& value) override {
                LinkedNode* next = m_sentinel->next;
                m_sentinel->next = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->next->value = value;
                m_sentinel->next->prev = m_sentinel;
                m_sentinel->next->next = next;
                next->prev = m_sentinel->next;
                m_size++;
            }

            void addLast(const T& value) override {
                LinkedNode* prev = m_sentinel->prev;
                m_sentinel->prev = (LinkedNode*)malloc(sizeof(LinkedNode));
                m_sentinel->prev->value = value;
                m_sentinel->prev->next = m_sentinel;
                m_sentinel->prev->prev = prev;
                prev->next = m_sentinel->prev;
                m_size++;
            }

            [[nodiscard]] T& first() override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot access an empty list");
                return m_sentinel->next->value;
            }

            [[nodiscard]] const T& first() const override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot access an empty list");
                return m_sentinel->next->value;
            }

            [[nodiscard]] T& last() override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot access an empty list");
                return m_sentinel->prev->value;
            }

            [[nodiscard]] const T& last() const override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot access an empty list");
                return m_sentinel->prev->value;
            }

            T removeFirst() override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot remove from an empty list");

                LinkedNode* first = m_sentinel->next;
                first->prev->next = first->next;
                first->next->prev = first->prev;
                T temp = first->value;
                m_size--;
                free(first);
                return temp;
            }

            T removeLast() override {
                // TODO: Change to assertion macro
                if (m_size == 0) fail("Cannot remove from an empty list");

                LinkedNode* last = m_sentinel->prev;
                last->prev->next = last->next;
                last->next->prev = last->prev;
                T temp = last->value;
                m_size--;
                free(last);
                return temp;
            }

            void clear() override {
                LinkedNode* current = m_sentinel->next;
                while (current && current != m_sentinel) {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    LinkedNode* temp = current;
                    current = current->next;
                    free(temp);
                }
                m_sentinel->next = m_sentinel;
                m_sentinel->prev = m_sentinel;
                m_size = 0;
            }

            void reverse() override {
                List<T>::reverse(); // TODO: Implement LinkedList.reverse()
            }

            [[nodiscard]] std::size_t size() const noexcept override {
                return m_size;
            }

            // Assignment Operators

            /**
             * @brief The copy assignment operator for LinkedList objects.
             * @details Reassigns the value of this object by copying the data of a LinkedList into this object.
             */
            LinkedList& operator=(const LinkedList& rhs) = default;

            /**
             * @brief The move assignment operator for LinkedList objects.
             * @details Reassigns the value of this object by moving the data of a LinkedList into this object.
             */
            LinkedList& operator=(LinkedList&& rhs) = default;

        private:

            /**
             * Called when a critical error occurs in this class. This should only be used in debug mode.
             * This is a placeholder method for future assertion utilities.
             * @param msg The failure message.
             */
            inline void fail(const char* msg = "Error occurred in LinkedList") const {
                assert(false);
            }

    };

}

#endif