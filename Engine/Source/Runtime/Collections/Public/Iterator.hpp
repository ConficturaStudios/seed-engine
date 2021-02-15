/**
 * Iterator.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ITERATOR_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ITERATOR_H_

#include "CollectionsAPI.hpp"

namespace seedengine {
    
    /**
     * @brief An interface representing an Iterator compatible with range based
     *        for loops.
     * @details An Iterator interface used to create custom Iterators compatible
     *          with range based for loops. This interface only enforces iteration
     *          in the forward direction of a collection.
     * 
     * @tparam T The type of data iterated over by this Iterator.
     */
    template <typename T>
    struct ENGINE_API Iterator {
        [[nodiscard]] virtual       T& operator*() = 0;
        [[nodiscard]] virtual const T& operator*() const = 0;

        [[nodiscard]] virtual bool operator==(const Iterator<T>& rhs) const = 0;
        [[nodiscard]] virtual bool operator!=(const Iterator<T>& rhs) const = 0;
        
        [[nodiscard]] virtual bool operator==(const T& rhs) const = 0;
        [[nodiscard]] virtual bool operator!=(const T& rhs) const = 0;

        virtual Iterator<T>& operator++() = 0;
        virtual Iterator<T>& operator++(int) = 0;
    };

    /**
     * @brief An interface used to represent an object that can be iterated on
     *        within a range based for loop.
     * @details
     * An interface used to represent an object that can be iterated on
     * within a range based for loop. This interface only enforces forward
     * iteration, not reverse iteration.
     * 
     * Each method is expected to return an instance of the Iterator interface. The
     * type of Iterator returned by each function is not strict, only requiring that
     * the Iterator types are comparable. This is to allow for custom behavior such as
     * using a sentinel end Iterator.
     * 
     * @tparam T The type of data this object iterates over.
     */
    template <typename T>
    struct Iterable {

        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual Iterator<T> begin() = 0;
        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> begin() const = 0;
        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> cbegin() const = 0;
        
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return Iterator<T> The Iterator at the end of the collection.
         */
        [[nodiscard]] virtual Iterator<T> end() = 0;
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return Iterator<T> The Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> end() const = 0;
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return Iterator<T> The Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> cend() const = 0;
    };

    /**
     * @brief An interface used to represent an object that can be reverse iterated on
     *        within a range based for loop.
     * @details
     * An interface used to represent an object that can be iterated on
     * within a range based for loop. This interface only enforces reverse
     * iteration, not forward iteration.
     * 
     * Each method is expected to return an instance of the Iterator interface. The
     * type of Iterator returned by each function is not strict, only requiring that
     * the Iterator types are comparable. This is to allow for custom behavior such as
     * using a sentinel end Iterator.
     * 
     * @tparam T The type of data this object iterates over.
     */
    template <typename T>
    struct ReverseIterable {
        
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual Iterator<T> rbegin() = 0;
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> rbegin() const = 0;
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> crbegin() const = 0;
        
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual Iterator<T> rend() = 0;
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> rend() const = 0;
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> crend() const = 0;
    };

}

#endif