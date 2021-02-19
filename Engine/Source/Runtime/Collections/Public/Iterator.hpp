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
        virtual IteratorBase<T>& operator++(int) = 0;
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
            constexpr Iterator(IteratorBase<T>* ptr) : instance(ptr) { }
            
            /**
             * @brief The copy constructor for Iterator objects.
             * @details Constructs a new Iterator by copying an existing Iterator.
             */
            constexpr Iterator(const Iterator& rhs) : instance(rhs.ptr) { }
            
            /**
             * @brief The move constructor for Iterator objects.
             * @details Constructs a new Iterator by moving the data of a Iterator into this object.
             */
            constexpr Iterator(Iterator&& rhs) : instance(rhs.ptr) { }
            
            /**
             * @brief Destroys the Iterator object and internal implementation pointer.
             */
            ~Iterator() {
                delete instance;
            }
            
            Iterator& operator=(const Iterator& rhs) {
                instance = rhs.instance;
            }
            
            Iterator& operator=(Iterator&& rhs) {
                instance = rhs.instance;
                rhs.instance = nullptr;
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
                return instance->operator==(rhs.instance);
            }
            
            [[nodiscard]] bool operator!=(const Iterator<T>& rhs) const {
                return instance->operator!=(rhs.instance);
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
            
            Iterator<T>& operator++(int) {
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
     * Each method is expected to return an instance of the Iterator interface. The
     * type of Iterator returned by each function is not strict, only requiring that
     * the Iterator types are comparable. This is to allow for custom behavior such as
     * using a sentinel end Iterator.
     * 
     * @tparam T The type of data this object iterates over.
     */
    template <typename T>
    struct ENGINE_API Iterable {

        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual Iterator<T> begin() = 0;
        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return const Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> begin() const = 0;
        /**
         * @brief Gets the Iterator at the beginning of the collection.
         * @return const Iterator<T> The Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> cbegin() const = 0;
        
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return Iterator<T> The Iterator at the end of the collection.
         */
        [[nodiscard]] virtual Iterator<T> end() = 0;
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return const Iterator<T> The Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> end() const = 0;
        /**
         * @brief Gets the Iterator at the end of the collection.
         * @return const Iterator<T> The Iterator at the end of the collection.
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
    struct ENGINE_API ReverseIterable {
        
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual Iterator<T> rbegin() = 0;
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return const Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> rbegin() const = 0;
        /**
         * @brief Gets the reverse Iterator at the beginning of the collection.
         * @return const Iterator<T> The reverse Iterator at the beginning of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> crbegin() const = 0;
        
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual Iterator<T> rend() = 0;
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return const Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> rend() const = 0;
        /**
         * @brief Gets the reverse Iterator at the end of the collection.
         * @return const Iterator<T> The reverse Iterator at the end of the collection.
         */
        [[nodiscard]] virtual const Iterator<T> crend() const = 0;
    };

}

#endif