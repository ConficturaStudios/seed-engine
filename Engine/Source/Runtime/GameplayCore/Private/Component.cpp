/**
 * Component.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Component.hpp"

namespace seedengine {

    // Static initialization

    Component::ComponentTypeID Component::s_type_iter = 1;

    // Constructor and destructor

    Component::Component(const Component::ComponentInstanceID& instance_id) {
        this->m_instance_id = instance_id;
        this->m_enabled = true;
    }

    Component::~Component() {

    }

    // Functions

    Component::ComponentInstanceID Component::getInstanceID() const {
        return this->m_instance_id;
    }

    bool Component::isEnabled() const {
        return this->m_enabled;
    }

    void Component::enable() {
        if (!m_enabled) {
            this->m_enabled = true;
            this->onEnable();
        }
        // else throw warning if debug logging enabled
    }

    void Component::disable() {
        if (m_enabled) {
            this->m_enabled = false;
            this->onDisable();
        }
        // else throw warning if debug logging enabled
    }

    void Component::destroy() {
        // Queue in ComponentManager for destroy
    }

    // Events

    void Component::onCreate() {

    }

    void Component::onAwake() {

    }
    
    void Component::onEnable() {

    }
    
    void Component::onDisable() {

    }
    
    void Component::onEarlyUpdate() {

    }
    
    void Component::onUpdate() {

    }
    
    void Component::onFixedUpdate() {

    }
    
    void Component::onLateUpdate() {

    }
    
    void Component::onDestroy() {

    }
    

}