/**
 * Transform3DComponent.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_TRANSFORM3D_COMPONENT_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_TRANSFORM3D_COMPONENT_H_

#include "GameplayCoreAPI.hpp"
#include "Component.hpp"

namespace seedengine {

    /**
     * @brief A component that contains 3D transform data.
     * @details A component that contains 3D transform data.
     *          This is used directly by the rendering system.
     * 
     * @see Component
     * @see Transform3D
     */
    class ENGINE_API Transform3DComponent : public Component {

        public:

        // Properties

            Transform3D transform;

        // Constructors and destructor

            /**
             * @brief The default constructor for Transform3DComponent objects.
             * @details Constructs a new Transform3DComponent with default initialization for all members.
             * 
             * @param instance_id The ID to use for this component instance.
             */
            Transform3DComponent(const Component::ComponentInstanceID& instance_id);

            /**
             * @brief The copy constructor for Transform3DComponent objects.
             * @details Constructs a new Transform3DComponent by copying an existing Transform3DComponent.
             */
            Transform3DComponent(const Transform3DComponent& ref) = default;
            
            /**
             * @brief The move constructor for Transform3DComponent objects.
             * @details Constructs a new Transform3DComponent by moving the data of a Transform3DComponent into this object.
             */
            Transform3DComponent(Transform3DComponent&& ref) = default;

            /**
             * @brief The destructor for Transform3DComponent objects.
             * @details Called when an instance of Transform3DComponent is deleted.
             */
            virtual ~Transform3DComponent();

        // Functions



        // Operators

            /**
             * @brief The copy assignment operator for Transform3DComponent objects.
             * @details Reassigns the value of this object by copying the data of a Transform3DComponent into this object.
             */
            Transform3DComponent& operator=(const Transform3DComponent& ref) = default;

            /**
             * @brief The move assignment operator for Transform3DComponent objects.
             * @details Reassigns the value of this object by moving the data of a Transform3DComponent into this object.
             */
            Transform3DComponent& operator=(Transform3DComponent&& ref) = default;

        protected:

        private:

    };

}

#endif