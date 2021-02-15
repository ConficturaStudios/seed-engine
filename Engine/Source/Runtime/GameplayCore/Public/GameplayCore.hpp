/**
 * GameplayCore.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_MODULE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_MODULE_H_

#include "GameplayCoreAPI.hpp"


#include "CameraComponent.hpp"
#include "CameraProperties.hpp"
#include "Component.hpp"
#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Level.hpp"
#include "LevelManager.hpp"
#include "Transform3DComponent.hpp"

#ifdef ENGINE_API
    #undef ENGINE_API
#endif

#endif