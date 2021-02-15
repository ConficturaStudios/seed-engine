/**
 * GameplayCoreAPI.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */
 
#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_API_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_API_H_

#include "Math.hpp"
#include "Common.hpp"


#ifndef RUNTIME_GAMEPLAY_CORE_EXPORT_API
    #if BUILD_SHARED_LIBS
        #if defined(_WIN32) || defined(__CYGWIN__) || defined(_MSC_VER)
            #define RUNTIME_GAMEPLAY_CORE_EXPORT_API __declspec(dllexport)
            #define RUNTIME_GAMEPLAY_CORE_IMPORT_API __declspec(dllimport)
            #define RUNTIME_GAMEPLAY_CORE_HIDDEN_API
        #elif defined(__GNUC__) && __GNUC__ >= 4
            #define RUNTIME_GAMEPLAY_CORE_EXPORT_API __attribute__((visibility("default")))
            #define RUNTIME_GAMEPLAY_CORE_IMPORT_API __attribute__((visibility("default")))
            #define RUNTIME_GAMEPLAY_CORE_HIDDEN_API __attribute__((visibility("hidden")))
        #else
            #define RUNTIME_GAMEPLAY_CORE_EXPORT_API
            #define RUNTIME_GAMEPLAY_CORE_IMPORT_API
            #define RUNTIME_GAMEPLAY_CORE_HIDDEN_API
        #endif
    #else
        #define RUNTIME_GAMEPLAY_CORE_EXPORT_API
        #define RUNTIME_GAMEPLAY_CORE_IMPORT_API
        #define RUNTIME_GAMEPLAY_CORE_HIDDEN_API
    #endif
#endif

//#ifndef ${PROJECT_IDENTIFIER}_API
#ifndef ENGINE_API
    #ifdef RUNTIME_GAMEPLAY_CORE_EXPORT
        #define ENGINE_API RUNTIME_GAMEPLAY_CORE_EXPORT_API
    #else
        #define ENGINE_API RUNTIME_GAMEPLAY_CORE_IMPORT_API
    #endif
#endif

#endif



// Original:

/**
 * GameplayCoreAPI.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */
 
/*
#ifndef SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_API_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GAMEPLAY_CORE_API_H_

#include "Math.hpp"
#include "Common.hpp"


#ifndef ENGINE_API

    #if defined(_WIN32) && defined(BUILD_SHARED_LIBS)
        #if BUILD_SHARED_LIBS
            #if defined(_MSC_VER)
                #pragma warning(disable: 4251)
            #endif

            #if defined(RUNTIME_GAMEPLAY_CORE_EXPORT)
                #define ENGINE_API __declspec(dllexport)
            #else
                #define ENGINE_API __declspec(dllimport)
            #endif
        #else
            #define ENGINE_API
        #endif
    #else
        #define ENGINE_API
    #endif
    
#endif

#endif
*/