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
#include <initializer_list>

#include "CollectionsAPI.hpp"
#include "Iterator.hpp"

namespace seedengine {

    /**
     * @brief A generic Array of a fixed size N. N must be known at compile time.
     * @details A generic array with a fixed size known at compile time. This array type
     *          has a fixed size, allowing for compiler optimizations and a consistent
     *          memory layout. The only data stored in this class is the N size array
     *          of T objects.
     * 
     * @tparam T The type of data stored within this Array.
     * @tparam N The number of elements in this Array.
     */
    template <typename T, std::size_t N>
    class ENGINE_API FixedArray final : public Iterable<T>, public ReverseIterable<T> {

        static_assert(N > 0, "An array cannot have a size of 0");

        private:
        // Data members

            /** The internal fixed size array data. */
            T data[N];

        private:
        // Iterator classes

            // TODO: Document FixedArray Iterators

            struct FixedArrayIterator final : public IteratorBase<T> {

                T* ptr;

                explicit FixedArrayIterator(T* ptr) : ptr(ptr) { }

                ~FixedArrayIterator() = default;

                [[nodiscard]] T& operator*() override {
                    return *ptr;
                }

                [[nodiscard]] const T& operator*() const override {
                    return *ptr;
                }

                [[nodiscard]] bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->ptr == dynamic_cast<const FixedArrayIterator&>(rhs).ptr;
                }

                [[nodiscard]] bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->ptr != dynamic_cast<const FixedArrayIterator&>(rhs).ptr;
                }
                
                [[nodiscard]] bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                IteratorBase<T>& operator++() override {
                    ptr++;
                    return *this;
                }
            };

            struct FixedArrayReverseIterator : public IteratorBase<T> {

                T* ptr;

                explicit FixedArrayReverseIterator(T* ptr) : ptr(ptr) { }

                virtual ~FixedArrayReverseIterator() = default;

                [[nodiscard]] T& operator*() override {
                    return *ptr;
                }

                [[nodiscard]] const T& operator*() const override {
                    return *ptr;
                }

                [[nodiscard]] bool operator==(const IteratorBase<T>& rhs) const override {
                    return this->ptr == dynamic_cast<const FixedArrayReverseIterator&>(rhs).ptr;
                }

                [[nodiscard]] bool operator!=(const IteratorBase<T>& rhs) const override {
                    return this->ptr != dynamic_cast<const FixedArrayReverseIterator&>(rhs).ptr;
                }
                
                [[nodiscard]] bool operator==(const T& rhs) const override {
                    return this->operator*() == rhs;
                }

                [[nodiscard]] bool operator!=(const T& rhs) const override {
                    return this->operator*() != rhs;
                }

                IteratorBase<T>& operator++() override {
                    --ptr;
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
             * @brief The default constructor for FixedArray objects.
             * @details Constructs a new empty FixedArray with no initialization for any members.
             *          Initializiation is skipped to increase performance and remove the
             *          requirement for T to have a default constructor.
             */
            FixedArray() = default;

            /**
             * @brief The copy constructor for FixedArray objects.
             * @details Constructs a new FixedArray by copying an existing FixedArray.
             */
            FixedArray(const FixedArray& ref) = default;
            
            /**
             * @brief The move constructor for FixedArray objects.
             * @details Constructs a new FixedArray by moving the data of a FixedArray
             *          into this object.
             */
            FixedArray(FixedArray&& ref) noexcept = default;

            /**
             * @brief The destructor for FixedArray objects.
             * @details Called when an instance of FixedArray is deleted.
             */
            virtual ~FixedArray() {
                delete[] data;
            }

        // Functions

            /**
             * @brief Gets the underlying array pointer of this instance.
             * @return T* The underlying array pointer of this instance.
             */
            [[nodiscard]] T* getData() {
                return data;
            }

            /**
             * @brief Gets the underlying array pointer of this instance.
             * @return const T* The underlying array pointer of this instance.
             */
            [[nodiscard]] const T* getData() const {
                return data;
            }

            /**
             * @brief Returns the number of elements in this array.
             * @return std::size_t The number of elements in this array.
             */
            [[nodiscard]] std::size_t size() const {
                return Size;
            }


            /**
             * @brief Performs a linear search to find the specified element.
             * @details Performs a linear search to find the specified element. Returns the index
             *          the element was found at if it exists. Otherwise, a value of -1 is returned.
             * 
             * @param element The element to search for.
             * @return int64_t The index that the element was found at, or -1 if it was not found.
             */
            [[nodiscard]] int64_t find(const T& element) const {
                for (int i = 0; i < N; i++) {
                    if (data[i] == element) return i;
                }
                return -1;
            }

            /**
             * @brief Performs a linear search to find the specified element.
             * @details Performs a linear search to find the specified element. Returns true if
             *          the element was found and passes the index it was found at to outIndex. If
             *          the element was not found outIndex will be set to -1.
             * 
             * @param element The element to search for.
             * @param outIndex The output destination for the index the element was found at.
             * @return true If the element was found.
             * @return false If the element was not found.
             */
            bool find(const T& element, int64_t& outIndex) const {
                return (outIndex = find(element)) != -1;
            }

            /**
             * @brief Swaps the values stored at the two specified indices.
             * 
             * @param first The first index to swap.
             * @param second The second index to swap.
             */
            void swap(std::size_t first, std::size_t second) {
                T temp = data[first];
                data[first] = data[second];
                data[second] = temp;
            }

            /**
             * @brief Copies the elements from index Start (inclusive) to End (exclusive) into
             *        the provided sub array object.
             * 
             * @tparam Start The first index to copy, inclusive.
             * @tparam End The last index to copy, exclusive.
             * @param target The array to copy the values into.
             */
            template <std::size_t Start, std::size_t End>
            [[nodiscard]] void copyToSubarray(FixedArray<T, End - Start>& target) const {
                for (std::size_t i = Start; i < End; i++) {
                    target[i] = T(data[i]);
                }
            }

        // Override Functions

        // Iterator Functions

            [[nodiscard]] virtual Iterator<T> begin() override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            [[nodiscard]] virtual const Iterator<T> begin() const override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            [[nodiscard]] virtual const Iterator<T> cbegin() const override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            
            [[nodiscard]] virtual Iterator<T> end() override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }
            [[nodiscard]] virtual const Iterator<T> end() const override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }
            [[nodiscard]] virtual const Iterator<T> cend() const override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }

        // Reverse Iterator Functions
            
            [[nodiscard]] virtual Iterator<T> rbegin() override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] virtual const Iterator<T> rbegin() const override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] virtual const Iterator<T> crbegin() const override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            
            [[nodiscard]] Iterator<T> rend() override {
                return Iterator(new FixedArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] Iterator<T> rend() const override {
                return Iterator(new FixedArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] Iterator<T> crend() const override {
                return Iterator(new FixedArrayReverseIterator(&data[-1]));
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for FixedArray objects.
             * @details Reassigns the value of this object by copying the data of a FixedArray
             *          into this object.
             */
            FixedArray& operator=(const FixedArray& rhs) = default;

            /**
             * @brief The move assignment operator for FixedArray objects.
             * @details Reassigns the value of this object by moving the data of a FixedArray
             *          into this object.
             */
            FixedArray& operator=(FixedArray&& rhs) noexcept = default;

        // Operators

            [[nodiscard]] T& operator[](std::size_t i) {
                // TODO: Add flag and behavior to perform optional bounds checking
                return data[i];
            }

            [[nodiscard]] const T& operator[](std::size_t i) const {
                return data[i];
            } 

        protected:

        private:

    };

}

#endif