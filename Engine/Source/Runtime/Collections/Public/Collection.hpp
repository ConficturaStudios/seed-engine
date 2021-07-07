/**
 * Collection.hpp
 *
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 *
 * This code is distributed as part of the Seed Engine project.
 *
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_COLLECTION_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_COLLECTION_H_

#include "CollectionsAPI.hpp"
#include "Iterator.hpp"
#include "Array.hpp"

namespace seedengine {

    /**
     * @brief A generic collection of T typed objects. A collection is an abstract, iterable representation
     *        used by all dynamically sized
     * @tparam T
     * @tparam IndexType
     */
    template <typename T, typename IndexType>
    class Collection : public Iterable<T, Iterator<T>>, public ReverseIterable<T, Iterator<T>> {

        public:
            /**
             * @brief The default constructor for Collection objects.
             * @details Constructs a new Collection with default initialization for all members.
             */
            Collection() = default;

            /**
             * @brief The destructor for Collection objects.
             * @details Called when an instance of Collection is deleted.
             */
            virtual ~Collection() = default;

            /**
             * Sets the value associated with the specified index to the provided value.
             * @param index The index to set at.
             * @param value The new value.
             * @return The previously stored value.
             */
            virtual T set(IndexType index, const T& value) = 0;

            /**
             * Gets the value associated with the specified index.
             * @param index The index to get.
             * @return The value at the index.
             */
            [[nodiscard]] virtual T& get(IndexType index) = 0;

            /**
             * Gets the value associated with the specified index.
             * @param index The index to get.
             * @return The value at the index.
             */
            [[nodiscard]] virtual const T& get(IndexType index) const = 0;

            /**
             * Gets the number of elements in this collection.
             * @return The number of elements in this collection.
             */
            [[nodiscard]] virtual size_t size() const noexcept = 0;

            /**
             * Returns true if there are no elements in this collection.
             * @return True if there are no elements in this collection.
             */
            [[nodiscard]] inline bool isEmpty() const noexcept { return size() == 0; }

            /**
             * Searches the collection for the provided element, removing it if found.
             * @param element The element to remove.
             * @return True if the element was found and removed.
             */
            virtual bool removeElement(const T& element) = 0;

            /**
             * Removes the element with the specified index.
             * @param index The index of the element to remove.
             * @return The removed object.
             */
            virtual T remove(IndexType index) = 0;

            /**
             * Checks if this collection contains the specified element.
             * @param element The element to search for.
             * @return True if the element was found.
             */
            [[nodiscard]] virtual bool contains(const T& element) const = 0;

            /**
             * Iterates through this collection, removing each element matching the
             * check condition provided.
             * @param check The function used to evaluate if each element should be removed.
             */
            virtual void removeIf(bool (*check)(const T&)) {
                for (size_t i = 0; i < size(); i++) {
                    if (check(get(i))) this->remove(i--);
                }
            }

            /**
             * Removes all elements from this collection.
             */
            virtual void clear() = 0;

            /**
             * Converts this collection to an array.
             * @return This collection represented as an array.
             */
            [[nodiscard]] virtual Array<T> toArray() const {
                Array<T> result(size());
                int i = 0;
                for (const T& element : *this) {
                    result[i++] = element;
                }
                return result;
            }

            [[nodiscard]] virtual T& operator[](IndexType index) {
                return get(index);
            }

            [[nodiscard]] virtual const T& operator[](IndexType index) const {
                return get(index);
            }
    };

}


#endif
