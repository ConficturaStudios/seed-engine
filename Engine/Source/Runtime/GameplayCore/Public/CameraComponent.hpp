/**
 * CameraComponent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_CAMERA_COMPONENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_CAMERA_COMPONENT_H_

#include "GameplayCoreAPI.hpp"
#include "SmartPointer.hpp"
#include "Component.hpp"
#include "CameraProperties.hpp"
#include "Transform3DComponent.hpp"

namespace seedengine {

    /**
     * @brief A component containing data necessary for the parent entity to act as a camera.
     * @details A component containing data necessary for the parent entity to act as a camera.
     * 
     *          A Transform3DComponent should accompany this Component.
     * 
     *          This component is passed to the rendering system if it is the active camera, or
     *          if it is used for writing to a render target/buffer.
     * 
     * @see Component
     * @see Transform3DComponent
     */
    class ENGINE_API CameraComponent : public Component {

        public:

        // Properties

            UniquePtr<ICameraProperties> properties;

        // Constructors and destructor

            /**
             * @brief The default constructor for CameraComponent objects.
             * @details Constructs a new CameraComponent with default initialization for all members.
             * 
             * @param instance_id The ID to use for this component instance.
             */
            CameraComponent(const Component::ComponentInstanceID& instance_id);

            /**
             * @brief The copy constructor for CameraComponent objects.
             * @details Constructs a new CameraComponent by copying an existing CameraComponent.
             */
            CameraComponent(const CameraComponent& ref) = default;
            
            /**
             * @brief The move constructor for CameraComponent objects.
             * @details Constructs a new CameraComponent by moving the data of a CameraComponent into this object.
             */
            CameraComponent(CameraComponent&& ref) = default;

            /**
             * @brief The destructor for CameraComponent objects.
             * @details Called when an instance of CameraComponent is deleted.
             */
            virtual ~CameraComponent();

        // Functions

            /**
             * @brief Get the view matrix of the companion Transform3DComponent.
             * 
             * @param transform The Transfrom3DComponent that accompanies this CameraComponent.
             * @return Matrix4 The view matrix for this camera.
             */
            Matrix4 getViewMatrix(Transform3DComponent& transform) const;

        // Operators

            /**
             * @brief The copy assignment operator for CameraComponent objects.
             * @details Reassigns the value of this object by copying the data of a CameraComponent into this object.
             */
            CameraComponent& operator=(const CameraComponent& ref) = default;

            /**
             * @brief The move assignment operator for CameraComponent objects.
             * @details Reassigns the value of this object by moving the data of a CameraComponent into this object.
             */
            CameraComponent& operator=(CameraComponent&& ref) = default;

        protected:

        private:

    };

}

#endif