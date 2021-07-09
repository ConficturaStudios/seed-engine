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
     * @brief A generic collection of T typed objects.
     * @details
     * A generic collection of T typed objects. A collection is an abstract, iterable representation
     * used by all dynamically sized sets of data such LinkedLists, Trees, Queues, and Maps.
     * @tparam T The type of data stored in this collection.
     */
    template <typename T>
    class Collection : public Iterable<T, Iterator<T>> {

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
             * @brief Searches the collection for the provided elements, removing each if found.
             * @details
             * Searches the collection for the provided elements, removing each if found. The number of
             * elements successfully removed by this function are returned. By default, this function
             * uses removeElement for each removal.
             * @param elements The elements to remove.
             * @return The number of elements successfully removed from this collection.
             */
            virtual size_t removeElements(const Collection<T>& elements) {
                size_t removed = 0;
                for (const T& element : elements) {
                    if (removeElement(element)) removed++;
                }
                return removed;
            }

            /**
             * @brief Iterates through this collection, removing each element matching the
             *        check condition provided.
             * @details
             * Iterates through this collection, removing each element matching the
             * check condition provided using the removeElement(element) function by default. It is highly
             * recommended to override this behavior in any derived class.
             * @param filter The function used to evaluate if each element should be removed.
             * @return The number of elements that were removed.
             */
            virtual size_t removeIf(bool (*filter)(const T&)) {
                size_t removed = 0;
                Array<T> elements = this->toArray();
                for (const T& element : elements) {
                    if (filter(element)) {
                        this->removeElement(element);
                        removed++;
                    }
                }
                return removed;
            }

            /**
             * @brief Removes all elements from this collection except for those contained by the
             *        provided collection.
             * @details
             * Removes all elements from this collection except for those contained by the
             * provided collection. The number of elements remaining after this operation are returned.
             * By default, the removeElement(element) function is used.
             * @param elements The elements that should be retained by this collection.
             * @return The number of elements retained by this collection.
             */
            virtual size_t retainElements(const Collection<T>& elements) {
                Array<T> content = this->toArray();
                for (const T& element : content) {
                    if (!elements.contains(element)) removeElement(element);
                }
                return this->size();
            }

            /**
             * @brief Removes all elements from this collection not matching the provided predicate.
             * @details
             * Removes all elements from this collection not matching the provided predicate. The number of
             * elements remaining after this operation are returned. By default, the removeElement(element)
             * function is used.
             * @param filter The predicate function used to evaluate if each element should be retained.
             * @return The number of elements retained by this collection.
             */
            virtual size_t retainIf(bool (*filter)(const T&)) {
                // TODO: Throw exception or provide check for null predicate
                Array<T> content = this->toArray();
                for (const T& element : content) {
                    if (!filter(element)) removeElement(element);
                }
                return this->size();
            }

            /**
             * @brief Checks if this collection contains the specified element.
             * @details
             * Checks if this collection contains the specified element. The exact behavior
             * and performance of this function is dependent on the exact type of collection
             * it is being called on.
             * @param element The element to search for.
             * @return True if the element was found.
             */
            [[nodiscard]] virtual bool contains(const T& element) const = 0;

            /**
             * @brief Checks if this collection contains all elements specified by the provided collection.
             * @details
             * Checks if this collection contains all elements specified by the provided collection. If an
             * empty collection is provided, true is returned.
             * @param elements The elements to search for.
             * @return True if all elements requested were found.
             */
            [[nodiscard]] virtual bool containsAll(const Collection<T>& elements) const {
                bool result = true;
                for (const T& element : elements) {
                    result &= this->contains(element);
                }
                return result;
            }

            /**
             * @brief Removes all elements from this collection.
             * @details
             * Removes all elements from this collection. The exact implementation of this
             * function is defined by its subclasses.
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
    };

}


#endif
