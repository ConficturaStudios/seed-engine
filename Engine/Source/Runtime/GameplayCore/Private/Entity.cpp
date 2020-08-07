/**
 * Entity.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Entity.hpp"

namespace seedengine {

    Entity::Entity(const Entity::EntityInstanceID& instance_id) {
        this->m_instance_id = instance_id;
        this->m_components = std::map<Component::ComponentTypeID, Component::ComponentInstanceID>();
    }

    Entity::~Entity() {
        
    }

    // --- Serialization ---

    void Entity::serialize(std::ostream& target) const {

    }

    void Entity::deserialize(std::istream& source) {

    }

    // --- Functions ---

    Entity::EntityInstanceID Entity::getInstanceID() const {
        return this->m_instance_id;
    }

}