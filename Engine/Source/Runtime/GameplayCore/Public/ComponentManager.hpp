/**
 * ComponentManager.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_COMPONENT_MANAGER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_COMPONENT_MANAGER_H_

#include "GameplayCoreAPI.hpp"
#include "Component.hpp"

namespace seedengine {

    /**
     * @brief
     * @details
     * 
     */
    class ENGINE_API ComponentManager final {

        public:

        // Functions

            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            static T createComponent() {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                return 
            }

        // Operators

        private:

            template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
            static Component::ComponentInstanceID generateID(bool reset = false) {
                static_assert(std::is_base_of<Component, T>::value, "T must be of type Component.");
                static Component::ComponentInstanceID inst_id = Component::InvalidInstanceID;
                if (reset) inst_id = Component::InvalidInstanceID;
                return ++inst_id;
            }

    };

}

#endif