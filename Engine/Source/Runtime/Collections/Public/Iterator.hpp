/**
 * @file Iterator.hpp
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

#include <cstdint>

namespace seedengine {

    // Forward declare Iterator

    template <typename T>
    class Iterator;
    
    /**
     * @brief An interface representing an Iterator implementation compatible with range
     *        based for loops.
     * @details An Iterator interface used to create custom Iterators compatible
     *          with range based for loops. This interface only enforces iteration
     *          in the forward direction of a collection.
     *          Because of the nature of C++ polymorphism, this class is wrapped into
     *          a concrete Iterator<T> instance in most uses.
     * 
     * @tparam T The type of data iterated over by this Iterator.
     */
    template <typename T>
    struct ENGINE_API IteratorBase {

        virtual ~IteratorBase() = default;

        [[nodiscard]] virtual       T& operator*() = 0;
        [[nodiscard]] virtual const T& operator*() const = 0;

        [[nodiscard]] virtual bool operator==(const IteratorBase<T>& rhs) const = 0;
        [[nodiscard]] virtual bool operator!=(const IteratorBase<T>& rhs) const = 0;
        
        [[nodiscard]] virtual bool operator==(const T& rhs) const = 0;
        [[nodiscard]] virtual bool operator!=(const T& rhs) const = 0;

        virtual IteratorBase<T>& operator++() = 0;
    };

    /**
     * @brief An iterator object compatible with range based for loops. This object
     *        uses an internal pointer to implementation.
     * @details
     * An Iterator interface used to create custom Iterators compatible
     * with range based for loops. This interface only enforces iteration
     * in the forward direction of a collection.
     * This is a concrete class with an internal pointer to implementation of an
     * instance of the IteratorBase class. This design is used to allow Iterable
     * and ReverseIterable objects to return their iterators by value.
     * 
     * @tparam T The type of data iterated over by this Iterator.
     */
    template <typename T>
    class ENGINE_API Iterator final {
        private:
            IteratorBase<T>* instance;
            
        public:
        
            /**
             * @brief Constructs a new Iterator wrapped around the provided implementation
             *        pointer. This pointer will be deleted when this object is destroyed.
             * 
             * @param ptr The pointer to the Iterator implementation.
             */
            constexpr explicit Iterator(IteratorBase<T>* ptr) : instance(ptr) { }
            
            /**
             * @brief Destroys the Iterator object and internal implementation pointer.
             */
            ~Iterator() {
                delete instance;
            }
            
            [[nodiscard]] T& operator*() {
                return instance->operator*();
            }
            
            [[nodiscard]] const T& operator*() const {
                return instance->operator*();
            }
        
            [[nodiscard]] bool operator==(const IteratorBase<T>& rhs) const {
                return instance->operator==(rhs);
            }
            [[nodiscard]] bool operator!=(const IteratorBase<T>& rhs) const {
                return instance->operator!=(rhs);
            }
        
            [[nodiscard]] bool operator==(const Iterator<T>& rhs) const {
                return instance->operator==(*rhs.instance);
            }
            
            [[nodiscard]] bool operator!=(const Iterator<T>& rhs) const {
                return instance->operator!=(*rhs.instance);
            }
            
            [[nodiscard]] bool operator==(const T& rhs) const {
                return instance->operator==(rhs);
            }
            
            [[nodiscard]] bool operator!=(const T& rhs) const {
                return instance->operator!==(rhs);
            }
        
            Iterator<T>& operator++() {
                instance->operator++();
                return *this;
            }
    };

    /**
     * @brief An interface used to represent an object that can be iterated on
     *        within a range based for loop.
     * @details
     * An interface used to represent an object that can be iterated on
     * within a range based for loop. This interface only enforces forward
     * iteration, not reverse iteration.
     * 
     * Each method is expected to return an object that is a valid iterator. By default, the
     * return type is set to the generic Iterator object for type T. It is recommended to
     * either use the default, or a pointer type.
     * When using the Iterator wrapper class, the type of Iterator returned by each function
     * is not strict, only requiring that he Iterator types are comparable. This is to allow for custom
     * behavior such as using a sentinel end Iterator.
     *
     * @tparam T The type of data this object iterates over.
     * @tparam ItrType The type of iterator returned by each function.
     */
    template <typename T, typename ItrType = Iterator<T>>
    struct ENGINE_API Iterable {

        /** The type of iterator used by this iterable object. */
        using IteratorType = ItrType;

        /**
         * @brief Gets the iterator at the beginning of the collection.
         * @return IteratorType The iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual IteratorType begin() = 0;
        /**
         * @brief Gets the iterator at the beginning of the collection.
         * @return const IteratorType The iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const IteratorType begin() const = 0;
        /**
         * @brief Gets the iterator at the beginning of the collection.
         * @return const IteratorType The iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const IteratorType cbegin() const = 0;
        
        /**
         * @brief Gets the iterator at the end of the collection.
         * @return IteratorType The iterator at the end of the collection.
         */
        [[nodiscard]] virtual IteratorType end() = 0;
        /**
         * @brief Gets the iterator at the end of the collection.
         * @return const IteratorType The iterator at the end of the collection.
         */
        [[nodiscard]] virtual const IteratorType end() const = 0;
        /**
         * @brief Gets the iterator at the end of the collection.
         * @return const IteratorType The iterator at the end of the collection.
         */
        [[nodiscard]] virtual const IteratorType cend() const = 0;
    };

    /**
     * @brief An interface used to represent an object that can be reverse iterated on
     *        within a range based for loop.
     * @details
     * An interface used to represent an object that can be iterated on
     * within a range based for loop. This interface only enforces reverse
     * iteration, not forward iteration.
     * 
     * Each method is expected to return an object that is a valid iterator. By default, the
     * return type is set to the generic Iterator object for type T. It is recommended to
     * either use the default, or a pointer type.
     * When using the Iterator wrapper class, the type of Iterator returned by each function
     * is not strict, only requiring that he Iterator types are comparable. This is to allow for custom
     * behavior such as using a sentinel end Iterator.
     * 
     * @tparam T The type of data this object iterates over.
     * @tparam ItrType The type of iterator returned by each function.
     */
    template <typename T, typename ItrType = Iterator<T>>
    struct ENGINE_API ReverseIterable {

        /** The type of iterator used by this iterable object. */
        using RIteratorType = ItrType;
        
        /**
         * @brief Gets the reverse iterator at the beginning of the collection.
         * @return IteratorType The reverse iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual RIteratorType rbegin() = 0;
        /**
         * @brief Gets the reverse iterator at the beginning of the collection.
         * @return const IteratorType The reverse iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const RIteratorType rbegin() const = 0;
        /**
         * @brief Gets the reverse iterator at the beginning of the collection.
         * @return const IteratorType The reverse iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const RIteratorType crbegin() const = 0;
        
        /**
         * @brief Gets the reverse iterator at the end of the collection.
         * @return IteratorType The reverse iterator at the end of the collection.
         */
        [[nodiscard]] virtual RIteratorType rend() = 0;
        /**
         * @brief Gets the reverse iterator at the end of the collection.
         * @return const IteratorType The reverse iterator at the end of the collection.
         */
        [[nodiscard]] virtual const RIteratorType rend() const = 0;
        /**
         * @brief Gets the reverse iterator at the end of the collection.
         * @return const IteratorType The reverse iterator at the end of the collection.
         */
        [[nodiscard]] virtual const RIteratorType crend() const = 0;
    };

}

#endif