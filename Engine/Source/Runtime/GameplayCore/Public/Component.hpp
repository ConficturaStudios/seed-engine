/**
 * Component.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_COMPONENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_COMPONENT_H_

#include "GameplayCoreAPI.hpp"
#include <iostream>
#include "ISerializable.hpp"

namespace seedengine {

    /**
     * @brief A component to attach to an entity.
     * @details A component containing data to be attached to an entity.
     * 
     */
    class ENGINE_API Component : ISerializable {

        friend class ComponentManager;

        public:

        // Aliases

            using ComponentInstanceID = std::size_t;
            using ComponentTypeID = uint32_t;
            static constexpr const ComponentInstanceID InvalidInstanceID = 0;
            static constexpr const ComponentTypeID InvalidTypeID = 0;

        // Copy Constructors and Destructor

            /**
             * @brief The default constructor for Component objects. Unused.
             * @details Constructs a new Component with default initialization for all members.
             */
            Component() = delete;
            /**
             * @brief The copy constructor for Component objects.
             * @details Constructs a new Component by copying an existing Component.
             */
            Component(const Component& ref) = default;
            
            /**
             * @brief The move constructor for Component objects.
             * @details Constructs a new Component by moving the data of a Component into this object.
             */
            Component(Component&& ref) = default;

            /**
             * @brief The destructor for Component objects.
             * @details Called when an instance of Component is deleted.
             */
            virtual ~Component();

        // Override Functions

            /**
             * @brief Serializes this object into a stream.
             * 
             * @param target The output stream to write to.
             */
            virtual void serialize(std::ostream& target) const override;

            /**
             * @brief Deserializes the target from a stream.
             * 
             * @param source The source of the data to load in.
             */
            virtual void deserialize(std::istream& source) override;

        // Static Functions

            /**
             * @brief Get the type ID of the passed component.
             * 
             * @tparam T The type of component to check.
             * @tparam std::enable_if<std::is_base_of<Component, T>::value>::type Used for type verification.
             * 
             * @param component The component to check.
             * @return ComponentTypeID The type ID of this component.
             */
            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            static ComponentTypeID getTypeID(const T& component) {
                return getTypeID<T>();
            }

            /**
             * @brief Get the type ID of the template component type.
             * 
             * @tparam T The type of component to check.
             * @tparam std::enable_if<std::is_base_of<Component, T>::value>::type Used for type verification.
             * 
             * @return ComponentTypeID The type ID of this component.
             */
            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            static ComponentTypeID getTypeID() {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                static ComponentTypeID t_id = ++s_type_iter;
                return t_id;
            }

        // Getter Functions

            /**
             * @brief Get the instance ID of this component.
             * 
             * @return ComponentInstanceID The instance ID of this component.
             */
            ComponentInstanceID getInstanceID() const;

            /**
             * @brief Returns true if this component is enabled.
             * 
             * @return true This component is enabled.
             * @return false This component is disabled.
             */
            bool isEnabled() const;

        // Functions

            /**
             * @brief Enables this component if it is disabled.
             * 
             */
            void enable();

            /**
             * @brief Disables this component if it is enabled.
             * 
             */
            void disable();

            /**
             * @brief Queues this component to be destroyed.
             * @details Queues this component for destruction. This will remove this component from any entities it is attached to.
             */
            void destroy();

        // Event Functions

            /**
             * @brief Event handle called when this component is created.
             */
            virtual void onCreate();
            /**
             * @brief Event handle called when this component is attached to an active entity.
             */
            virtual void onAwake();
            /**
             * @brief Event handle called when this component is enabled.
             */
            virtual void onEnable();
            /**
             * @brief Event handle called when this component is disabled.
             */
            virtual void onDisable();
            /**
             * @brief Event handle called during the early update phase of the main program loop.
             */
            virtual void onEarlyUpdate();
            /**
             * @brief Event handle called during the update phase of the main program loop.
             */
            virtual void onUpdate();
            /**
             * @brief Event handle called during the fixed update phase of the main program loop.
             */
            virtual void onFixedUpdate();
            /**
             * @brief Event handle called during the late update phase of the main program loop.
             */
            virtual void onLateUpdate();
            /**
             * @brief Event handle called when this component is destroyed.
             */
            virtual void onDestroy();

        // Comparison Operators

            bool operator==(const Component& rhs) const;
            bool operator!=(const Component& rhs) const;

        // Assignment Operators

            /**
             * @brief The copy assignment operator for Component objects.
             * @details Reassigns the value of this object by copying the data of a Component into this object.
             */
            Component& operator=(const Component& ref) = default;

            /**
             * @brief The move assignment operator for Component objects.
             * @details Reassigns the value of this object by moving the data of a Component into this object.
             */
            Component& operator=(Component&& ref) = default;

        protected:

            /**
             * @brief The constructor for Component objects used by the ComponentManager.
             * @details Constructs a new Component with default initialization for all members.
             * 
             * @param instance_id The instance ID used by this component instance.
             */
            Component(const ComponentInstanceID& instance_id);

        private:

            /** The instance ID of this component, assigned at creation. */
            ComponentInstanceID m_instance_id;
            /** True if this component is enabled to recieve updates. */
            bool m_enabled = true;

            /** Used to track allocated type ID values. */
            static ComponentTypeID s_type_iter;

    };

}

#endif