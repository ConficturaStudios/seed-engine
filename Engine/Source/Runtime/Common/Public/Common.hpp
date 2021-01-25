/**
 * Common.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_MODULE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_MODULE_H_

#include "CommonAPI.hpp"


#include "CommonDefinitions.hpp"
#include "CommonMacros.hpp"
#include "CommonSTL.hpp"
#include "CommonTraits.hpp"
#include "FunctionPointer.hpp"
#include "GraphicsMode.hpp"
#include "ISerializable.hpp"
#include "Log.hpp"
#include "MemberFunctionPointer.hpp"
#include "Platform.hpp"
#include "SmartPointer.hpp"
#include "String.hpp"
#include "System.hpp"

#ifdef ENGINE_API
    #undef ENGINE_API
#endif

#endif