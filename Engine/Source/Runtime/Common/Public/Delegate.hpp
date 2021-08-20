/**
 * @file Delegate.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_DELEGATE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_DELEGATE_H_

#include "CommonAPI.hpp"
#include <utility>
#include <tuple>

#include "FunctionPointer.hpp"
#include "MemberFunctionPointer.hpp"

#include "LinkedList.hpp"

namespace seedengine {

    /**
     * @brief A delegate responsible for notifying subscribers of events.
     * @details
     * A delegate responsible for notifying subscribed functions whenever this delegate
     * is broadcast. Global/static functions can subscribe as well as member functions (provided
     * an object instance).
     */
    template <typename... Args>
    class Delegate {

        public:

        // Constructors and destructor

            /**
             * @brief The default constructor for Delegate objects.
             * @details Constructs a new Delegate with default initialization for all members.
             */
            Delegate() {
                m_globals = new LinkedList<FunctionPointer<void, Args...>>();
                m_objects = new LinkedList<DelegateObject>();
            }

            /**
             * @brief The copy constructor for Delegate objects.
             * @details Constructs a new Delegate by copying an existing Delegate.
             */
            Delegate(const Delegate& ref) = default;
            
            /**
             * @brief The move constructor for Delegate objects.
             * @details Constructs a new Delegate by moving the data of a Delegate into this object.
             */
            Delegate(Delegate&& ref) noexcept = default;

            /**
             * @brief The destructor for Delegate objects.
             * @details Called when an instance of Delegate is deleted.
             */
            virtual ~Delegate() {
                delete m_globals;
                delete m_objects;
            }

        // Functions

            /**
             * Binds the provided function pointer to this delegate.
             * @param fp The function pointer to bind.
             */
            void bind(const FunctionPointer<void, Args...>& fp) {
                m_globals->addLast(fp);
            }

            /**
             * Binds the provided function pointer to this delegate.
             * @param fp The function pointer to bind.
             */
            void bind(void (*fp)(Args...)) {
                bind(FunctionPointer<void, Args...>(fp));
            }

            /*template <typename T>
            void bindObject(T* object, const MemberFunctionPointer<T, void, Args...>& mfp) {
                DelegateObject obj = { object, &internalCallObject<T, mfp> };
                m_objects->addLast(obj);
            }*/

            /**
             * Binds the provided object and member function to this delegate.
             * This version takes in non-const member functions.
             * @tparam T The type of object to bind.
             * @tparam MFP The (compile time constant) pointer to the member function to call.
             * @param object The object instance to call the member function from.
             */
            template <typename T, void (T::*MFP)(Args...)>
            void bindObject(T* object) {
                DelegateObject obj = { object, &Delegate<Args...>::internalCallObject<T, MFP> };
                m_objects->addLast(obj);
            }

            /**
             * Binds the provided object and member function to this delegate.
             * This version takes in const member functions.
             * @tparam T The type of object to bind.
             * @tparam MFP The (compile time constant) pointer to the member function to call.
             * @param object The object instance to call the member function from.
             */
            template <typename T, void (T::*MFP)(Args...) const>
            void bindObject(T* object) {
                DelegateObject obj = { object, &Delegate<Args...>::internalCallObjectConst<T, MFP> };
                m_objects->addLast(obj);
            }

            // TODO: Create functions to unbind functions and objects

            /**
             * Broadcasts the provided arguments to all subscribers of this delegate.
             * @param args The arguments to supply to subscribers.
             */
            void broadcast(Args&&... args) const {
                for (const FunctionPointer<void, Args...>& func : *m_globals) {
                    func(std::forward<Args>(args)...);
                }
                for (DelegateObject obj : *m_objects) {
                    obj.function(obj.instance, std::forward<Args>(args)...);
                }
            }

        // Operators

            /**
             * Binds the provided function pointer to this delegate.
             * @param fp The function pointer to bind.
             * @return A reference to this delegate.
             */
            Delegate& operator+=(const FunctionPointer<void, Args...>& fp) {
                bind(fp);
                return *this;
            }

            /**
             * Binds the provided function pointer to this delegate.
             * @param fp The function pointer to bind.
             * @return A reference to this delegate.
             */
            Delegate& operator+=(void (*fp)(Args...)) {
                bind(fp);
                return *this;
            }

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Delegate objects.
             * @details Reassigns the value of this object by copying the data of a Delegate into this object.
             */
            Delegate& operator=(const Delegate& rhs) = default;

            /**
             * @brief The move assignment operator for Delegate objects.
             * @details Reassigns the value of this object by moving the data of a Delegate into this object.
             */
            Delegate& operator=(Delegate&& rhs) noexcept = default;

        protected:

            /**
             * A type erased object passed to this delegate.
             */
            struct DelegateObject {
                /** The type-erased pointer to the object instance. */
                void* instance;
                /** A pointer to the internal call instance used for this object. */
                void (*function)(void*, Args&&...);

                [[nodiscard]] bool operator==(const DelegateObject& rhs) const {
                    return this->instance == rhs.instance && this->function == rhs.function;
                }

                [[nodiscard]] bool operator!=(const DelegateObject& rhs) const {
                    return this->instance != rhs.instance || this->function != rhs.function;
                }
            };

        private:

            /**
             * An internal call method used to wrap member function calls in a generic, type free context.
             * This version is used for non-const member functions.
             * @tparam T The type of the owning object.
             * @tparam Func The member function to call.
             * @param instance A pointer to the owning object instance.
             * @param args The arguments to call the function with.
             */
            template <typename T, void (T::*Func)(Args...)>
            static void internalCallObject(void* instance, Args&&... args) {
                (static_cast<T*>(instance)->*Func)(std::forward<Args>(args)...);
            }

            /**
             * An internal call method used to wrap member function calls in a generic, type free context.
             * This version is used for const member functions.
             * @tparam T The type of the owning object.
             * @tparam Func The member function to call.
             * @param instance A pointer to the owning object instance.
             * @param args The arguments to call the function with.
             */
            template <typename T, void (T::*Func)(Args...) const>
            static void internalCallObjectConst(void* instance, Args&&... args) {
                (static_cast<T*>(instance)->*Func)(std::forward<Args>(args)...);
            }

            // TODO: Switch to a Set to allow O(1) removals

            /** The list of global and static function subscribers. */
            LinkedList<FunctionPointer<void, Args...>>* m_globals;
            /** The list of object delegate wrappers for member function calls. */
            LinkedList<DelegateObject>* m_objects;

    };

}

#endif