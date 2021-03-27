/**
 * @file GraphicsManager.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_GRAPHICS_MANAGER_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_GRAPHICS_MANAGER_H_

#include "GraphicsAPI.hpp"

namespace seedengine {

    /**
     * @brief The available graphics frameworks.
     */
    enum class EGraphicsFramework : uint8 {
        OPEN_GL = 0,
        VULKAN = 1,
        DIRECT_X = 2,
        METAL = 3
    };

    // TODO: Create toString<EGraphicsFramework>() specialization

    // TODO: figure out how to select the active graphics implementation class(es) at runtime
    // TODO: allow users to get a list of available frameworks (needed for selection dropdowns)
    // TODO: implement/create OpenGLGraphicsManager, DirectXGraphicsManager, etc.
    // TODO: handle all api initialization and termination in graphics manager implementation

    /**
     * @brief The manager responsible for controlling initialization and shutdown for the active
     *        graphics API.
     * @details
     * 
     */
    class ENGINE_API GraphicsManager {

        public:

            [[nodiscard]] static EGraphicsFramework GetFramework();
            static void SetFramework(EGraphicsFramework framework);

            [[nodiscard]] static Array<EGraphicsFramework> GetAvailableFrameworks() noexcept;

            static bool Startup();
            static bool Startup(EGraphicsFramework framework);

            static void Shutdown();

            [[nodiscard]] static bool Initialized();

        protected:

            explicit GraphicsManager(EGraphicsFramework framework);
            virtual ~GraphicsManager();

        private:

            static GraphicsManager* s_instance;
            EGraphicsFramework m_framework;



    };

}

#endif