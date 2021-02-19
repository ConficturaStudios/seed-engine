/**
 * Array.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COLLECTIONS_ARRAY_H_

#include <cstddef>

#include "CollectionsAPI.hpp"
#include "Iterator.hpp"

namespace seedengine {

    /**
     * @brief A generic stack allocated Array of a fixed size N.
     * 
     * @tparam T The type of data stored within this Array.
     * @tparam N The number of elements in this Array.
     */
    template <typename T, std::size_t N>
    class ENGINE_API Array : public Iterable<T>, public ReverseIterable<T> {

        private:
        // Data members

            T data[N];

        private:
        // Iterator classes

            struct ArrayIterator : public IteratorBase<T> {

                T* ptr;

                ArrayIterator(T* ptr) : ptr(ptr) { }

                virtual ~ArrayIterator() = default;

                [[nodiscard]] virtual T& operator*() override {
                    return *ptr;
                }

                [[nodiscard]] virtual const T& operator*() const override {
                    return *ptr;
                }

                [[nodiscard]] virtual bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->ptr == dynamic_cast<const ArrayIterator&>(rhs).ptr;
                }

                [[nodiscard]] virtual bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->ptr != dynamic_cast<const ArrayIterator&>(rhs).ptr;
                }
                
                [[nodiscard]] virtual bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] virtual bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                virtual IteratorBase<T>& operator++() override {
                    ++ptr;
                    return *this;
                }

                virtual IteratorBase<T>& operator++(int) override {
                    ptr++;
                    return *this;
                }
            };

            struct ArrayReverseIterator : public IteratorBase<T> {

                T* ptr;

                ArrayReverseIterator(T* ptr) : ptr(ptr) { }

                virtual ~ArrayReverseIterator() = default;

                [[nodiscard]] virtual T& operator*() override {
                    return *ptr;
                }

                [[nodiscard]] virtual const T& operator*() const override {
                    return *ptr;
                }

                [[nodiscard]] virtual bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->ptr == dynamic_cast<const ArrayReverseIterator&>(rhs).ptr;
                }

                [[nodiscard]] virtual bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->ptr != dynamic_cast<const ArrayReverseIterator&>(rhs).ptr;
                }
                
                [[nodiscard]] virtual bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] virtual bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                virtual IteratorBase<T>& operator++() override {
                    --ptr;
                    return *this;
                }

                virtual IteratorBase<T>& operator++(int) override {
                    ptr--;
                    return *this;
                }
            };

        public:

            /** The type of elements stored in this Array type. */
            using Type = T;
            /** The number of elements stored in this Array type. */
            static constexpr const std::size_t Size = N;

        // Constructors and destructor

            /**
             * @brief The default constructor for Array objects.
             * @details Constructs a new Array with default initialization for all members.
             */
            Array() {
                
            }

            /**
             * @brief The copy constructor for Array objects.
             * @details Constructs a new Array by copying an existing Array.
             */
            Array(const Array& ref) = default;
            
            /**
             * @brief The move constructor for Array objects.
             * @details Constructs a new Array by moving the data of a Array into this object.
             */
            Array(Array&& ref) = default;

            /**
             * @brief The destructor for Array objects.
             * @details Called when an instance of Array is deleted.
             */
            virtual ~Array() {
                
            }

        // Functions

        // Override Functions

        // Iterator Functions

            [[nodiscard]] virtual Iterator<T> begin() override {
                return Iterator(new ArrayIterator(&data[0]));
            }
            [[nodiscard]] virtual const Iterator<T> begin() const override {
                return const Iterator(new ArrayIterator(&data[0]));
            }
            [[nodiscard]] virtual const Iterator<T> cbegin() const override {
                return const Iterator(new ArrayIterator(&data[0]));
            }
            
            [[nodiscard]] virtual Iterator<T> end() override {
                return Iterator(new ArrayIterator(&data[N]));
            }
            [[nodiscard]] virtual const Iterator<T> end() const override {
                return const Iterator(new ArrayIterator(&data[N]));
            }
            [[nodiscard]] virtual const Iterator<T> cend() const override {
                return const Iterator(new ArrayIterator(&data[N]));
            }

        // Reverse Iterator Functions
            
            [[nodiscard]] virtual Iterator<T> rbegin() override {
                return Iterator(new ArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] virtual const Iterator<T> rbegin() const override {
                return const Iterator(new ArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] virtual const Iterator<T> crbegin() const override {
                return const Iterator(new ArrayReverseIterator(&data[N - 1]));
            }

            
            [[nodiscard]] virtual Iterator<T> rend() override {
                return Iterator(new ArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] virtual const Iterator<T> rend() const override {
                return const Iterator(new ArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] virtual const Iterator<T> crend() const override {
                return const Iterator(new ArrayReverseIterator(&data[-1]));
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Array objects.
             * @details Reassigns the value of this object by copying the data of a Array into this object.
             */
            Array& operator=(const Array& rhs) = default;

            /**
             * @brief The move assignment operator for Array objects.
             * @details Reassigns the value of this object by moving the data of a Array into this object.
             */
            Array& operator=(Array&& rhs) = default;

        protected:

        private:

    };

}

#endif