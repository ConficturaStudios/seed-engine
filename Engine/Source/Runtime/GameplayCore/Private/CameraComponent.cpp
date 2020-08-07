/**
 * CameraComponent.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "CameraComponent.hpp"

namespace seedengine {

    CameraComponent::CameraComponent(const Component::ComponentInstanceID& instance_id) : Component(instance_id) {
        
    }

    CameraComponent::~CameraComponent() {
        
    }

    Matrix4 CameraComponent::getViewMatrix(Transform3DComponent& transform) const {
        return transform.transform.getTransformationMatrix().inverse();
    }

}