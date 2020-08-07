/**
 * Entity.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_ENTITY_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_ENTITY_H_

#include "GameplayCoreAPI.hpp"
#include <map>
#include "SmartPointer.hpp"
#include "Component.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API Entity final : public ISerializable {

        friend class EntityManager;

        public:

            using EntityInstanceID = std::size_t;

        // Copy Constructors and Destructor

            /**
             * @brief The copy constructor for Entity objects.
             * @details Constructs a new Entity by copying an existing Entity.
             */
            Entity(const Entity& ref) = default;
            
            /**
             * @brief The move constructor for Entity objects.
             * @details Constructs a new Entity by moving the data of a Entity into this object.
             */
            Entity(Entity&& ref) = default;

            /**
             * @brief The destructor for Entity objects.
             * @details Called when an instance of Entity is deleted.
             */
            ~Entity();

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

        // Getter Functions

            /**
             * @brief Get the Instance ID of this entity.
             * 
             * @return EntityInstanceID The instance ID of this entity.
             */
            EntityInstanceID getInstanceID() const;

        // Functions

            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            bool attachComponent(const SharedPtr<T>& component) {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                Component::ComponentTypeID id = Component::getTypeID<T>();
                if (this->m_components.find(id) == this->m_components.end()) return false;
                else this->m_components[id] = component->getInstanceID();
                return true;
            }

            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            Component::ComponentInstanceID getComponentInstance() {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                Component::ComponentTypeID id = Component::getTypeID<T>();
                if (this->m_components.find(id) == this->m_components.end()) return Component::InvalidInstanceID;
                else return this->m_components[id];
            }

            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            Component::ComponentInstanceID detachComponentType() {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                Component::ComponentTypeID id = Component::getTypeID<T>();
                if (this->m_components.find(id) == this->m_components.end()) return Component::InvalidInstanceID;
                else {
                    Component::ComponentInstanceID inst_id = this->m_components[id];
                    this->m_components.erase(id);
                    return inst_id;
                }
            }

        private:

        // Private Constructors

            /**
             * @brief The default constructor for Entity objects.
             * @details Constructs a new Entity with default initialization for all members.
             * 
             * @param instance_id The instance ID to use for this entity.
             */
            Entity(const EntityInstanceID& instance_id);

        // Properaties

            EntityInstanceID m_instance_id;

            std::map<Component::ComponentTypeID, Component::ComponentInstanceID> m_components;

    };

}

#endif