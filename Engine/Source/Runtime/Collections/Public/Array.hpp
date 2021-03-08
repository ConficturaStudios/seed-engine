/**
 * @file Array.hpp
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

#include <cstdlib>
#include <cstddef>
#include <initializer_list>

#include "CollectionsAPI.hpp"
#include "Iterator.hpp"

namespace seedengine {

    // Forward declaration of Array

    template <typename>
    class Array;

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
            [[nodiscard]] inline T* getData() {
                return data;
            }

            /**
             * @brief Gets the underlying array pointer of this instance.
             * @return const T* The underlying array pointer of this instance.
             */
            [[nodiscard]] inline const T* getData() const {
                return data;
            }

            /**
             * @brief Returns the number of elements in this array.
             * @return std::size_t The number of elements in this array.
             */
            [[nodiscard]] inline std::size_t size() const {
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
            void copyToSubarray(FixedArray<T, End - Start>& target) const {
                for (std::size_t i = Start; i < End; i++) {
                    target[i - Start] = T(data[i]);
                }
            }

            /**
             * @brief Copies the elements from index start (inclusive) to end (exclusive) into
             *        a new array object.
             *
             * @param start The first index to copy, inclusive.
             * @param end The last index to copy, exclusive.
             * @return A sub array of elements from this array.
             */
            [[nodiscard]] Array<T> subarray(std::size_t start, std::size_t end) const {
                Array<T> target(end - start);
                for (std::size_t i = start; i < end; i++) {
                    target[i - start] = T(data[i]);
                }
                return target;
            }

            /**
             * @brief Concatenates this array with another, returning a new Array with the contents of
             *        the parameter appended to this array.
             * @tparam M The size of the fixed array to append.
             * @param array The array to concatenate with.
             * @return The resulting combined array.
             */
            template <std::size_t M>
            [[nodiscard]] FixedArray<T, N + M> concat(const FixedArray<T, M>& array) const {
                FixedArray<T, N + M> result;
                int i = 0;
                for (const T& element : *this) {
                    result[i++] = T(data[i]);
                }
                for (const T& element : array) {
                    result[i++] = T(array[i - N]);
                }
                return result;
            }

            /**
             *
             * @return
             */
            [[nodiscard]] Array<T> toArray() const {
                Array<T> result(N);
                for (int i = 0; i < N; i++) {
                    result[i] = data[i];
                }
                return result;
            }

        // Override Functions

        // Iterator Functions

            [[nodiscard]] Iterator<T> begin() override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            [[nodiscard]] const Iterator<T> begin() const override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            [[nodiscard]] const Iterator<T> cbegin() const override {
                return Iterator(new FixedArrayIterator(&data[0]));
            }
            
            [[nodiscard]] Iterator<T> end() override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }
            [[nodiscard]] const Iterator<T> end() const override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }
            [[nodiscard]] const Iterator<T> cend() const override {
                return Iterator(new FixedArrayIterator(&data[N]));
            }

        // Reverse Iterator Functions
            
            [[nodiscard]] Iterator<T> rbegin() override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] const Iterator<T> rbegin() const override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            [[nodiscard]] const Iterator<T> crbegin() const override {
                return Iterator(new FixedArrayReverseIterator(&data[N - 1]));
            }

            
            [[nodiscard]] Iterator<T> rend() override {
                return Iterator(new FixedArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] const Iterator<T> rend() const override {
                return Iterator(new FixedArrayReverseIterator(&data[-1]));
            }

            [[nodiscard]] const Iterator<T> crend() const override {
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

    };

    /**
     * @brief A generic Array of T typed elements. This array can be resized dynamically.
     * @details A generic array with a dynamic size specified at runtime. This array type
     *          can have any number of elements, but does not support reallocation after its
     *          initial creation.
     *
     * @tparam T The type of data stored within this Array.
     */
    template <typename T>
    class ENGINE_API Array final : public Iterable<T, T*>, public ReverseIterable<T, T*> {

    private:
        // Data members

        /** The internal array data. */
        T* data;

        /** The number of elements stored in this Array. */
        std::size_t length;

    public:

        /** The type of elements stored in this Array type. */
        using Type = T;

        // Constructors and destructor

        /**
         * @brief (Deleted) The default constructor for Array objects.
         * @warning Deleted
         */
        Array() = delete;

        /**
         * @brief Constructs an empty array with the specified size.
         * @details Constructs a new empty Array with no initialization for any members.
         *          Initialization is skipped to increase performance and remove the
         *          requirement for T to have a default constructor.
         * @param size The number of elements to allocate.
         */
        explicit Array(std::size_t size) {
            data = (T*)malloc(size * sizeof(T));
            length = size;
        }

        /**
         * @brief Constructs an array from the provided initializer list.
         * @details Constructs a new Array from the provided initializer list. The size
         *          of this array is determined implicitly by the number of elements in the
         *          list.
         * @param list The initializer list to construct this array from.
         */
        Array(std::initializer_list<T> list) {
            data = (T*)malloc(list.size() * sizeof(T));
            int i = 0;
            for (const T& element : list) {
                data[i++] = element;
            }
            length = list.size();
        }

        /**
         * @brief The copy constructor for Array objects.
         * @details Constructs a new Array by copying an existing Array.
         */
        Array(const Array& ref) {
            data = (T*)malloc(ref.size * sizeof(T));
            int i = 0;
            for (T element : ref) {
                data[i++] = element;
            }
            length = ref.size;
        }

        /**
         * @brief The move constructor for Array objects.
         * @details Constructs a new Array by moving the data of a Array
         *          into this object.
         */
        Array(Array&& ref) noexcept {
            data = ref.data;
            ref.data = nullptr;
            length = ref.size;
        }

        /**
         * @brief The destructor for Array objects.
         * @details Called when an instance of Array is deleted.
         */
        ~Array() {
            free(data);
        }

        // Functions

        /**
         * @brief Gets the underlying array pointer of this instance.
         * @return T* The underlying array pointer of this instance.
         */
        [[nodiscard]] inline T* getData() {
            return data;
        }

        /**
         * @brief Gets the underlying array pointer of this instance.
         * @return const T* The underlying array pointer of this instance.
         */
        [[nodiscard]] inline const T* getData() const {
            return data;
        }

        /**
         * @brief Returns the number of elements in this array.
         * @return std::size_t The number of elements in this array.
         */
        [[nodiscard]] inline std::size_t size() const {
            return length;
        }

        /**
         * @brief Performs a linear search to find the specified element.
         * @details Performs a linear search to find the specified element. Returns the index
         *          the element was found at if it exists. Otherwise, a value of -1 is returned.
         *
         * @param element The element to search for.
         * @return The index that the element was found at, or -1 if it was not found.
         */
        [[nodiscard]] int64_t find(const T& element) const {
            for (int i = 0; i < length; i++) {
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
         * @return True if the element was found.
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
         * @brief Copies the elements from index start (inclusive) to end (exclusive) into
         *        a new array object.
         *
         * @param start The first index to copy, inclusive.
         * @param end The last index to copy, exclusive.
         * @return A sub array of elements from this array.
         */
        [[nodiscard]] Array<T> subarray(std::size_t start, std::size_t end) const {
            Array<T> target(end - start);
            for (std::size_t i = start; i < end; i++) {
                target[i - start] = T(data[i]);
            }
            return target;
        }

        /**
         * @brief Concatenates this array with another, returning a new Array with the contents of
         *        the parameter appended to this array.
         * @param array The array to concatenate with.
         * @return The resulting combined array.
         */
        [[nodiscard]] Array<T> concat(const Array<T>& array) const {
            Array<T> result(length + array.length);
            int i = 0;
            for (const T& element : *this) {
                result[i++] = T(data[i]);
            }
            for (const T& element : array) {
                result[i++] = T(array[i - length]);
            }
            return result;
        }

        // Override Functions

        // Iterator Functions

        [[nodiscard]] T* begin() override {
            return &data[0];
        }
        [[nodiscard]] const T* begin() const override {
            return &data[0];
        }
        [[nodiscard]] const T* cbegin() const override {
            return &data[0];
        }

        [[nodiscard]] T* end() override {
            return &data[length];
        }
        [[nodiscard]] const T* end() const override {
            return &data[length];
        }
        [[nodiscard]] const T* cend() const override {
            return &data[length];
        }

        // Reverse Iterator Functions

        [[nodiscard]] T* rbegin() override {
            return &data[length - 1];
        }

        [[nodiscard]] const T* rbegin() const override {
            return &data[length - 1];
        }

        [[nodiscard]] const T* crbegin() const override {
            return &data[length - 1];
        }


        [[nodiscard]] T* rend() override {
            return &data[-1];
        }

        [[nodiscard]] const T* rend() const override {
            return &data[-1];
        }

        [[nodiscard]] const T* crend() const override {
            return &data[-1];
        }

        // Assignment Operators

        /**
         * @brief (Deleted) The copy assignment operator for Array objects.
         * @details (Deleted) Reassigns the value of this object by copying the data of a Array
         *          into this object.
         * @warning Deleted
         */
        Array& operator=(const Array& rhs) = delete;

        /**
         * @brief (Deleted) The move assignment operator for Array objects.
         * @details (Deleted) Reassigns the value of this object by moving the data of a Array
         *          into this object.
         * @warning Deleted
         */
        Array& operator=(Array&& rhs) noexcept = delete;

        // Operators

        [[nodiscard]] T& operator[](std::size_t i) {
            // TODO: Add flag and behavior to perform optional bounds checking
            return data[i];
        }

        [[nodiscard]] const T& operator[](std::size_t i) const {
            return data[i];
        }

    };
}

#endif